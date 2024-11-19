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
#include "CCollisionMgr.h"

#include "CMonster.h"
#include "CCollider.h"
#include "CFlipbookPlayer.h"
#include "CGuidedMissile.h"

#include "CEngine.h"
#include "CTexture.h"
#include "CFlipbook.h"
#include "CSprite.h"
#include "CRigidBody.h"




bool IsRollState(PLAYER_STATE _state)
{
	return _state == PLAYER_STATE::ROLLING;
}

bool IsIdleState(PLAYER_STATE _state)
{
	return _state == PLAYER_STATE::IDLE;
}

bool IsMoveState(PLAYER_STATE _state)
{
	return _state == PLAYER_STATE::MOVING;
}

tAnimState ProcessDodgeAnimState(const Vec2& _dir)
{
	tAnimState state = { ROGUE_DODGE_LEFT, false };

	if (_dir.x == 0.f)
	{
		state.mirror = false;
		if (_dir.y >= 0.f)
		{
			state.idx = ROGUE_DODGE_FRONT;
		}
		else
		{
			state.idx = ROGUE_DODGE_BACK;
		}	
	} 
	
	else
	{
		state.mirror = _dir.x < 0.f;
		if (_dir.y >= 0.f)
		{
			state.idx = ROGUE_DODGE_LEFT;
		}
		else
		{
			state.idx = ROGUE_DODGE_LEFT_BACK;
		}
	}

	return state;
}

/* TODO: change it to binary search tree???*/
tAnimState CPlayer::ProcessAnimState(const Vec2& _dir, const PLAYER_STATE _state)
{
	float angle = std::atan2f(-_dir.y, _dir.x) * (180.0 / PI);
	tAnimState state = { ROGUE_IDLE_FRONT_HANDS, false };

	// forward or backward
	if (fabs(fabs(angle) - 90.f) >= 20.f) 
	{
		if (_dir.y < 0.f)
		{
			switch (_state)
			{
			case PLAYER_STATE::MOVING:
				state.idx = ROGUE_RUN_BACKWARD;
				break;
			case PLAYER_STATE::IDLE:
			default:
				state.idx = ROGUE_IDLE_BACKWARDS;
				break;
			}
		}

		else
		{
			switch (_state)
			{
			case PLAYER_STATE::MOVING:
				state.idx = ROGUE_RUN_FORWARD_HANDS;
				break;
			case PLAYER_STATE::IDLE:
			default:
				state.idx = ROGUE_IDLE_HANDS;
				break;
			}
		}
	}
	// front or back
	else
	{
		// back
		if (_dir.y < 0.f)
		{
			switch (_state)
			{
			case PLAYER_STATE::MOVING:
				state.idx = ROGUE_RUN_BACK_HANDS_LEFT;
				break;
			case PLAYER_STATE::IDLE:
			default:
				state.idx = ROGUE_IDLE_BACK_HAND_LEFT;
				break;
			}
		}
		// front
		else
		{
			switch (_state)
			{
			case PLAYER_STATE::MOVING:
				state.idx = ROGUE_RUN_FRONT_HANDS_LEFT;
				break;
			case PLAYER_STATE::IDLE:
			default:
				state.idx = ROGUE_IDLE_FRONT_HAND_LEFT;
				break;
			}
		}
	}

	state.mirror = !(m_gun->IsRightHand());

	return state;
}

CPlayer::CPlayer()
	: m_curHP(6)
	, m_maxHP(6)
	, m_blankCnt(1)
	, m_keyCnt(1)
	, m_moveSpeed(400.f)
	, m_HitBox(nullptr)
	, m_FlipbookPlayer(nullptr)
	, m_gun(nullptr)
	, m_reloadBar(nullptr)
	, m_rollSpeed(500.f)
	, m_rollTime(0.6f)
	, m_rollAccTime(0.f)
	, m_isInvincible(false)
	, m_invincibleAccTime(0.f)
	, m_invincibleTime(0.7f)
	, m_animState({ ROGUE_IDLE, false })
	, m_RigidBody(nullptr)
{
	// Collider 컴포넌트 추가
	SetScale(45.f, 50.f);



	// Flipbook 생성 및 등록
	CreatePlayerFlipbook();

	// RigidBody 컴포넌트 추가
	m_RigidBody = (CRigidBody*)AddComponent(new CRigidBody);
	m_RigidBody->SetMode(RIGIDBODY_MODE::TOPVIEW);
	m_RigidBody->SetMass(1.f);

	m_HitBox = new CCollider;
	m_HitBox->SetName(L"HitBox_01");
	m_HitBox->SetScale(GetScale());
	m_HitBox->SetOffset(Vec2(0.f, 5.f));
	m_HitBox->SetRigidBody(m_RigidBody);
	AddComponent(m_HitBox);
}

CPlayer::~CPlayer()
{	
}

void CPlayer::Begin()
{

	m_FlipbookPlayer->Play(m_animState.idx, 5.f, true, m_animState.mirror);
	CCamera::GetInst()->SetTarget(this);


}

void CPlayer::Tick()
{
	// update gun direction
	Vec2 mousePos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());
	m_gunDir = mousePos - GetPos();
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

	//// check if collided with wall
	//if (m_normal.x * m_moveDir.x < 0) // if normal and move direction is "not" the same
	//{
	//	m_moveDir.x = 0.f;
	//}
	//if (m_normal.y * m_moveDir.y < 0)
	//{
	//	m_moveDir.y = 0.f;
	//}

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
	case PLAYER_STATE::IDLE:
		IdleState();
		break;
	case PLAYER_STATE::MOVING:
		MoveState();
		break;
	case PLAYER_STATE::ROLLING:
		RollState();
		break;
	case PLAYER_STATE::DEAD:
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
	case PLAYER_STATE::IDLE:
		penType = PEN_TYPE::GREEN;
		break;
	case PLAYER_STATE::MOVING:
		penType = PEN_TYPE::BLUE;
		break;
	case PLAYER_STATE::ROLLING:
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
	if (m_gun != nullptr && m_gun->GetHandSprite() == nullptr)
	{
		m_gun->SetHandSprite(CAssetMgr::GetInst()->LoadSprite(L"rogue_hand_001", L"Sprite\\SpaceRogue\\rogue_hand\\rogue_hand_001.sprite"));
	}

	m_FlipbookPlayer->Render();
}

void CPlayer::BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
	if (_OtherObject->GetLayerType() == LAYER_TYPE::MONSTER ||
		_OtherObject->GetLayerType() == LAYER_TYPE::MONSTER_OBJECT)
	{
		if (m_isInvincible)
			return;

		m_curHP--;
		CCamera::GetInst()->PostProcessEffect(POST_PROCESS::HEART, 0.7f);
		if (m_curHP == 0)
			m_state = PLAYER_STATE::DEAD;
		m_isInvincible = true;
	}
}

void CPlayer::Overlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
	//if (_OtherObject->GetLayerType() == LAYER_TYPE::TILE)
	//{
	//	auto normal = _Collider->CalCulateNormal(_OtherCollider);

	//	if (abs(normal.x) > 0) m_normal.x = normal.x;
	//	else m_normal.y = normal.y;
	//}
}

void CPlayer::EndOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
	//if (_OtherObject->GetLayerType() == LAYER_TYPE::TILE)
	//{
	//	m_normal = Vec2(0.f, 0.f);
	//}
}

void CPlayer::CreatePlayerFlipbook()
{
	// FlipbookPlayer 컴포넌트 추가하기
	m_FlipbookPlayer = (CFlipbookPlayer*)AddComponent(new CFlipbookPlayer);
	
	m_FlipbookPlayer->AddFlipbook(ROGUE_IDLE,					CAssetMgr::GetInst()->LoadFlipbook(L"rogue_idle" ,					L"Flipbook\\SpaceRogue\\rogue_idle.flip" ));
	m_FlipbookPlayer->AddFlipbook(ROGUE_IDLE_BACK,				CAssetMgr::GetInst()->LoadFlipbook(L"rogue_idle_back",				L"Flipbook\\SpaceRogue\\rogue_idle_back.flip" ));
	m_FlipbookPlayer->AddFlipbook(ROGUE_IDLE_BACKWARDS,			CAssetMgr::GetInst()->LoadFlipbook(L"rogue_idle_backwards",			L"Flipbook\\SpaceRogue\\rogue_idle_backwards.flip"   ));
	m_FlipbookPlayer->AddFlipbook(ROGUE_IDLE_BACKWARDS_HANDS2,	CAssetMgr::GetInst()->LoadFlipbook(L"rogue_idle_backwards_hands2",  L"Flipbook\\SpaceRogue\\rogue_idle_backwards_hands2.flip" ));
	m_FlipbookPlayer->AddFlipbook(ROGUE_IDLE_BACK_HANDS,		CAssetMgr::GetInst()->LoadFlipbook(L"rogue_idle_back_hands",		L"Flipbook\\SpaceRogue\\rogue_idle_back_hands.flip"));
	m_FlipbookPlayer->AddFlipbook(ROGUE_IDLE_BACK_HAND_LEFT,	CAssetMgr::GetInst()->LoadFlipbook(L"rogue_idle_back_hand_left",	L"Flipbook\\SpaceRogue\\rogue_idle_back_hand_left.flip"));
	m_FlipbookPlayer->AddFlipbook(ROGUE_IDLE_BACK_HAND_RIGHT,	CAssetMgr::GetInst()->LoadFlipbook(L"rogue_idle_back_hand_right",	L"Flipbook\\SpaceRogue\\rogue_idle_back_hand_right.flip"));
	m_FlipbookPlayer->AddFlipbook(ROGUE_IDLE_FRONT,				CAssetMgr::GetInst()->LoadFlipbook(L"rogue_idle_front",				L"Flipbook\\SpaceRogue\\rogue_idle_front.flip"));
	m_FlipbookPlayer->AddFlipbook(ROGUE_IDLE_FRONT_HANDS,		CAssetMgr::GetInst()->LoadFlipbook(L"rogue_idle_front_hands",		L"Flipbook\\SpaceRogue\\rogue_idle_front_hands.flip"));
	m_FlipbookPlayer->AddFlipbook(ROGUE_IDLE_FRONT_HAND_LEFT,	CAssetMgr::GetInst()->LoadFlipbook(L"rogue_idle_front_hand_left",	L"Flipbook\\SpaceRogue\\rogue_idle_front_hand_left.flip"));
	m_FlipbookPlayer->AddFlipbook(ROGUE_IDLE_FRONT_HAND_RIGHT,	CAssetMgr::GetInst()->LoadFlipbook(L"rogue_idle_front_hand_right",	L"Flipbook\\SpaceRogue\\rogue_idle_front_hand_right.flip"));
	m_FlipbookPlayer->AddFlipbook(ROGUE_IDLE_HANDS,				CAssetMgr::GetInst()->LoadFlipbook(L"rogue_idle_hands",				L"Flipbook\\SpaceRogue\\rogue_idle_hands.flip"));
	m_FlipbookPlayer->AddFlipbook(ROGUE_IDLE_HANDS2,			CAssetMgr::GetInst()->LoadFlipbook(L"rogue_idle_hands2",			L"Flipbook\\SpaceRogue\\rogue_idle_hands2.flip"));

	m_FlipbookPlayer->AddFlipbook(ROGUE_RUN_FRONT,				CAssetMgr::GetInst()->LoadFlipbook(L"rogue_run_front",				L"Flipbook\\SpaceRogue\\rogue_run_front.flip"));
	m_FlipbookPlayer->AddFlipbook(ROGUE_RUN_FRONT_HANDS,		CAssetMgr::GetInst()->LoadFlipbook(L"rogue_run_front_hands",		L"Flipbook\\SpaceRogue\\rogue_run_front_hands.flip"));
	m_FlipbookPlayer->AddFlipbook(ROGUE_RUN_FRONT_HANDS2,		CAssetMgr::GetInst()->LoadFlipbook(L"rogue_run_front_hands2",		L"Flipbook\\SpaceRogue\\rogue_run_front_hands2.flip"));
	m_FlipbookPlayer->AddFlipbook(ROGUE_RUN_FRONT_HANDS_LEFT,	CAssetMgr::GetInst()->LoadFlipbook(L"rogue_run_front_hands_left",	L"Flipbook\\SpaceRogue\\rogue_run_front_hands_left.flip"));
	m_FlipbookPlayer->AddFlipbook(ROGUE_RUN_BACK,				CAssetMgr::GetInst()->LoadFlipbook(L"rogue_run_back",				L"Flipbook\\SpaceRogue\\rogue_run_back.flip"));
	m_FlipbookPlayer->AddFlipbook(ROGUE_RUN_BACK_HANDS,			CAssetMgr::GetInst()->LoadFlipbook(L"rogue_run_back_hands",			L"Flipbook\\SpaceRogue\\rogue_run_back_hands.flip"));
	m_FlipbookPlayer->AddFlipbook(ROGUE_RUN_BACK_HANDS2,		CAssetMgr::GetInst()->LoadFlipbook(L"rogue_run_back_hands2",		L"Flipbook\\SpaceRogue\\rogue_run_back_hands2.flip"));
	m_FlipbookPlayer->AddFlipbook(ROGUE_RUN_BACK_HANDS_LEFT,	CAssetMgr::GetInst()->LoadFlipbook(L"rogue_run_back_hands_left",	L"Flipbook\\SpaceRogue\\rogue_run_back_hands_left.flip"));
	m_FlipbookPlayer->AddFlipbook(ROGUE_RUN_BACKWARD,			CAssetMgr::GetInst()->LoadFlipbook(L"rogue_run_backward",			L"Flipbook\\SpaceRogue\\rogue_run_backward.flip"));
	m_FlipbookPlayer->AddFlipbook(ROGUE_RUN_BACKWARD_HANDS2,	CAssetMgr::GetInst()->LoadFlipbook(L"rogue_run_backward_hands2",	L"Flipbook\\SpaceRogue\\rogue_run_backward_hands2.flip"));
	m_FlipbookPlayer->AddFlipbook(ROGUE_RUN_FORWARD,			CAssetMgr::GetInst()->LoadFlipbook(L"rogue_run_forward",			L"Flipbook\\SpaceRogue\\rogue_run_forward.flip"));
	m_FlipbookPlayer->AddFlipbook(ROGUE_RUN_FORWARD_HANDS,		CAssetMgr::GetInst()->LoadFlipbook(L"rogue_run_forward_hands",		L"Flipbook\\SpaceRogue\\rogue_run_forward_hands.flip"));
	m_FlipbookPlayer->AddFlipbook(ROGUE_RUN_FORWARD_HANDS2,		CAssetMgr::GetInst()->LoadFlipbook(L"rogue_run_forward_hands2",		L"Flipbook\\SpaceRogue\\rogue_run_forward_hands2.flip"));

	m_FlipbookPlayer->AddFlipbook(ROGUE_DODGE_BACK,      CAssetMgr::GetInst()->LoadFlipbook(L"rogue_dodge_back",      L"Flipbook\\SpaceRogue\\rogue_dodge_back.flip"));
	m_FlipbookPlayer->AddFlipbook(ROGUE_DODGE_FRONT,     CAssetMgr::GetInst()->LoadFlipbook(L"rogue_dodge_front",     L"Flipbook\\SpaceRogue\\rogue_dodge_front.flip"));
	m_FlipbookPlayer->AddFlipbook(ROGUE_DODGE_LEFT,		 CAssetMgr::GetInst()->LoadFlipbook(L"rogue_dodge_left",      L"Flipbook\\SpaceRogue\\rogue_dodge_left.flip"));
	m_FlipbookPlayer->AddFlipbook(ROGUE_DODGE_LEFT_BACK, CAssetMgr::GetInst()->LoadFlipbook(L"rogue_dodge_left_back", L"Flipbook\\SpaceRogue\\rogue_dodge_left_back.flip"));

	m_FlipbookPlayer->SetMagnification(3.f);
}

void CPlayer::CreateFlipbook(const wstring& _FlipbookName, CTexture* _Atlas, Vec2 _LeftTop, Vec2 _Slice, int MaxFrame)
{
	return;
}

void CPlayer::IdleState()
{
	if (m_moveDir.Length() > 0)
	{
		m_state = PLAYER_STATE::MOVING;
		return;
	}

	tAnimState animState = ProcessAnimState(m_gunDir, m_state);
	if (animState != m_animState)
	{
		m_animState = animState;
		m_FlipbookPlayer->Play(m_animState.idx, 10.f, true, m_animState.mirror);
	}
}

void CPlayer::MoveState()
{
	if (KEY_TAP(KEY::RBTN))
	{
		tAnimState animState = ProcessDodgeAnimState(m_moveDir);
		if (animState != m_animState)
		{
			m_animState = animState;
			m_FlipbookPlayer->Play(m_animState, 10.f, false);
		}
		CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER_OBJECT, false);
		m_state = PLAYER_STATE::ROLLING;
	}
	else if (m_moveDir.Length() > 0)
	{
		auto velocity = m_moveDir * m_moveSpeed;
		m_RigidBody->SetVelocity(velocity);
		auto animState = ProcessAnimState(m_gunDir, m_state);
		if (animState != m_animState)
		{
			m_animState = animState;
			m_FlipbookPlayer->Play(m_animState.idx, 10.f, true, m_animState.mirror);
		}
	}
	else
	{
		m_state = PLAYER_STATE::IDLE;
		m_RigidBody->SetVelocity(Vec2(0.f, 0.f));
	}
}

void CPlayer::RollState()
{
	m_rollAccTime += DT;
	if (m_rollAccTime < m_rollTime)
	{
		m_gun->SetVisible(false);
		float rollSpeed = m_rollSpeed;
		float ratio = m_rollAccTime / m_rollTime;
		rollSpeed *= ratio < 0.4f ? 1.0f : 0.3f;
		m_RigidBody->SetVelocity(m_moveDir * rollSpeed);
		// state 표시용
		DrawDebugRect(PEN_TYPE::RED, GetRenderPos() + Vec2(50.f, -50.f), Vec2(10.f, 10.f), 0.f);
		return;
	}

	m_rollAccTime = 0;
	m_gun->SetVisible(true);
	CCollisionMgr::GetInst()->CollisionCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER_OBJECT, true);
	if (m_moveDir.Length() > 0) {
		m_state = PLAYER_STATE::MOVING;
	}
	else
	{
		m_state = PLAYER_STATE::IDLE;
	}

}

void CPlayer::DeadState()
{
	ChangeLevel(LEVEL_TYPE::EDITOR);
}

void CPlayer::Reload(float _duration)
{
	m_reloadBar->Draw(_duration);
}

