#include "pch.h"
#include "CPlayer.h"

#include "CCamera.h"
#include "CAssetMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CTaskMgr.h"
#include "CDbgRender.h"

#include "CMissile.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CGun.h"
#include "CReloadUI.h"

#include "CMonster.h"
#include "CCollider.h"
#include "CFlipbookPlayer.h"
#include "CGuidedMissile.h"

#include "CEngine.h"
#include "CTexture.h"
#include "CFlipbook.h"
#include "CSprite.h"
#include "CRigidBody.h"

#include "CFSM.h"
#include "CPlayerIdleState.h"
#include "CPlayerMovingState.h"
#include "CPlayerEvadingState.h"



bool IsRollState(PLAYER_ANIM_STATE _state)
{
	return _state == ROLL_UP
		|| _state == ROLL_UPRIGHT
		|| _state == ROLL_UPLEFT
		|| _state == ROLL_DOWN
		|| _state == ROLL_DOWNLEFT
		|| _state == ROLL_LEFT
		|| _state == ROLL_RIGHT
		|| _state == ROLL_START;
}

bool IsIdleState(PLAYER_ANIM_STATE _state)
{
	return _state == IDLE_UP
		|| _state == IDLE_UPRIGHT
		|| _state == IDLE_UPLEFT
		|| _state == IDLE_DOWN
		|| _state == IDLE_DOWNLEFT
		|| _state == IDLE_LEFT
		|| _state == IDLE_RIGHT
		|| _state == IDLE_START;
}

bool IsMoveState(PLAYER_ANIM_STATE _state)
{
	return _state == MOVE_UP
		|| _state == MOVE_UPRIGHT
		|| _state == MOVE_UPLEFT
		|| _state == MOVE_DOWN
		|| _state == MOVE_DOWNLEFT
		|| _state == MOVE_LEFT
		|| _state == MOVE_RIGHT
		|| _state == MOVE_START;
}

CPlayer::CPlayer()
	: m_curHP(6)
	, m_maxHP(6)
	, m_blankCnt(1)
	, m_keyCnt(1)
	, m_moveSpeed(500.f)
	, m_HitBox(nullptr)
	, m_FlipbookPlayer(nullptr)
	, m_gun(nullptr)
	, m_fsm(nullptr)
	, m_reloadBar(nullptr)
	, m_rollSpeed(1200.f)
	, m_rollTime(0.7f)
	, m_rollAccTime(0.f)
	, m_isInvincible(false)
	, m_invincibleAccTime(0.f)
	, m_invincibleTime(0.7f)
	, m_state(IDLE_DOWN)
	, m_RigidBody(nullptr)
{
	// Collider 컴포넌트 추가
	m_HitBox = new CCollider;
	m_HitBox->SetName(L"HitBox_01");
	m_HitBox->SetScale(Vec2(60.f, 60.f));
	m_HitBox->SetOffset(Vec2(0.f, 0.f));

	AddComponent(m_HitBox);

	// fsm 생성 및 등록
	m_fsm = (CFSM*)AddComponent(new CFSM);
	m_fsm->AddState(L"Idle", new CPlayerIdleState);
	m_fsm->AddState(L"Moving", new CPlayerMovingState);
	m_fsm->AddState(L"Evading", new CPlayerEvadingState);


	// Flipbook 생성 및 등록
	CreatePlayerFlipbook();

	// RigidBody 컴포넌트 추가
	m_RigidBody = (CRigidBody*)AddComponent(new CRigidBody);
	m_RigidBody->SetMode(RIGIDBODY_MODE::TOPVIEW);
	//m_RigidBody->SetInitialSpeed(100.f);
	//m_RigidBody->SetMaxSpeed(500.f);
	m_RigidBody->SetMass(1.f);
	//m_RigidBody->SetFriction(1000.f);
	//m_RigidBody->SetJumpVelocity(Vec2(0.f, -500.f));


}

CPlayer::~CPlayer()
{	
}

void CPlayer::Begin()
{

	m_FlipbookPlayer->Play(IDLE_DOWN, 5.f, true);

	CCamera::GetInst()->SetTarget(this);


}

void CPlayer::Tick()
{
	// update gun direction
	Vec2 mousePos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());
	m_gunDir = GetPos() - mousePos;
	m_gunDir.Normalize();

	// update move direction
	if (!IsRollState(m_state))
	{
		// get move direction
		m_moveDir = { 0.f, 0.f };

		if (KEY_PRESSED(KEY::A))
			m_moveDir += Vec2(-1.f, 0.f);
		if (KEY_PRESSED(KEY::D))
			m_moveDir += Vec2(1.f, 0.f);
		if (KEY_PRESSED(KEY::W))
			m_moveDir += Vec2(0.f, -1.f);
		if (KEY_PRESSED(KEY::S))
			m_moveDir += Vec2(0.f, 1.f);

		if (m_moveDir.x != 0.f || m_moveDir.y != 0.f)
			m_moveDir.Normalize();
	}

	// check if collided with wall
	if (m_normal.x * m_moveDir.x < 0) // if normal and move direction is "not" the same
	{
		m_moveDir.x = 0.f;
	}
	if (m_normal.y * m_moveDir.y < 0)
	{
		m_moveDir.y = 0.f;
	}

	// check for invincible state
	if (m_isInvincible)
	{
		m_invincibleAccTime += DT;
		if (m_invincibleAccTime >= m_invincibleTime)
		{
			m_invincibleAccTime = 0;
			m_isInvincible = false;
		}
	}

	// for animation
	switch (m_state)
	{
	case IDLE_UP:
	case IDLE_UPRIGHT:
	case IDLE_UPLEFT:
	case IDLE_DOWN:
	case IDLE_DOWNRIGHT:
	case IDLE_DOWNLEFT:
	case IDLE_LEFT:
	case IDLE_RIGHT:
	case IDLE_START:
		IdleState();
		break;
	case MOVE_UP:
	case MOVE_UPRIGHT:
	case MOVE_UPLEFT:
	case MOVE_DOWN:
	case MOVE_DOWNRIGHT:
	case MOVE_DOWNLEFT:
	case MOVE_LEFT:
	case MOVE_RIGHT:
	case MOVE_START:
		MoveState();
		break;
	case ROLL_UP:
	case ROLL_UPRIGHT:
	case ROLL_UPLEFT:
	case ROLL_DOWN:
	case ROLL_DOWNRIGHT:
	case ROLL_DOWNLEFT:
	case ROLL_LEFT:
	case ROLL_RIGHT:
	case ROLL_START:
		RollState();
		break;
	case DEAD:
		DeadState();
	default:
		IdleState();
		break;
	}

	// gun related
	if (m_gun != nullptr)
	{
		if (!IsRollState(m_state))
		{
			GUN_STATE fireResult = m_gun->Fire();
			if (fireResult == GUN_STATE::RELOAD)
			{
				this->Reload(m_gun->GetReloadDelay());
			}
		}

		// R key works even if rolling happening
		GUN_STATE reloadResult = m_gun->Reload(false);
		if (reloadResult == GUN_STATE::RELOAD)
		{
			this->Reload(m_gun->GetReloadDelay());
		}
	}

	// USE item
	if (KEY_TAP(SPACE) && !IsRollState(m_state))
	{
		//m_RigidBody->Jump();
		//DrawDebugRect(PEN_TYPE::GREEN, GetPos(), GetScale() * 2.f, 3.f);
		//DrawDebugCircle(PEN_TYPE::GREEN, GetPos(), GetScale() * 2.f, 3.f);
		//DrawDebugLine(PEN_TYPE::GREEN, GetPos(), GetPos() + GetScale(), 3.f);
	}

	// use blank
	if (KEY_TAP(KEY::Q))
	{
		// do blank stuff
		if (m_blankCnt > 0) 
		{
			// blank effect
			CCamera::GetInst()->PostProcessEffect(HEART, 0.2f);

			DeleteObjects(LAYER_TYPE::MONSTER_OBJECT);
			m_blankCnt--;
		}
	}

	DrawDebugCircle(PEN_TYPE::RED, GetRenderPos(), Vec2(5.f, 5.f), 0.f);

	PEN_TYPE penType = PEN_TYPE::RED;

	switch (m_state)
	{
	case IDLE_UP:
	case IDLE_UPRIGHT:
	case IDLE_UPLEFT:
	case IDLE_DOWN:
	case IDLE_DOWNRIGHT:
	case IDLE_DOWNLEFT:
	case IDLE_LEFT:
	case IDLE_RIGHT:
		penType = PEN_TYPE::GREEN;
		break;
	case MOVE_UP:
	case MOVE_UPRIGHT:
	case MOVE_UPLEFT:
	case MOVE_DOWN:
	case MOVE_DOWNRIGHT:
	case MOVE_DOWNLEFT:
	case MOVE_LEFT:
	case MOVE_RIGHT:
		penType = PEN_TYPE::BLUE;
		break;
	case ROLL_UP:
	case ROLL_UPRIGHT:
	case ROLL_UPLEFT:
	case ROLL_DOWN:
	case ROLL_DOWNRIGHT:
	case ROLL_DOWNLEFT:
	case ROLL_LEFT:
	case ROLL_RIGHT:
		penType = PEN_TYPE::RED;
		break;
	default:
		penType = PEN_TYPE::GREEN;
		break;
	}

	DrawDebugRect(penType, GetRenderPos() + Vec2(50.f, -50.f), Vec2(10.f, 10.f), 0.f);
}

void CPlayer::Render()
{
	m_FlipbookPlayer->Render();
}

void CPlayer::BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
	if (_OtherObject->GetName() == L"Monster")
	{
		if (m_isInvincible)
			return;

		m_curHP--;
		if (m_curHP == 0)
			m_state = DEAD;
		m_isInvincible = true;
	}
	else if (_OtherObject->GetLayerType() == LAYER_TYPE::MONSTER_OBJECT)
	{
		if (m_isInvincible || IsRollState(m_state))
			return;

		m_curHP--;
		if (m_curHP == 0)
			m_state = DEAD;
		m_isInvincible = true;
	}
}

void CPlayer::Overlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
	if (_OtherObject->GetLayerType() == LAYER_TYPE::TILE)
	{
		auto normal = _Collider->CalCulateNormal(_OtherCollider);

		if (abs(normal.x) > 0) m_normal.x = normal.x;
		else m_normal.y = normal.y;
	}
}

void CPlayer::EndOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
	if (_OtherObject->GetLayerType() == LAYER_TYPE::TILE)
	{
		m_normal = Vec2(0.f, 0.f);
	}

}

void CPlayer::CreatePlayerFlipbook()
{
	// FlipbookPlayer 컴포넌트 추가하기
	m_FlipbookPlayer = (CFlipbookPlayer*)AddComponent(new CFlipbookPlayer);
	
	m_FlipbookPlayer->AddFlipbook(IDLE_DOWN, CAssetMgr::GetInst()->LoadFlipbook(L"rogue_idle_front" , L"Flipbook\\SpaceRogue\\rogue_idle_front.flip" ));
	m_FlipbookPlayer->AddFlipbook(IDLE_LEFT, CAssetMgr::GetInst()->LoadFlipbook(L"rogue_idle_hands2", L"Flipbook\\SpaceRogue\\rogue_idle_hands2.flip" ));
	m_FlipbookPlayer->AddFlipbook(IDLE_UP,	 CAssetMgr::GetInst()->LoadFlipbook(L"rogue_idle_back",   L"Flipbook\\SpaceRogue\\rogue_idle_back.flip"   ));
	m_FlipbookPlayer->AddFlipbook(IDLE_RIGHT,CAssetMgr::GetInst()->LoadFlipbook(L"rogue_idle_hands",  L"Flipbook\\SpaceRogue\\rogue_idle_hands.flip" ));

	m_FlipbookPlayer->AddFlipbook(MOVE_DOWN, CAssetMgr::GetInst()->LoadFlipbook(L"rogue_run_front",   L"Flipbook\\SpaceRogue\\rogue_run_front.flip"));
	m_FlipbookPlayer->AddFlipbook(MOVE_LEFT, CAssetMgr::GetInst()->LoadFlipbook(L"rogue_run_forward", L"Flipbook\\SpaceRogue\\rogue_run_forward.flip"));
	m_FlipbookPlayer->AddFlipbook(MOVE_UP,   CAssetMgr::GetInst()->LoadFlipbook(L"rogue_run_back",    L"Flipbook\\SpaceRogue\\rogue_run_back.flip"));
	m_FlipbookPlayer->AddFlipbook(MOVE_RIGHT,CAssetMgr::GetInst()->LoadFlipbook(L"rogue_run_forward", L"Flipbook\\SpaceRogue\\rogue_run_forward.flip"));
}

void CPlayer::CreateFlipbook(const wstring& _FlipbookName, CTexture* _Atlas, Vec2 _LeftTop, Vec2 _Slice, int MaxFrame)
{
	return;
	// Sprite 생성하기
	//for (int i = 0; i < MaxFrame; ++i)
	//{
	//	CSprite* pSprite = new CSprite;
	//	pSprite->Create(_Atlas, Vec2(_LeftTop.x + (_Slice.x * i), _LeftTop.y), _Slice);

	//	wchar_t Key[50] = {};
	//	swprintf_s(Key, 50, (_FlipbookName + L"_%d").c_str(), i);
	//	CAssetMgr::GetInst()->AddSprite(Key, pSprite);

	//	wstring strSavePath = L"Sprite\\";
	//	strSavePath += pSprite->GetKey();
	//	pSprite->Save(strSavePath);
	//}

	for (int i = 0; i < MaxFrame; ++i)
	{
		wchar_t Key[50] = {};
		swprintf_s(Key, 50, (_FlipbookName + L"_%d").c_str(), i);		
		wstring Path = L"Sprite\\";		
		Path += Key;
		CAssetMgr::GetInst()->LoadSprite(Key, Path + L".sprite");
	}


	// Flipbook 생성하기
	//CFlipbook* pFlipbook = new CFlipbook;

	//for (int i = 0; i < MaxFrame; ++i)
	//{
	//	wchar_t Key[50] = {};
	//	swprintf_s(Key, 50, (_FlipbookName + L"_%d").c_str(), i);
	//	pFlipbook->AddSprite(CAssetMgr::GetInst()->FindSprite(Key));		
	//}

	//CAssetMgr::GetInst()->AddFlipbook(_FlipbookName, pFlipbook);
	//wstring Path = L"Flipbook\\";
	//pFlipbook->Save(Path + _FlipbookName);
}

void CPlayer::IdleState()
{
	if (m_moveDir.Length() > 0)
	{
		m_state = MOVE_START;
		return;
	}

	
}

void CPlayer::MoveState()
{
	if (KEY_TAP(KEY::RBTN))
	{
		m_state = ROLL_DOWN;
	}
	else if (m_moveDir.Length() > 0)
	{
		auto velocity = m_moveDir * m_moveSpeed;
		m_RigidBody->SetVelocity(velocity);
		PLAYER_ANIM_STATE before = m_state;
		bool isMirrored = false;
		if (m_moveDir.x > 0)
		{
			m_state = MOVE_RIGHT;
		}
		else if (m_moveDir.x < 0)
		{
			m_state = MOVE_RIGHT;
			isMirrored = true;
		}
		else if (m_moveDir.y > 0)
		{
			m_state = MOVE_DOWN;
		}
		else
			m_state = MOVE_UP;

		if (before != m_state)
			m_FlipbookPlayer->Play(m_state, 10.f, true, isMirrored);
	}
	else
	{
		m_RigidBody->SetVelocity(Vec2(0.f, 0.f));
		switch (m_state)
		{
		case MOVE_UP:
			m_state = IDLE_UP;
			break;
		case MOVE_DOWN:
			m_state = IDLE_DOWN;
			break;
		case MOVE_UPRIGHT:
		case MOVE_DOWNRIGHT:
		case MOVE_RIGHT:
			m_state = IDLE_RIGHT;
			break;
		case MOVE_UPLEFT:
		case MOVE_DOWNLEFT:
		case MOVE_LEFT:
			m_state = IDLE_LEFT;
			break;
		}
		m_FlipbookPlayer->Play(m_state, 10.f, true);
	}
}

void CPlayer::RollState()
{
	m_rollAccTime += DT;
	if (m_rollAccTime < m_rollTime)
	{
		float rollSpeed = m_rollSpeed;
		float ratio = m_rollAccTime / m_rollTime;
		rollSpeed *= ratio < 0.4f ? 1.0f : 0.15f;
		//SetPos(GetPos() + m_moveDir * rollSpeed * DT);
		m_RigidBody->SetVelocity(m_moveDir * rollSpeed);
		// state 표시용
		DrawDebugRect(PEN_TYPE::RED, GetRenderPos() + Vec2(50.f, -50.f), Vec2(10.f, 10.f), 0.f);
		return;
	}

	m_rollAccTime = 0;
	m_state = MOVE_DOWN;
}

void CPlayer::DeadState()
{
	ChangeLevel(LEVEL_TYPE::EDITOR);
}

void CPlayer::Reload(float _duration)
{
	m_reloadBar->Draw(_duration);
}

