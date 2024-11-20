#include "pch.h"
#include "CCorridor.h"
#include "CTileMap.h"
#include "CAssetMgr.h"
#include "CCollider.h"
#include "CLevelMgr.h"
#include "CWall.h"
#include "CLevel.h"

void CCorridor::CreateMap(int row, int col)
{
	float mag = 2.5f;
	float modifier = TILE_SIZE * mag;
	float wallSize = 20.f;

	CreateTileMap(row, col);

	CLevel* level = CLevelMgr::GetInst()->GetCurrentLevel();

	if (m_isVertical)
	{
		CWall* wall = new CWall(row, 1);
		wall->SetPos(GetPos() + Vec2{ -((col + 1) * modifier * 0.5f), 0.f});
		level->AddObject(wall, LAYER_TYPE::WALL);

		wall = new CWall(row, 1);
		wall->SetPos(GetPos() + Vec2{ (col + 1) * modifier * 0.5f, 0.f});
		level->AddObject(wall, LAYER_TYPE::WALL);
#if 0
		CCollider* collider = (CCollider*)AddComponent(new CCollider);
		collider->SetScale({ wallSize, row * modifier });
		collider->SetRigid(true);
		collider->SetOffset({ -(col * modifier / 2.f), 0.f });

		collider = (CCollider*)AddComponent(new CCollider);
		collider->SetScale({ wallSize, row * modifier });
		collider->SetRigid(true);
		collider->SetOffset({ (col * modifier / 2.f), 0.f });
#endif
	}
	else
	{
		CWall* wall = new CWall(3, col);
		wall->SetPos(GetPos() + Vec2{ 0.f, -((row + 1) * modifier * 0.5f) });
		level->AddObject(wall, LAYER_TYPE::WALL);

		wall = new CWall(3, col);
		wall->SetPos(GetPos() + Vec2{ 0.f, ((row + 1) * modifier * 0.5f) });
		level->AddObject(wall, LAYER_TYPE::WALL);
	}
}

CCorridor::CCorridor()
{
	CreateMap(5, 30);
}

CCorridor::CCorridor(float x, float y, int row, int col, bool isVertical)
	:m_isVertical(isVertical)
{
	SetPos(x, y);
	SetScale(col * TILE_SIZE * 2.5f, row * TILE_SIZE * 2.5f);
	CreateMap(row, col);
}

CCorridor::~CCorridor()
{
	
}
