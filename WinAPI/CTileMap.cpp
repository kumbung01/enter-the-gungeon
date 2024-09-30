#include "pch.h"
#include "CTileMap.h"

#include "CTexture.h"

CTileMap::CTileMap()
	: CComponent(COMPONENT_TYPE::TILEMAP)
	, m_Col(1)
	, m_Row(1)
	, m_Atlas(nullptr)
	, m_AtlasTileCol(0)
	, m_AtlasTileRow(0)	
{
}

CTileMap::~CTileMap()
{
}

void CTileMap::FinalTick()
{
	Vec2 OwnerPos = GetOwner()->GetRenderPos();

	for (int row = 0; row < m_Row + 1; ++row)
	{
		DrawDebugLine(PEN_TYPE::GREEN
			, OwnerPos + Vec2(0, TILE_SIZE * row)
			, OwnerPos + Vec2(m_Col * TILE_SIZE, TILE_SIZE * row), 0.f);
	}

	for (int col = 0; col < m_Col + 1; ++col)
	{
		DrawDebugLine(PEN_TYPE::GREEN
			, OwnerPos + Vec2(TILE_SIZE * col, 0)
			, OwnerPos + Vec2(TILE_SIZE * col, m_Row * TILE_SIZE), 0.f);
	}
	
}

void CTileMap::Render()
{

}

void CTileMap::SetAtlasTexture(CTexture* _Atlas)
{
	m_Atlas = _Atlas;

	if (nullptr == m_Atlas)
		return;

	// 아틀라스 텍스쳐 정보 가져오기
	m_AtlasResolution = Vec2((float)m_Atlas->GetWidth(), (float)m_Atlas->GetHeight());
	m_AtlasTileCol = m_AtlasResolution.x / TILE_SIZE;
	m_AtlasTileRow = m_AtlasResolution.y / TILE_SIZE;
}
