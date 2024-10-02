#include "pch.h"
#include "CTileMap.h"

#include "CEngine.h"
#include "CTexture.h"

#include "CCamera.h"

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

	Vec2 OwnerRenderPos = GetOwner()->GetRenderPos();
	HDC dc = CEngine::GetInst()->GetSecondDC();

	// 카메라 영역 안에 들어오는 행, 열을 계산하기
	Vec2 vCamLook = CCamera::GetInst()->GetLookAt();
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	Vec2 vCamLeftTop = vCamLook - (vResolution / 2.f);
	Vec2 vCamRightBot = vCamLook + (vResolution / 2.f);

	Vec2 vOwnerPos = GetOwner()->GetPos();
	vCamLeftTop = vCamLeftTop - vOwnerPos;

	int LeftTopCol = vCamLeftTop.x / TILE_SIZE;
	int LeftTopRow = vCamLeftTop.y / TILE_SIZE;

	if (LeftTopCol < 0)
		LeftTopCol = 0;
	if(LeftTopRow < 0)
		LeftTopRow = 0;

	vCamRightBot = vCamRightBot - vOwnerPos;
	int RightBotCol = (vCamRightBot.x / TILE_SIZE) + 1;
	int RightBotRow = (vCamRightBot.y / TILE_SIZE) + 1;

	if (m_Col < RightBotCol)
		RightBotCol = m_Col;
	if (m_Row < RightBotRow)
		RightBotRow = m_Row;

	for (int Row = LeftTopRow; Row < RightBotRow; ++Row)
	{
		for (int Col = LeftTopCol; Col < RightBotCol; ++Col)
		{
			// 반복문 회차에 맞는 행렬에 대해서 이게 몇번째 타일정보인지 1차원 인덱스로 변환
			// 해당 타일정보에 접근한다.
			int TileIdx = m_Col * Row + Col;
			int ImgIdx = m_vecTileInfo[TileIdx].ImgIdx;

			// 해당 타일의 ImgIdx 가 -1 인 경우, Blank Tile
			if (ImgIdx == -1)
				continue;

			int ImgRow = ImgIdx / m_AtlasTileCol; //  1 행
			int ImgCol = ImgIdx % m_AtlasTileCol; //   6 열

			assert(!(ImgIdx < 0 || m_AtlasTileCol * m_AtlasTileRow <= ImgIdx));

			BitBlt(dc
				 , (int)OwnerRenderPos.x + Col * TILE_SIZE
				 , (int)OwnerRenderPos.y + Row * TILE_SIZE
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

	for (int i = 0; i < m_vecTileInfo.size(); ++i)
		m_vecTileInfo[i].ImgIdx = 1;
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
