#include "pch.h"
#include "CMap.h"
#include "CTileMap.h"
#include "CAssetMgr.h"


CMap::CMap()
	: m_TileMap(nullptr)
{
	
}

CMap::~CMap()
{
}

void CMap::CreateTileMap(int row, int col)
{
	m_TileMap = (CTileMap*)AddComponent(new CTileMap);
	m_TileMap->SetRowCol(row, col);
	m_TileMap->SetMagnification(2.5f);
	m_TileMap->SetAtlasTexture(CAssetMgr::GetInst()->LoadTexture(L"TileMapAtlas", L"Texture\\CastleTile.png"));

	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			m_TileMap->SetTileImgIdx(i, j, TILE_FLOOR);
		}
	}
}

void CMap::Tick()
{

}

void CMap::Render()
{
	if (m_TileMap)
		m_TileMap->Render();
}