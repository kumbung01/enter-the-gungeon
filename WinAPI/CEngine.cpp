#include "pch.h"
#include "CEngine.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"

#include "CSelectGDI.h"

CEngine::CEngine()
    : m_hInst(nullptr)
    , m_hWnd(nullptr)
    , m_Resolution{}
    , m_hSecondDC(nullptr)
    , m_hSecondBitmap(nullptr)
{
   
}

CEngine::~CEngine()
{
    // DC 해제
    ReleaseDC(m_hWnd, m_hDC);

    // SecondBuffer 관련 메모리 해제
    DeleteDC(m_hSecondDC);
    DeleteObject(m_hSecondBitmap);


    // Pen 과 Brush 해제
    for (UINT i = 0; i < (UINT)PEN_TYPE::END; ++i)
    {
        DeleteObject(m_Pen[i]);
    }

    for (UINT i = 0; i < (UINT)BRUSH_TYPE::END; ++i)
    {
        DeleteObject(m_Brush[i]);
    }
}


int CEngine::Init(HINSTANCE _hInst, POINT _Resolution)
{
    m_hInst = _hInst;
    m_Resolution = _Resolution;

    // HWND 윈도우 ID 타입
    // 커널 오브젝트 ( OS 차원에서 관리되는 객체 )
    m_hWnd = CreateWindowW(L"Key", L"MyGame", (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX),
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInst, nullptr);

    if (!m_hWnd)   
        return E_FAIL;
    
    ShowWindow(m_hWnd, true);
    UpdateWindow(m_hWnd);

    // 윈도우 크기를 해상도에 맞게 설정
    ChangeWindowSize(m_Resolution);

    // DC 생성   
    m_hDC = GetDC(m_hWnd);

    // GDIObject 생성
    CreateGDIObject();    
  
    // Manager 생성 및 초기화
    CTimeMgr::GetInst()->Init();
    CKeyMgr::GetInst()->Init();
    CLevelMgr::GetInst()->Init();

    // 더블버퍼링을 위한 추가버퍼 생성
    CreateSecondBuffer();


    return S_OK;
}

void CEngine::CreateGDIObject()
{
    // Pen
    m_Pen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
    m_Pen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
    m_Pen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));

    // Brush
    m_Brush[(UINT)BRUSH_TYPE::RED] = CreateSolidBrush(RGB(255, 0, 0));
    m_Brush[(UINT)BRUSH_TYPE::GREEN] = CreateSolidBrush(RGB(0, 255, 0));
    m_Brush[(UINT)BRUSH_TYPE::BLUE] = CreateSolidBrush(RGB(0, 0, 255));
    m_Brush[(UINT)BRUSH_TYPE::GRAY] = CreateSolidBrush(RGB(100, 100, 100));
}



void CEngine::Progress()
{
    // Manager Tick
    CTimeMgr::GetInst()->Tick();
    CKeyMgr::GetInst()->Tick();

    // 레벨 실행
    CLevelMgr::GetInst()->Progress();

    // 렌더링
    // 화면 클리어
    {
        SELECT_BRUSH(BRUSH_TYPE::GRAY);
        Rectangle(m_hSecondDC, -1, -1, (int)m_Resolution.x + 1, (int)m_Resolution.y + 1);
    }

    CLevelMgr::GetInst()->Render();

    // SecondBitmap 있는 장면을 MainWindowBitmap 으로 복사해온다.
    BitBlt(m_hDC, 0, 0, (int)m_Resolution.x, (int)m_Resolution.y, m_hSecondDC, 0, 0, SRCCOPY);
}


void CEngine::ChangeWindowSize(Vec2 _vResolution)
{
    m_Resolution = _vResolution;   

    RECT rt = { 0, 0, m_Resolution.x, m_Resolution.y };

    // 메인윈도우가 Menu 가 있는지 확인
    HMENU hMenu = GetMenu(m_hWnd);

    AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, !!hMenu);

    SetWindowPos(m_hWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
}

void CEngine::CreateSecondBuffer()
{
    // 윈도우 비트맵과 동일한 크기(해상도) 비트맵을 생성
    m_hSecondBitmap = CreateCompatibleBitmap(m_hDC, (int)m_Resolution.x, (int)m_Resolution.y);

    // DC 생성
    // Pen : Black
    // Brush : White
    // Bitmap : 1 pixel 비트맵
    m_hSecondDC = CreateCompatibleDC(m_hDC);

    // DC 가 Bitmap 을 렌더타겟으로 지정하고 기존에 가리키던 비트맵을 삭제요청 
    DeleteObject(SelectObject(m_hSecondDC, m_hSecondBitmap));   
}