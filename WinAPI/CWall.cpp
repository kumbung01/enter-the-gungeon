#include "pch.h"
#include "CWall.h"
#include "CCollider.h"
#include "CTileMap.h"
#include "CAssetMgr.h"

void CWall::LoadTileMap(wstring _FullPath)
{
	m_TileMap->LoadTileMap(_FullPath);
}

void CWall::SaveTileMap(wstring _FullPath)
{
	m_TileMap->SaveTileMap(_FullPath);
}

void CWall::SetTileImgIdx(int row, int col, int idx)
{
	m_TileMap->SetTileImgIdx(row, col, idx);
}

void CWall::Tick()
{
}

void CWall::Render()
{
	if (!m_TileMap)
		return;

	m_TileMap->Render();
}

CWall::CWall(int row, int col)
	: m_TileMap(nullptr)
{
	float modifier = TILE_SIZE * 2.5f;

	Vec2 scale = Vec2{ col, row } * modifier;
	SetScale(scale);
	CCollider* collider = (CCollider*)AddComponent(new CCollider);
	collider->SetRigid(true);
	collider->SetScale({scale.x, scale.y - modifier});

	m_TileMap = (CTileMap*)AddComponent(new CTileMap);
	m_TileMap->SetRowCol(row, col);
	m_TileMap->SetMagnification(2.5f);
	m_TileMap->SetAtlasTexture(CAssetMgr::GetInst()->LoadTexture(L"TileMapAtlas", L"Texture\\CastleTile.png"));

	bool isVertical = (row != 3);

	if (isVertical)
	{
		m_TileMap->SetTileImgIdx(0, 0, TILE_WALL_ROOF_VERTICAL_TOP);

		for (int i = 1; i < row - 3; ++i)
		{
			m_TileMap->SetTileImgIdx(i, 0, TILE_WALL_ROOF_VERTICAL);
		}

		m_TileMap->SetTileImgIdx(row - 3, 0, TILE_WALL_ROOF_VERTICAL_BOTTOM);

		for (int i = row - 2; i < row; ++i)
		{
			m_TileMap->SetTileImgIdx(i, 0, TILE_WALL_SIDE);
		}
	}

	else
	{
		m_TileMap->SetTileImgIdx(0, 0, TILE_WALL_ROOF_HORIZONTAL_LEFT);

		for (int i = 1; i < col - 1; ++i)
		{
			m_TileMap->SetTileImgIdx(0, i, TILE_WALL_ROOF_HORIZONTAL);
		}

		m_TileMap->SetTileImgIdx(0, col - 1, TILE_WALL_ROOF_HORIZONTAL_RIGHT);

		for (int i = 0; i < col; ++i)
		{
			for (int j = 1; j < row; ++j)
			{
				m_TileMap->SetTileImgIdx(j, i, TILE_WALL_SIDE);
			}
		}
	}
}

CWall::~CWall()
{
}
