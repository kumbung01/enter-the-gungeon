#include "pch.h"
#include "CRoom1.h"
#include "CAssetMgr.h"
#include "CTexture.h"
#include "CTileMap.h"
#include "CCollider.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CMonster.h"
#include "CMonsterRevolver.h"
#include "CMonsterShotgun.h"
#include "CWall.h"
#include "CTimeMgr.h"

void CRoom1::CreateMap(int row, int col)
{
	float mag = 2.5f;
	float modifier = TILE_SIZE * mag;
	float wallSize = 20.f;

	int doorPos = 2;
	int doorSize = 3;

	CreateTileMap(row, col);
#if 0
	m_TileMap = (CTileMap*)AddComponent(new CTileMap);
	m_TileMap->SetRowCol(row, col);
	m_TileMap->SetMagnification(mag);
	m_TileMap->SetAtlasTexture(CAssetMgr::GetInst()->LoadTexture(L"TileMapAtlas", L"Texture\\CastleTile.png"));
#endif
	m_SpawnZone = (CCollider*)AddComponent(new CCollider);
	m_SpawnZone->SetScale(GetScale() * 0.5f);

	CLevel* level = CLevelMgr::GetInst()->GetCurrentLevel();

	// left wall
	CWall* wall = new CWall(row, 1);
	wall->SetPos(GetPos() + Vec2{ -((col - 1) * modifier / 2.f), 0.f });
	level->AddObject(wall, LAYER_TYPE::WALL);

	// right wall
	wall = new CWall(row, 1);
	wall->SetPos(GetPos() + Vec2{ (col - 1) * modifier / 2.f, 0.f });
	level->AddObject(wall, LAYER_TYPE::WALL);

	// upper wall
	wall = new CWall(3, doorPos);
	float leftX = (-col + doorPos) * modifier / 2.f;
	wall->SetPos(GetPos() + Vec2{ leftX, -(row * modifier / 2.f) });
	level->AddObject(wall, LAYER_TYPE::WALL);

	wall = new CWall(3, (col - doorPos - doorSize));
	leftX = (doorPos + doorSize) * modifier / 2.f;
	wall->SetPos(GetPos() + Vec2{ leftX, -(row * modifier / 2.f) });
	level->AddObject(wall, LAYER_TYPE::WALL);

	// lower wall
	wall = new CWall(3, col);
	wall->SetPos(GetPos() + Vec2{ 0.f, (row * modifier / 2.f) });
	level->AddObject(wall, LAYER_TYPE::WALL);

	// column
	wall = new CWall(3, 5);
	wall->SetPos(GetPos());
	level->AddObject(wall, LAYER_TYPE::WALL);

	wall = new CWall(7, 1);
	wall->SetPos(GetPos() + Vec2{ -3,  0 } * modifier);
	level->AddObject(wall, LAYER_TYPE::WALL);

	wall = new CWall(7, 1);
	wall->SetPos(GetPos() + Vec2{  3,  0 } * modifier);
	level->AddObject(wall, LAYER_TYPE::WALL);
}

void SpawnMonster(Vec2 pos, int type)
{
	CLevel* level = CLevelMgr::GetInst()->GetCurrentLevel();

	switch (type)
	{
	case 1:
		{
			CMonster* pMonster = new CMonster;
			pMonster->SetName(L"Monster");
			pMonster->SetPos(pos + Vec2{ -100.f, -100.f });
			level->AddObject(pMonster, LAYER_TYPE::MONSTER);

			CGun* gun = new CMonsterShotgun;
			gun->SetOwner(pMonster);
			pMonster->SetGun(gun);
			gun->SetName(L"MonsterShotgun");
			level->AddObject(gun, LAYER_TYPE::GUN);
			gun->Begin();
			pMonster->Begin();
		}
		break;
	case 2:
		{
			CMonster* pMonster = new CMonster;
			pMonster->SetName(L"Monster");
			pMonster->SetPos(pos + Vec2{ -100.f, 100.f });
			level->AddObject(pMonster, LAYER_TYPE::MONSTER);

			CGun* gun = new CMonsterRevolver;
			gun->SetOwner(pMonster);
			pMonster->SetGun(gun);
			gun->SetName(L"MonsterRevolver");
			level->AddObject(gun, LAYER_TYPE::GUN);
			gun->Begin();
			pMonster->Begin();
		}
	}
}

void CRoom1::SpawnMonsters()
{
	SpawnMonster(GetPos() + Vec2{ -200.f, -200.f }, 1);
	SpawnMonster(GetPos() + Vec2{ -200.f,  200.f }, 1);
	SpawnMonster(GetPos() + Vec2{  200.f, -200.f }, 2);
	SpawnMonster(GetPos() + Vec2{  200.f,  200.f }, 2);
}

CRoom1::CRoom1()
{
	CreateMap(30, 30);
}

CRoom1::CRoom1(float x, float y)
	: m_SpawnZone(nullptr)
	, m_SpawnCount(3)
	, m_SpawnDelay(1.f)
	, m_SpawnAccTime(0.f)
{
	int row = 30;
	int col = 30;

	SetPos(x, y);
	SetScale(col * TILE_SIZE * 2.5f, row * TILE_SIZE * 2.5f);
	CreateMap(row, col);
}

CRoom1::~CRoom1()
{
}

void CRoom1::Tick()
{
	if (m_SpawnZone->IsActive())
		return;

	if (CLevelMgr::GetInst()->GetCurrentLevel()->GetObjCount(LAYER_TYPE::MONSTER) > 0)
		return;

	if (m_SpawnCount == 0)
		return;

	m_SpawnAccTime += DT;

	if (m_SpawnAccTime >= m_SpawnDelay)
	{
		m_SpawnAccTime = 0.f;
		m_SpawnCount--;
		SpawnMonsters();
	}
}

void CRoom1::BeginOverlap(CCollider* _Collider, CObj* _OtherObject, CCollider* _OtherCollider)
{
	if (_OtherObject->GetLayerType() == LAYER_TYPE::PLAYER)
	{
		SpawnMonsters();
		m_SpawnCount--;
		_Collider->SetActive(false);
	}

}
