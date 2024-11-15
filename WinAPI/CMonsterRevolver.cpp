#include "pch.h"
#include "CMonsterRevolver.h"
#include "CAssetMgr.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CFlipbookPlayer.h"
#include "CMonsterMissile.h"
#include "CTimeMgr.h"

Vec2 CMonsterRevolver::CalculateFireDirection()
{
	Vec2 playerPos = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(LAYER_TYPE::PLAYER, L"Player")->GetPos();
	Vec2 fireDirection = playerPos - m_owner->GetPos();
	fireDirection.Normalize();

	return fireDirection;
}

void CMonsterRevolver::CreateFlipbook()
{
	CGun::CreateFlipbook();

	m_flipbookPlayer->AddFlipbook(GUN_IDLE,   CAssetMgr::GetInst()->LoadFlipbook(L"bulletbro_revolver_green_idle", L"Flipbook\\Weapon\\bulletbro_revolver_green_idle.flip"));
	m_flipbookPlayer->AddFlipbook(GUN_CHARGE, CAssetMgr::GetInst()->LoadFlipbook(L"bulletbro_revolver_green_enemy_charge", L"Flipbook\\Weapon\\bulletbro_revolver_green_enemy_charge.flip"));
	m_flipbookPlayer->AddFlipbook(GUN_FIRE,   CAssetMgr::GetInst()->LoadFlipbook(L"bulletbro_revolver_green_fire", L"Flipbook\\Weapon\\bulletbro_revolver_green_fire.flip"));
}

void CMonsterRevolver::CreateBullet()
{
	CMonsterMissile* pMissile = new CMonsterMissile;
	pMissile->SetPos(m_muzzle);
	pMissile->SetScale(30.f, 30.f);
	pMissile->SetVelocity(m_gunDir * 500.f);
	CreateObject(pMissile, LAYER_TYPE::MONSTER_OBJECT);
}

GUN_STATE CMonsterRevolver::Fire()
{
	if (m_gunState != GUN_STATE::IDLE)
		return m_gunState;

	m_gunState = GUN_STATE::FIRING;

	// animate "CHARGE" before "FIRE"
	tAnimState state{ GUN_CHARGE, false };
	m_flipbookPlayer->Play(state, 10.f, false);

	return m_gunState;
}

void CMonsterRevolver::Begin()
{
	m_gunState = GUN_STATE::IDLE;
}

void CMonsterRevolver::Tick()
{
	switch (m_gunState)
	{
	case GUN_STATE::EMPTY:

	case GUN_STATE::FIRING:
		m_fireTime += DT;
		// if "charge" is finished
		if (m_flipbookPlayer->IsFlipbookMatch(GUN_CHARGE) && m_flipbookPlayer->IsFinish())
		{
			CreateBullet();
			m_flipbookPlayer->Play({ GUN_FIRE, false }, 15.f, false);
		}

		if (m_fireTime > m_fireDelay)
		{
			m_fireTime -= m_fireDelay;
			m_gunState = GUN_STATE::IDLE;
		}
		break;
	case GUN_STATE::GROUND:
		// do not update position
		return;
	case GUN_STATE::IDLE:
		if (nullptr != m_flipbookPlayer)
		{
			tAnimState state{ GUN_IDLE, false };
			m_flipbookPlayer->Play(state, 5.f, true);
		}
	default:
		break;
	}

	SetGunPos();
}

CMonsterRevolver::CMonsterRevolver()
{
	m_magnification = 2.f;
	m_fireDelay = 3.f;

	CreateFlipbook();
}

CMonsterRevolver::~CMonsterRevolver()
{
}
