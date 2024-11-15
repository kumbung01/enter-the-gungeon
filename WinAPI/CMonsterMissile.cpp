#include "pch.h"
#include "CMonsterMissile.h"
#include "CAssetMgr.h"

CMonsterMissile::CMonsterMissile()
{
	CMonsterMissile::CreateSprite();
}

CMonsterMissile::~CMonsterMissile()
{
}

void CMonsterMissile::CreateSprite()
{
	m_sprite = CAssetMgr::GetInst()->LoadSprite(L"8x8_enemy_projectile_001", L"Sprite\\EnemyProjectile\\8x8_enemy_projectile\\8x8_enemy_projectile_001.sprite");
}
