#include "pch.h"
#include "CStartRoom.h"
#include "CTileMap.h"
#include "CCollider.h"
#include "CAssetMgr.h"
#include "CWall.h"
#include "CLevel.h"
#include "CLevelMgr.h"


void CStartRoom::CreateMap(int row, int col)
{
	float mag = 2.5f;
	float modifier = TILE_SIZE * mag;

	int doorPos = 15;
	int doorSize = 3;

	CreateTileMap(row, col);

	CLevel* level = CLevelMgr::GetInst()->GetCurrentLevel();

	// vertical walls
	CWall* wall = new CWall(row, 1);
	wall->SetPos(GetPos() + Vec2{ -((col - 1) * modifier * 0.5f), 0.f });
	level->AddObject(wall, LAYER_TYPE::WALL);

	wall = new CWall(row, 1);
	wall->SetPos(GetPos() + Vec2{ ((col - 1) * modifier * 0.5f), 0.f });
	level->AddObject(wall, LAYER_TYPE::WALL);

	// horizontal walls
	wall = new CWall(3, col);
	wall->SetPos(GetPos() + Vec2{ 0.f, -((row - 1) * modifier * 0.5f) });
	level->AddObject(wall, LAYER_TYPE::WALL);

	wall = new CWall(3, doorPos);
	float leftX = (-col + doorPos) * modifier / 2.f;
	wall->SetPos(GetPos() + Vec2{ leftX, ((row - 1) * modifier * 0.5f) });
	level->AddObject(wall, LAYER_TYPE::WALL);

	wall = new CWall(3, (col - doorPos - doorSize));
	leftX = (doorPos + doorSize) * modifier / 2.f;
	wall->SetPos(GetPos() + Vec2{ leftX, ((row - 1) * modifier * 0.5f) });
	level->AddObject(wall, LAYER_TYPE::WALL);
}

CStartRoom::CStartRoom()
{
	CreateMap(30, 30);
}

CStartRoom::CStartRoom(float x, float y)
{
	int row = 15;
	int col = 20;
	Vec2 scale = Vec2{ col, row } * TILE_SIZE * 2.5f;

	SetPos(x, y);
	SetScale(scale);
	CreateMap(row, col);
}

CStartRoom::~CStartRoom()
{
}
