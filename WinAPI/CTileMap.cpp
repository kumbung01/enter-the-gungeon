#include "pch.h"
#include "CTileMap.h"

#include "CKeyMgr.h"

#include "CEngine.h"
#include "CTexture.h"

#include "CCamera.h"

#include "CPathMgr.h"


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

	// ī�޶� ���� �ȿ� ������ ��, ���� ����ϱ�
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
			// �ݺ��� ȸ���� �´� ��Ŀ� ���ؼ� �̰� ���° Ÿ���������� 1���� �ε����� ��ȯ
			// �ش� Ÿ�������� �����Ѵ�.
			int TileIdx = m_Col * Row + Col;
			int ImgIdx = m_vecTileInfo[TileIdx].ImgIdx;

			// �ش� Ÿ���� ImgIdx �� -1 �� ���, Blank Tile
			if (ImgIdx == -1)
				continue;

			int ImgRow = ImgIdx / m_AtlasTileCol; //  1 ��
			int ImgCol = ImgIdx % m_AtlasTileCol; //   6 ��

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
}

void CTileMap::SetAtlasTexture(CTexture* _Atlas)
{
	m_Atlas = _Atlas;

	if (nullptr == m_Atlas)
		return;

	// ��Ʋ�� �ؽ��� ���� ��������
	m_AtlasResolution = Vec2((float)m_Atlas->GetWidth(), (float)m_Atlas->GetHeight());
	m_AtlasTileCol = m_AtlasResolution.x / TILE_SIZE;
	m_AtlasTileRow = m_AtlasResolution.y / TILE_SIZE;
}

tTile* CTileMap::GetTileInfo(Vec2 _MousePos)
{
	if (CKeyMgr::GetInst()->IsMouseOffScreen())
		return nullptr;

	_MousePos = CCamera::GetInst()->GetRealPos(_MousePos);
	Vec2 vOffset = _MousePos - GetOwner()->GetPos();

	// ���콺 ��ġ�� Ÿ�ϸ��� ������ Ÿ�� �߿��� ���� � ��ġ���� �˾Ƴ���.
	int Col = (int)vOffset.x / TILE_SIZE;
	int Row = (int)vOffset.y / TILE_SIZE;

	if (Col < 0 || Row < 0 || m_Col <= Col || m_Row <= Row)
		return nullptr;

	int idx = Row * m_Col + Col;
	return &m_vecTileInfo[idx];
}

bool CTileMap::SaveTileMap(wstring _FullPath)
{
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, _FullPath.c_str(), L"wb");
	assert(pFile);

	// Ÿ�� ��, �� ���� ����
	fwrite(&m_Col, sizeof(int), 1, pFile);
	fwrite(&m_Row, sizeof(int), 1, pFile);

	// �����ϴ� ��Ʋ�� �ؽ��� ����
	SaveAssetRef(m_Atlas, pFile);

	// ������ Ÿ���� ����ϴ� �̹��� �ε��� ����
	int TileCount = m_Col * m_Row;
	for (int i = 0; i < TileCount; ++i)
	{
		fwrite(&m_vecTileInfo[i], sizeof(tTile), 1, pFile);
	}	

	fclose(pFile);

	return true;
}

bool CTileMap::LoadTileMap(wstring _FullPath)
{
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, _FullPath.c_str(), L"rb");
	assert(pFile);

	// Ÿ�� ��, �� ���� ����
	fread(&m_Col, sizeof(int), 1, pFile);
	fread(&m_Row, sizeof(int), 1, pFile);
	SetRowCol(m_Row, m_Col);

	// �����ϴ� ��Ʋ�� �ؽ��� ����
	m_Atlas = (CTexture*)LoadAssetRef(pFile);
	SetAtlasTexture(m_Atlas);

	// ������ Ÿ���� ����ϴ� �̹��� �ε��� ����
	int TileCount = m_Col * m_Row;
	for (int i = 0; i < TileCount; ++i)
	{		
		fread(&m_vecTileInfo[i], sizeof(tTile), 1, pFile);
	}

	fclose(pFile);

	return true;
}
