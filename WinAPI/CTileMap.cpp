#include "pch.h"
#include "CTileMap.h"

#include "CEngine.h"
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
	if (nullptr == m_Atlas)
		return;

	Vec2 OwnerPos = GetOwner()->GetRenderPos();
	HDC dc = CEngine::GetInst()->GetSecondDC();

	// N 번 인덱스 타일 이미지를 모든 타일칸에 렌더링한다.
	int ImgIdx = 47;
	int ImgRow = ImgIdx / m_AtlasTileCol; //  1 행
	int ImgCol = ImgIdx % m_AtlasTileCol; //   6 열

	if (ImgIdx < 0 || m_AtlasTileCol * m_AtlasTileRow <= ImgIdx)
		return;

	for (int Row = 0; Row < m_Row; ++Row)
	{
		for (int Col = 0; Col < m_Col; ++Col)
		{
			BitBlt(dc
				 , (int)OwnerPos.x + Col * TILE_SIZE
				 , (int)OwnerPos.y + Row * TILE_SIZE
				 , TILE_SIZE, TILE_SIZE
				 , m_Atlas->GetDC()
				 , ImgCol * TILE_SIZE, ImgRow * TILE_SIZE
				 , SRCCOPY); 
		}
	}
}

void CTileMap::SetRowCol(int Row, int Col)
{
	m_Row = Row;
	m_Col = Col;

	if(m_vecTileInfo.size() < m_Row * m_Col)
		m_vecTileInfo.resize(m_Row * m_Col);

	for (int i = 0; i < m_Row * m_Col; ++i)
	{
		m_vecTileInfo[i].ImgIdx = 1;
	}	
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
