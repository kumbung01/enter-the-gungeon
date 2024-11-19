#include "pch.h"
#include "CMonster.h"
#include "CMissile.h"

#include "CEngine.h"
#include "CTimeMgr.h"
#include "CCollider.h"
#include "CFlipbookPlayer.h"
#include "CRigidBody.h"

#include "CAssetMgr.h"
#include "CTexture.h"
#include "CGun.h"
#include "CFSM.h"

#include "CIdleState.h"
#include "CTraceState.h"
#include "CSurpriseState.h"
#include "CHitState.h"
#include "CDieState.h"
#include "CDeadState.h"

CMonster::CMonster()
	: m_Collider(nullptr)
	, m_FSM(nullptr)
{

	// 몬스터 스탯
	m_Info.MaxHP = 25.f;
	m_Info.CurHP = 25.f;
	m_Info.AttRange = 300.f;
	m_Info.DetectRange = 500.f;
	m_Info.Speed = 100.f;
	m_Info.AttDelay = 1.f;

	// FSM 컴포넌트 추가
	m_FSM = (CFSM*)AddComponent(new CFSM);

	// FSM 에 상태 추가
	m_FSM->AddState(L"Idle", new CIdleState);
	m_FSM->AddState(L"Trace", new CTraceState);
	m_FSM->AddState(L"Surprise", new CSurpriseState);
	m_FSM->AddState(L"Hit", new CHitState);
	m_FSM->AddState(L"Die", new CDieState);
	m_FSM->AddState(L"Dead", new CDeadState);

	m_rigidBody = (CRigidBody*)AddComponent(new CRigidBody);
	m_rigidBody->SetMode(RIGIDBODY_MODE::TOPVIEW);
	m_rigidBody->SetMass(1.f);
	//m_rigidBody->SetFriction(10000.f);

	// Collider 컴포넌트 추가
	m_Collider = (CCollider*)AddComponent(new CCollider);
	m_Collider->SetScale(Vec2(45.f, 75.f));
	m_Collider->SetRigidBody(m_rigidBody);

	CreateFlipbook();
}

CMonster::~CMonster()
{
	DeleteObject(m_gun);
}

void CMonster::SetVelocity(Vec2 _velocity)
{
	m_rigidBody->SetVelocity(_velocity);
}

void CMonster::Begin()
{
	m_FSM->ChangeState(L"Idle");

	// 레벨이 시작할때 초기 위치값 기록
	m_InitPos = GetPos();
}

void CMonster::Tick()
{

}

void CMonster::Render()
{
	m_flipbookPlayer->Render();

	if (m_gun != nullptr && m_gun->GetHandSprite() == nullptr)
	{
		m_gun->SetHandSprite(CAssetMgr::GetInst()->LoadSprite(L"bullet_hand_001", L"Sprite\\BulletMan\\bullet_hand\\bullet_hand_001.sprite"));
	}
}

void CMonster::BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
	if (_OtherObject->GetLayerType() == LAYER_TYPE::PLAYER_OBJECT)
	{
		if (!IsDead())
		{
			auto pMissile = (CMissile*)_OtherObject;
			m_Info.CurHP -= pMissile->GetDamage();

			Vec2 missileDir = pMissile->GetVelocity();
			missileDir.Normalize();
			Vec2 force = missileDir * pMissile->GetKnockBack();

			m_rigidBody->SetVelocity(force);
			m_FSM->ChangeState(L"Hit");
		}
	}
}

void CMonster::Overlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
}

void CMonster::EndOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
}

void CMonster::CreateFlipbook()
{
	m_flipbookPlayer = (CFlipbookPlayer*)AddComponent(new CFlipbookPlayer);

	m_flipbookPlayer->AddFlipbook(BULLET_COVER_LEFT_IDLE, CAssetMgr::GetInst()->LoadFlipbook(L"bullet_cover_left_idle", L"Flipbook\\BulletMan\\bullet_cover_left_idle.flip"));
	m_flipbookPlayer->AddFlipbook(BULLET_COVER_LEFT_LEAP, CAssetMgr::GetInst()->LoadFlipbook(L"bullet_cover_left_leap", L"Flipbook\\BulletMan\\bullet_cover_left_leap.flip"));
	m_flipbookPlayer->AddFlipbook(BULLET_COVER_RIGHT_IDLE, CAssetMgr::GetInst()->LoadFlipbook(L"bullet_cover_right_idle", L"Flipbook\\BulletMan\\bullet_cover_right_idle.flip"));
	m_flipbookPlayer->AddFlipbook(BULLET_COVER_RIGHT_LEAP, CAssetMgr::GetInst()->LoadFlipbook(L"bullet_cover_right_leap", L"Flipbook\\BulletMan\\bullet_cover_right_leap.flip"));
	m_flipbookPlayer->AddFlipbook(BULLET_DEATH_BACK_SOUTH, CAssetMgr::GetInst()->LoadFlipbook(L"bullet_death_back_south", L"Flipbook\\BulletMan\\bullet_death_back_south.flip"));
	m_flipbookPlayer->AddFlipbook(BULLET_DEATH_FRONT_NORTH, CAssetMgr::GetInst()->LoadFlipbook(L"bullet_death_front_north", L"Flipbook\\BulletMan\\bullet_death_front_north.flip"));
	m_flipbookPlayer->AddFlipbook(BULLET_DEATH_LEFT_BACK, CAssetMgr::GetInst()->LoadFlipbook(L"bullet_death_left_back", L"Flipbook\\BulletMan\\bullet_death_left_back.flip"));
	m_flipbookPlayer->AddFlipbook(BULLET_DEATH_LEFT_FRONT, CAssetMgr::GetInst()->LoadFlipbook(L"bullet_death_left_front", L"Flipbook\\BulletMan\\bullet_death_left_front.flip"));
	m_flipbookPlayer->AddFlipbook(BULLET_DEATH_LEFT_SIDE, CAssetMgr::GetInst()->LoadFlipbook(L"bullet_death_left_side", L"Flipbook\\BulletMan\\bullet_death_left_side.flip"));
	m_flipbookPlayer->AddFlipbook(BULLET_DEATH_RIGHT_BACK, CAssetMgr::GetInst()->LoadFlipbook(L"bullet_death_right_back", L"Flipbook\\BulletMan\\bullet_death_right_back.flip"));
	m_flipbookPlayer->AddFlipbook(BULLET_DEATH_RIGHT_FRONT, CAssetMgr::GetInst()->LoadFlipbook(L"bullet_death_right_front", L"Flipbook\\BulletMan\\bullet_death_right_front.flip"));
	m_flipbookPlayer->AddFlipbook(BULLET_DEATH_RIGHT_SIDE, CAssetMgr::GetInst()->LoadFlipbook(L"bullet_death_right_side", L"Flipbook\\BulletMan\\bullet_death_right_side.flip"));
	m_flipbookPlayer->AddFlipbook(BULLET_DIE_LEFT, CAssetMgr::GetInst()->LoadFlipbook(L"bullet_die_left", L"Flipbook\\BulletMan\\bullet_die_left.flip"));
	m_flipbookPlayer->AddFlipbook(BULLET_DIE_LEFT_BACK, CAssetMgr::GetInst()->LoadFlipbook(L"bullet_die_left_back", L"Flipbook\\BulletMan\\bullet_die_left_back.flip"));
	m_flipbookPlayer->AddFlipbook(BULLET_DIE_RIGHT, CAssetMgr::GetInst()->LoadFlipbook(L"bullet_die_right", L"Flipbook\\BulletMan\\bullet_die_right.flip"));
	m_flipbookPlayer->AddFlipbook(BULLET_DIE_RIGHT_BACK, CAssetMgr::GetInst()->LoadFlipbook(L"bullet_die_right_back", L"Flipbook\\BulletMan\\bullet_die_right_back.flip"));
	m_flipbookPlayer->AddFlipbook(BULLET_HIT_BACK_LEFT, CAssetMgr::GetInst()->LoadFlipbook(L"bullet_hit_back_left", L"Flipbook\\BulletMan\\bullet_hit_back_left.flip"));
	m_flipbookPlayer->AddFlipbook(BULLET_HIT_BACK_RIGHT, CAssetMgr::GetInst()->LoadFlipbook(L"bullet_hit_back_right", L"Flipbook\\BulletMan\\bullet_hit_back_right.flip"));
	m_flipbookPlayer->AddFlipbook(BULLET_HIT_LEFT, CAssetMgr::GetInst()->LoadFlipbook(L"bullet_hit_left", L"Flipbook\\BulletMan\\bullet_hit_left.flip"));
	m_flipbookPlayer->AddFlipbook(BULLET_HIT_RIGHT, CAssetMgr::GetInst()->LoadFlipbook(L"bullet_hit_right", L"Flipbook\\BulletMan\\bullet_hit_right.flip"));
	m_flipbookPlayer->AddFlipbook(BULLET_IDLE_BACK, CAssetMgr::GetInst()->LoadFlipbook(L"bullet_idle_back", L"Flipbook\\BulletMan\\bullet_idle_back.flip"));
	m_flipbookPlayer->AddFlipbook(BULLET_IDLE_LEFT, CAssetMgr::GetInst()->LoadFlipbook(L"bullet_idle_left", L"Flipbook\\BulletMan\\bullet_idle_left.flip"));
	m_flipbookPlayer->AddFlipbook(BULLET_IDLE_RIGHT, CAssetMgr::GetInst()->LoadFlipbook(L"bullet_idle_right", L"Flipbook\\BulletMan\\bullet_idle_right.flip"));
	m_flipbookPlayer->AddFlipbook(BULLET_PITFALL_RIGHT, CAssetMgr::GetInst()->LoadFlipbook(L"bullet_pitfall_right", L"Flipbook\\BulletMan\\bullet_pitfall_right.flip"));
	m_flipbookPlayer->AddFlipbook(BULLET_RUN_LEFT, CAssetMgr::GetInst()->LoadFlipbook(L"bullet_run_left", L"Flipbook\\BulletMan\\bullet_run_left.flip"));
	m_flipbookPlayer->AddFlipbook(BULLET_RUN_LEFT_BACK, CAssetMgr::GetInst()->LoadFlipbook(L"bullet_run_left_back", L"Flipbook\\BulletMan\\bullet_run_left_back.flip"));
	m_flipbookPlayer->AddFlipbook(BULLET_RUN_RIGHT, CAssetMgr::GetInst()->LoadFlipbook(L"bullet_run_right", L"Flipbook\\BulletMan\\bullet_run_right.flip"));
	m_flipbookPlayer->AddFlipbook(BULLET_RUN_RIGHT_BACK, CAssetMgr::GetInst()->LoadFlipbook(L"bullet_run_right_back", L"Flipbook\\BulletMan\\bullet_run_right_back.flip"));
	m_flipbookPlayer->AddFlipbook(BULLET_SHOOTING_LEFT, CAssetMgr::GetInst()->LoadFlipbook(L"bullet_shooting_left", L"Flipbook\\BulletMan\\bullet_shooting_left.flip"));
	m_flipbookPlayer->AddFlipbook(BULLET_SHOOTING_RIGHT, CAssetMgr::GetInst()->LoadFlipbook(L"bullet_shooting_right", L"Flipbook\\BulletMan\\bullet_shooting_right.flip"));
	m_flipbookPlayer->AddFlipbook(BULLET_SPAWN, CAssetMgr::GetInst()->LoadFlipbook(L"bullet_spawn", L"Flipbook\\BulletMan\\bullet_spawn.flip"));
	m_flipbookPlayer->AddFlipbook(BULLET_SURPRISE_LEFT, CAssetMgr::GetInst()->LoadFlipbook(L"bullet_surprise_left", L"Flipbook\\BulletMan\\bullet_surprise_left.flip"));
	m_flipbookPlayer->AddFlipbook(BULLET_SURPRISE_RIGHT, CAssetMgr::GetInst()->LoadFlipbook(L"bullet_surprise_right", L"Flipbook\\BulletMan\\bullet_surprise_right.flip"));

	m_flipbookPlayer->SetMagnification(3.f);
}
