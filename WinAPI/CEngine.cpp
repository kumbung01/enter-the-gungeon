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
    , m_FrameCount(0)   
{
   
}

CEngine::~CEngine()
{
    // DC 해제
    ReleaseDC(m_hWnd, m_hDC);

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
    m_hWnd = CreateWindowW(L"Key", L"MyGame", WS_OVERLAPPEDWINDOW,
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
}


void CEngine::Progress()
{
    // Manager Tick
    CTimeMgr::GetInst()->Tick();
    CKeyMgr::GetInst()->Tick();

    // 레벨 실행
    CLevelMgr::GetInst()->Progress();
}


void CEngine::ChangeWindowSize(Vec2 _vResolution)
{
    m_Resolution = _vResolution;   

    RECT rt = { 0, 0, m_Resolution.x, m_Resolution.y };    
    AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);

    SetWindowPos(m_hWnd, nullptr, 10, 10, m_Resolution.x, m_Resolution.y, 0);
}