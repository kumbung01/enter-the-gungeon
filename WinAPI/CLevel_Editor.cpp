#include "pch.h"
#include "CLevel_Editor.h"

#include "resource.h"

#include "CEngine.h"
#include "CKeyMgr.h"
#include "CMap.h"
#include "CTileMap.h"

#include "CLevelMgr.h"
#include "CCamera.h"

CLevel_Editor::CLevel_Editor()
	: m_MapObj(nullptr)
	, m_hMenu(nullptr)
{
}

CLevel_Editor::~CLevel_Editor()
{
}

void CLevel_Editor::Begin()
{
	// �޴��� �ε� �� ���� �����쿡 ����
	if (nullptr == m_hMenu)
	{
		m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_WINAPI));
	}	
	SetMenu(CEngine::GetInst()->GetMainWndHwnd(), m_hMenu);

	// �޴��ٰ� �߰��Ǿ��� ������, ������ ũ�⸦ �������Ѵ�.
	CEngine::GetInst()->ChangeWindowSize(CEngine::GetInst()->GetResolution());

	// ���ÿ� Map ������Ʈ ����
	m_MapObj = new CMap;
	AddObject(m_MapObj, LAYER_TYPE::TILE);

	// ���� �Ҽ� ��� ������Ʈ�� Begin �� ȣ����� �� �ֵ��� �Ѵ�
	CLevel::Begin();
}

void CLevel_Editor::End()
{
	DeleteAllObject();

	// �޴��� ����
	SetMenu(CEngine::GetInst()->GetMainWndHwnd(), nullptr);

	// �޴��� ���ŵǾ����Ƿ�, �ٽ� ������ ũ�� ����
	CEngine::GetInst()->ChangeWindowSize(CEngine::GetInst()->GetResolution());
}




void CLevel_Editor::Tick()
{
	CLevel::Tick();

	// Ư�� Ű�� ������ Start ������ ����
	if (KEY_TAP(KEY::ENTER))
	{
		Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
		ChangeLevel(LEVEL_TYPE::START);
	}

	// ���콺 Ŭ������ CMap ������Ʈ�� Ÿ�� �̹��� �ε��� ����
	// �Ϲ����� ������ : ���� ��ǥ -> Render ��ǥ ����
	// ���콺 ��ǥ : Render ��ǥ(���콺��ǥ) -> ���� ��ǥ�� ����
	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();	
		tTile* TileInfo = m_MapObj->GetTileMap()->GetTileInfo(vMousePos);

		if (nullptr != TileInfo)
		{
			TileInfo->ImgIdx = 20;
		}		
	}
}

void CLevel_Editor::Render()
{
	CLevel::Render();

	TextOut(CEngine::GetInst()->GetSecondDC(), 10, 10, L"Editor Level", wcslen(L"Editor Level"));
}









// ============================
// Tile_Map_Info Dialog ���ν���
// ============================
INT_PTR CALLBACK TileMapInfoProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			// ����Ʈ ��Ʈ�ѿ� �Է��� ���ڸ� �˾Ƴ�����
			int Row = GetDlgItemInt(hDlg, IDC_ROW, nullptr, true);
			int Col = GetDlgItemInt(hDlg, IDC_COL, nullptr, true);

			// CLevel_Editor �� �ִ� MapObject �� Ÿ�ϸ� ������Ʈ�� �� ���� �������־�� ��
			// ���� ������ �˾Ƴ���. ��Ȳ�� ���� ������ �ݵ�� CLevel_Editor ���� �Ѵ�.
			CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
			CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
			assert(pEditorLevel);

			// Editor ������ ������ ���� CMap ������Ʈ�� ������
			CMap* pMapObj = pEditorLevel->GetMapObject();

			// Ÿ�ϸ� ������Ʈ�� ��ġ�� ����Ʈ��Ʈ�ѿ� �Էµ� ���ڷ� ������
			CTileMap* pTileMap = pMapObj->GetComponent<CTileMap>();
			pTileMap->SetRowCol(Row, Col);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}

		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
		}


		break;
	}
	return (INT_PTR)FALSE;
}