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

enum PLAYER_ANIM_STATE
{
	IDLE_UP,
	IDLE_DOWN,
	IDLE_LEFT,
	IDLE_RIGHT,

	MOVE_UP,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT,	
};

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
	, m_state(PLAYER_STATE::IDLE)
	//, m_RigidBody(nullptr)
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
	//CreatePlayerFlipbook();

	//// RigidBody 컴포넌트 추가
	//m_RigidBody = (CRigidBody*)AddComponent(new CRigidBody);
	//m_RigidBody->SetMode(RIGIDBODY_MODE::BELTSCROLL);
	//m_RigidBody->SetInitialSpeed(100.f);
	//m_RigidBody->SetMaxSpeed(500.f);
	//m_RigidBody->SetMass(1.f);
	//m_RigidBody->SetFriction(700.f);
	//m_RigidBody->SetJumpVelocity(Vec2(0.f, -500.f));


}

CPlayer::~CPlayer()
{	
}

void CPlayer::Begin()
{

	//m_FlipbookPlayer->Play(IDLE_DOWN, 5.f, true);

	//CCamera::GetInst()->SetTarget(this);


}

void CPlayer::Tick()
{
	// update gun direction
	Vec2 mousePos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());
	m_gunDir = GetPos() - mousePos;
	m_gunDir.Normalize();

	// update move direction
	if (m_state != PLAYER_STATE::ROLLING)
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
	case PLAYER_STATE::MOVING:
		MoveState();
		break;
	case PLAYER_STATE::ROLLING:
		RollState();
		break;
	case PLAYER_STATE::DEAD:
		DeadState();
		break;
	case PLAYER_STATE::FALLING:
		break;
	case PLAYER_STATE::IDLE:
	default:
		IdleState();
		break;
	}

	// gun related
	if (m_gun != nullptr)
	{
		if (m_state != PLAYER_STATE::ROLLING)
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
	if (KEY_TAP(SPACE) && m_state != PLAYER_STATE::ROLLING)
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
	case PLAYER_STATE::MOVING:
		penType = PEN_TYPE::BLUE;
		break;
	case PLAYER_STATE::ROLLING:
		penType = PEN_TYPE::RED;
		break;
	case PLAYER_STATE::IDLE:
	default:
		penType = PEN_TYPE::GREEN;
	}

	DrawDebugRect(penType, GetRenderPos() + Vec2(50.f, -50.f), Vec2(10.f, 10.f), 0.f);
}

void CPlayer::Render()
{
	//m_FlipbookPlayer->Render();
}

void CPlayer::BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
	if (_OtherObject->GetName() == L"Monster")
	{
		if (m_isInvincible)
			return;

		m_curHP--;
		if (m_curHP == 0)
			m_state = PLAYER_STATE::DEAD;
		m_isInvincible = true;
	}
	else if (_OtherObject->GetLayerType() == LAYER_TYPE::MONSTER_OBJECT)
	{
		if (m_isInvincible || m_state == PLAYER_STATE::ROLLING)
			return;

		m_curHP--;
		if (m_curHP == 0)
			m_state = PLAYER_STATE::DEAD;
		m_isInvincible = true;
	}
}

void CPlayer::Overlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
}

void CPlayer::EndOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
}

void CPlayer::CreatePlayerFlipbook()
{
	return;
	// AtlasTexture
	CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(L"Link", L"Texture\\link_32.bmp");

	/*CreateFlipbook(L"LINK_IDLEDOWN", pAtlas, Vec2(0.f, 0.f), Vec2(120.f, 130.), 3);
	CreateFlipbook(L"LINK_IDLELEFT", pAtlas, Vec2(0.f, 130.f), Vec2(120.f, 130.), 3);
	CreateFlipbook(L"LINK_IDLEUP", pAtlas, Vec2(0.f, 260.f), Vec2(120.f, 130.), 1);
	CreateFlipbook(L"LINK_IDLERIGHT", pAtlas, Vec2(0.f, 390.f), Vec2(120.f, 130.), 3);
	CreateFlipbook(L"LINK_MOVEDOWN", pAtlas, Vec2(0.f, 520.f), Vec2(120.f, 130.), 10);
	CreateFlipbook(L"LINK_MOVELEFT", pAtlas, Vec2(0.f, 650.f), Vec2(120.f, 130.), 10);
	CreateFlipbook(L"LINK_MOVEUP", pAtlas, Vec2(0.f, 780.f), Vec2(120.f, 130.), 10);
	CreateFlipbook(L"LINK_MOVERIGHT", pAtlas, Vec2(0.f, 910.f), Vec2(120.f, 130.), 10);*/

	// FlipbookPlayer 컴포넌트 추가하기
	m_FlipbookPlayer = (CFlipbookPlayer*)AddComponent(new CFlipbookPlayer);
	
	m_FlipbookPlayer->AddFlipbook(IDLE_DOWN, CAssetMgr::GetInst()->LoadFlipbook(L"LINK_IDLEDOWN" , L"Flipbook\\LINK_IDLEDOWN.flip" ));
	m_FlipbookPlayer->AddFlipbook(IDLE_LEFT, CAssetMgr::GetInst()->LoadFlipbook(L"LINK_IDLELEFT",  L"Flipbook\\LINK_IDLELEFT.flip" ));
	m_FlipbookPlayer->AddFlipbook(IDLE_UP,	 CAssetMgr::GetInst()->LoadFlipbook(L"LINK_IDLEUP"	,  L"Flipbook\\LINK_IDLEUP.flip"   ));
	m_FlipbookPlayer->AddFlipbook(IDLE_RIGHT,CAssetMgr::GetInst()->LoadFlipbook(L"LINK_IDLERIGHT", L"Flipbook\\LINK_IDLERIGHT.flip" ));

	m_FlipbookPlayer->AddFlipbook(MOVE_DOWN, CAssetMgr::GetInst()->LoadFlipbook( L"LINK_MOVEDOWN"	,L"Flipbook\\LINK_MOVEDOWN.flip" ));
	m_FlipbookPlayer->AddFlipbook(MOVE_LEFT, CAssetMgr::GetInst()->LoadFlipbook( L"LINK_MOVELEFT"	,L"Flipbook\\LINK_MOVELEFT.flip" ));
	m_FlipbookPlayer->AddFlipbook(MOVE_UP, CAssetMgr::GetInst()->LoadFlipbook(   L"LINK_MOVEUP"		,L"Flipbook\\LINK_MOVEUP.flip"   ));
	m_FlipbookPlayer->AddFlipbook(MOVE_RIGHT, CAssetMgr::GetInst()->LoadFlipbook(L"LINK_MOVERIGHT"	,L"Flipbook\\LINK_MOVERIGHT.flip"));

	CSprite* pSprite = CAssetMgr::GetInst()->FindSprite(L"LINK_IDLERIGHT_1");
	pSprite->SetOffset(Vec2(1.f, 0.f));
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
		m_state = PLAYER_STATE::MOVING;
}

void CPlayer::MoveState()
{
	if (KEY_TAP(KEY::RBTN))
	{
		m_state = PLAYER_STATE::ROLLING;
	}
	else if (m_moveDir.Length() > 0)
	{
		SetPos(GetPos() + m_moveDir * m_moveSpeed * DT);
	}
	else
	{
		m_state = PLAYER_STATE::IDLE;
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
		SetPos(GetPos() + m_moveDir * rollSpeed * DT);
		// state 표시용
		DrawDebugRect(PEN_TYPE::RED, GetRenderPos() + Vec2(50.f, -50.f), Vec2(10.f, 10.f), 0.f);
		return;
	}

	m_rollAccTime = 0;
	m_state = PLAYER_STATE::MOVING;
}

void CPlayer::DeadState()
{
	ChangeLevel(LEVEL_TYPE::EDITOR);
}

void CPlayer::Reload(float _duration)
{
	m_reloadBar->Draw(_duration);
}

