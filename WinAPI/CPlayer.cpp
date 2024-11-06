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

/* TODO: change it to binary search tree???*/
tAnimState ProcessAnimState(const Vec2& _dir, const PLAYER_STATE _state)
{
	float angle = std::atan2f(-_dir.y, _dir.x) * (180.0 / PI);
	tAnimState state = { ROGUE_IDLE_FRONT_HANDS, false };
	if (0 < angle && angle <= 60.f)
	{
		state.mirror = false;
		switch (_state)
		{
		case PLAYER_STATE::MOVING:
			state.state = ROGUE_RUN_BACKWARD;
			break;
		case PLAYER_STATE::IDLE:
		default:
			state.state = ROGUE_IDLE_BACKWARDS;
			break;
		}
	}
	else if (60.f < angle && angle <= 90.f)
	{
		state.mirror = false;
		switch (_state)
		{
		case PLAYER_STATE::MOVING:
			state.state = ROGUE_RUN_BACKWARD;
			break;
		case PLAYER_STATE::IDLE:
		default:
			state.state = ROGUE_IDLE_BACK_HAND_LEFT;
			break;
		}
	}
	else if (90.f < angle && angle <= 120.f)
	{
		state.mirror = true;
		switch (_state)
		{
		case PLAYER_STATE::MOVING:
			state.state = ROGUE_RUN_BACKWARD;
			break;
		case PLAYER_STATE::IDLE:
		default:
			state.state = ROGUE_IDLE_BACK_HAND_RIGHT;
			break;
		}
	}
	else if (120.f < angle && angle <= 180.f)
	{
		state.mirror = true;
		switch (_state)
		{
		case PLAYER_STATE::MOVING:
			state.state = ROGUE_RUN_BACKWARD;
			break;
		case PLAYER_STATE::IDLE:
		default:
			state.state = ROGUE_IDLE;
			break;
		}
	}
	else if (-180.f < angle && angle <= -120.f)
	{
		state.mirror = true;
		switch (_state)
		{
		case PLAYER_STATE::MOVING:
			state.state = ROGUE_RUN_FORWARD;
			break;
		case PLAYER_STATE::IDLE:
		default:
			state.state = ROGUE_IDLE;
			break;
		}
	}
	else if (-120.f < angle && angle <= -90.f)
	{
		state.mirror = false;
		switch (_state)
		{
		case PLAYER_STATE::MOVING:
			state.state = ROGUE_RUN_FRONT_HANDS2;
			break;
		case PLAYER_STATE::IDLE:
		default:
			state.state = ROGUE_IDLE_FRONT_HAND_RIGHT;
			break;
		}
	}
	else if (-90.f < angle && angle <= -60.f)
	{
		state.mirror = false;
		switch (_state)
		{
		case PLAYER_STATE::MOVING:
			state.state = ROGUE_RUN_FRONT_HANDS_LEFT;
			break;
		case PLAYER_STATE::IDLE:
		default:
			state.state = ROGUE_IDLE_FRONT_HAND_LEFT;
			break;
		}
	}
	else /* -60.f < angle && angle <= -0.f */
	{
		state.mirror = false;
		switch (_state)
		{
		case PLAYER_STATE::MOVING:
			state.state = ROGUE_RUN_FORWARD;
			break;
		case PLAYER_STATE::IDLE:
		default:
			state.state = ROGUE_IDLE;
			break;
		}
	}

	//printf("x: %f, y: %f, angle: %.1f, state: %d, mirror: %s\n", _dir.x, _dir.y, angle, state.state, state.mirror ? "yes" : "no");

	return state;
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
	, m_animState({ ROGUE_IDLE, false })
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

	m_FlipbookPlayer->Play(m_animState.state, 5.f, true, m_animState.mirror);
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
			m_state = PLAYER_STATE::DEAD;
		m_isInvincible = true;
	}
	else if (_OtherObject->GetLayerType() == LAYER_TYPE::MONSTER_OBJECT)
	{
		if (m_isInvincible || IsRollState(m_state))
			return;

		m_curHP--;
		if (m_curHP == 0)
			m_state = PLAYER_STATE::DEAD;
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
		m_FlipbookPlayer->Play(m_animState.state, 10.f, true, m_animState.mirror);
	}
}

void CPlayer::MoveState()
{
	if (KEY_TAP(KEY::RBTN))
	{
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
			m_FlipbookPlayer->Play(m_animState.state, 10.f, true, m_animState.mirror);
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

