#include "pch.h"
#include "CFlipbookPlayer.h"
#include "CAssetMgr.h"
#include "CMonsterShotgun.h"
#include "CMonsterMissile.h"



void CMonsterShotgun::CreateFlipbook()
{
	CGun::CreateFlipbook();

	m_flipbookPlayer->AddFlipbook(GUN_IDLE, CAssetMgr::GetInst()->LoadFlipbook(L"shotgun_idle", L"Flipbook\\Weapon\\shotgun_idle.flip"));
	m_flipbookPlayer->AddFlipbook(GUN_CHARGE, CAssetMgr::GetInst()->LoadFlipbook(L"shotgun_enemy_fire", L"Flipbook\\Weapon\\shotgun_enemy_fire.flip"));
	m_flipbookPlayer->AddFlipbook(GUN_FIRE, CAssetMgr::GetInst()->LoadFlipbook(L"shotgun_fire", L"Flipbook\\Weapon\\shotgun_fire.flip"));
	m_flipbookPlayer->SetAxis({ -5.f, 2.5f });
}


void CMonsterShotgun::CreateBullet()
{
	for (int i = -2; i < 2; ++i)
	{
		Vec2 gunDir = Rotate(m_gunDir, i * 0.1f);
		CMonsterMissile* pMissile = new CMonsterMissile;
		pMissile->SetPos(m_muzzle);
		pMissile->SetScale(30.f, 30.f);
		pMissile->SetVelocity(gunDir * 500.f);
		CreateCObject(pMissile, LAYER_TYPE::MONSTER_OBJECT);
	}
}


CMonsterShotgun::CMonsterShotgun()
{
	m_magnification = 3.f;
}

CMonsterShotgun::~CMonsterShotgun()
{
}
