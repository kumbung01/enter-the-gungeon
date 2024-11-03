#include "pch.h"
#include "CLevel_Editor.h"

#include "resource.h"

#include "CEngine.h"
#include "CKeyMgr.h"
#include "CMap.h"
#include "CTileMap.h"
#include "CAtlas.h"

#include "CLevelMgr.h"
#include "CCamera.h"

#include "CPathMgr.h"
#include "CUI.h"
#include "CPanelUI.h"
#include "CBtnUI.h"

#include "CAssetMgr.h"
#include "CSound.h"


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
	// ����� ����
	//CSound* pSound = CAssetMgr::GetInst()->LoadSound(L"DM_Opening", L"Sound\\DM.wav");
	//if (nullptr != pSound)
	//{
	//	pSound->SetVolume(70.f);
	//	pSound->PlayToBGM(true);
	//}

	// �޴��� �ε� �� ���� �����쿡 ����
	if (nullptr == m_hMenu)
	{
		m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_WINAPI));
	}	
	SetMenu(CEngine::GetInst()->GetMainWndHwnd(), m_hMenu);

	// �޴��ٰ� �߰��Ǿ��� ������, ������ ũ�⸦ �������Ѵ�.
	CEngine::GetInst()->ChangeWindowSize(CEngine::GetInst()->GetResolution());

	Vec2 vResolution = CEngine::GetInst()->GetResolution();


	// PanelUI ����
	//CPanelUI* pPanel = new CPanelUI;
	//pPanel->SetName(L"Panel 1");
	//Vec2 vScale = Vec2(380.f, 500.f);

	//pPanel->SetPos(Vec2(vResolution.x - vScale.x - 10, 10.f));
	//pPanel->SetScale(vScale);

	//// Panel �� ���� �ڽ� UI
	//CBtnUI* pBtn = new CBtnUI;
	//pBtn->SetScale(Vec2(150.f, 100.f));
	//pBtn->SetPos(Vec2(10.f, 10.f));

	//void SaveTileMap();
	////pBtn->AddCallBack(&SaveTileMap);
	//pBtn->AddDelegate(this, (DELEGATE_0)&CLevel_Editor::SaveTileMap);

	//pPanel->AddChildUI(pBtn);
	//AddObject(pPanel, LAYER_TYPE::UI);

	//// PanelUI ����
	//pPanel = new CPanelUI;
	//pPanel->SetName(L"Panel 2");	

	//pPanel->SetPos(Vec2(vResolution.x - vScale.x - 10.f- 500.f, 10.f));
	//pPanel->SetScale(vScale);

	//// Panel �� ���� �ڽ� UI
	//pBtn = new CBtnUI;
	//pBtn->SetScale(Vec2(150.f, 100.f));
	//pBtn->SetPos(Vec2(10.f, 10.f));

	//void LoadTileMap();
	////pBtn->AddCallBack(&LoadTileMap);
	//pBtn->AddDelegate(this, (DELEGATE_0)&CLevel_Editor::LoadTileMap);

	//pPanel->AddChildUI(pBtn);
	//AddObject(pPanel, LAYER_TYPE::UI);
	//

	//// ���ÿ� Map ������Ʈ ����
	//m_MapObj = new CMap;
	//AddObject(m_MapObj, LAYER_TYPE::TILE);

	
	auto pAtlas = new CAtlas;
	pAtlas->SetName(L"Atlas");
	AddObject(pAtlas, LAYER_TYPE::DEFAULT);
	CCamera::GetInst()->SetTarget(pAtlas);


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
	if (KEY_TAP(KEY::M))
	{
		Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
		ChangeLevel(LEVEL_TYPE::START);
	}

	// ���콺 Ŭ������ CMap ������Ʈ�� Ÿ�� �̹��� �ε��� ����
	// �Ϲ����� ������ : ���� ��ǥ -> Render ��ǥ ����
	// ���콺 ��ǥ : Render ��ǥ(���콺��ǥ) -> ���� ��ǥ�� ����
	if (KEY_TAP(KEY::LBTN))
	{
		//Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();	
		//tTile* TileInfo = m_MapObj->GetTileMap()->GetTileInfo(vMousePos);

		//if (nullptr != TileInfo)
		//{
		//	TileInfo->ImgIdx = 20;
		//}		
	}

	static Vec2 before;
	if (KEY_TAP(KEY::RBTN))
	{
		before = CKeyMgr::GetInst()->GetMousePos();
	}
	if (KEY_PRESSED(KEY::RBTN))
	{
		Vec2 now = CKeyMgr::GetInst()->GetMousePos();
		CCamera::GetInst()->AddOffset(before - now);
		before = now;
	}

	if (KEY_TAP(KEY::UP))
	{
		CAtlas* pAtlas = (CAtlas*)FindObjectByName(LAYER_TYPE::DEFAULT, L"Atlas");
		pAtlas->AddMagnification(1.f);
	}
	else if (KEY_TAP(KEY::DOWN))
	{
		CAtlas* pAtlas = (CAtlas*)FindObjectByName(LAYER_TYPE::DEFAULT, L"Atlas");
		pAtlas->AddMagnification(-1.f);
	}
}

void CLevel_Editor::Render()
{
	CLevel::Render();

	TextOut(CEngine::GetInst()->GetSecondDC(), 10, 10, L"Editor Level", wcslen(L"Editor Level"));
}

void CLevel_Editor::SaveTileMap()
{
	wstring strContentPath = CPathMgr::GetContentPath();
	strContentPath += L"TileMap";

	// ���� ��� ���ڿ�
	wchar_t szFilePath[255] = {};

	OPENFILENAME Desc = {};

	Desc.lStructSize = sizeof(OPENFILENAME);
	Desc.hwndOwner = nullptr;
	Desc.lpstrFile = szFilePath;	// ���������� �� ��θ� �޾Ƴ� ������
	Desc.nMaxFile = 255;
	Desc.lpstrFilter = L"Tile\0*.tile\0ALL\0*.*";
	Desc.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	Desc.lpstrInitialDir = strContentPath.c_str();

	if (GetSaveFileName(&Desc))
	{
		// �� ������Ʈ�� TileMap ������Ʈ ������ �����Ѵ�.
		m_MapObj->GetTileMap()->SaveTileMap(szFilePath);
	}
}

void CLevel_Editor::LoadTileMap()
{
	wstring strContentPath = CPathMgr::GetContentPath();
	strContentPath += L"TileMap";

	// ���� ��� ���ڿ�
	wchar_t szFilePath[255] = {};

	OPENFILENAME Desc = {};

	Desc.lStructSize = sizeof(OPENFILENAME);
	Desc.hwndOwner = nullptr;
	Desc.lpstrFile = szFilePath;
	Desc.nMaxFile = 255;
	Desc.lpstrFilter = L"Tile\0*.tile\0ALL\0*.*";
	Desc.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	Desc.lpstrInitialDir = strContentPath.c_str();

	if (GetOpenFileName(&Desc))
	{
		m_MapObj->GetTileMap()->LoadTileMap(szFilePath);
	}	
}






// =======
// �����Լ�
// =======
INT_PTR CALLBACK    TileMapInfoProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

void SaveTileMap()
{
	DialogBox(nullptr, MAKEINTRESOURCE(DLG_TILEMAP_INFO), CEngine::GetInst()->GetMainWndHwnd(), &TileMapInfoProc);

	/*CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pCurLevel);
	if (nullptr == pEditorLevel)
		return;

	pEditorLevel->SaveTileMap();*/
}

void LoadTileMap()
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pCurLevel);
	if (nullptr == pEditorLevel)
		return;

	pEditorLevel->LoadTileMap();
}


void OpenFileDialog(HWND _wnd);
bool EditorMenu(HINSTANCE _inst, HWND _wnd, int wParam)
{
	switch (wParam)
	{
	case ID_TILE_INFO:
	{
		DialogBox(_inst, MAKEINTRESOURCE(DLG_TILEMAP_INFO), _wnd, &TileMapInfoProc);

		/* if(nullptr == g_hDlg)
			g_hDlg = CreateDialog(g_hInst, MAKEINTRESOURCE(DLG_TILEMAP_INFO), hWnd, &TileMapInfoProc);

		ShowWindow(g_hDlg, true);*/
		return true;
	}
	case ID_LOAD_ATLAS:
	{
		//DialogBox(_inst, MAKEINTRESOURCE(DLG_TILEMAP_INFO), _wnd, &TileMapInfoProc);
		OpenFileDialog(_wnd);

		return true;
	}
	case ID_TILEMAP_SAVE:
	{
		// CLevel_Editor �� �ִ� MapObject �� Ÿ�ϸ� ������Ʈ�� �� ���� �������־�� ��
		// ���� ������ �˾Ƴ���. ��Ȳ�� ���� ������ �ݵ�� CLevel_Editor ���� �Ѵ�.
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
		assert(pEditorLevel);

		pEditorLevel->SaveTileMap();
	}
		return true;
	case ID_TILEMAP_LOAD:
	{
		// CLevel_Editor �� �ִ� MapObject �� Ÿ�ϸ� ������Ʈ�� �� ���� �������־�� ��
		// ���� ������ �˾Ƴ���. ��Ȳ�� ���� ������ �ݵ�� CLevel_Editor ���� �Ѵ�.
		CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pLevel);
		assert(pEditorLevel);

		pEditorLevel->LoadTileMap();
	}
		return true;
	};

	return false;
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

void OpenFileDialog(HWND hwnd) {
	IFileDialog* pFileDialog = NULL;

	// Initialize COM library
	HRESULT hr = CoInitialize(NULL);
	if (SUCCEEDED(hr)) {
		// Create the FileOpenDialog object
		hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_PPV_ARGS(&pFileDialog));
		if (SUCCEEDED(hr)) {
			// Show the dialog
			hr = pFileDialog->Show(hwnd);
			if (SUCCEEDED(hr)) {
				IShellItem* pItem;
				// Get the selected file
				hr = pFileDialog->GetResult(&pItem);
				if (SUCCEEDED(hr)) {
					LPWSTR pszFilePath;
					// Get the file path
					hr = pItem->GetDisplayName(SIGDN_NORMALDISPLAY, &pszFilePath);
					if (SUCCEEDED(hr)) {
						// Show the file path in a message box
						//MessageBox(hwnd, pszFilePath, L"Selected File", MB_OK);
						CAtlas* pAtlas = (CAtlas*)CLevelMgr::GetInst()->FindObjectByName(LAYER_TYPE::DEFAULT, L"Atlas");
						pAtlas->LoadTexture(pszFilePath, pszFilePath);
						CoTaskMemFree(pszFilePath); // Free the memory
					}
					pItem->Release();
				}
			}
			pFileDialog->Release(); // Release the dialog object
		}
		CoUninitialize(); // Uninitialize COM
	}
}