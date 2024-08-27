#include "pch.h"
#include "CEngine.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"

#include "CSelectGDI.h"
#include "CLevel.h"
#include "CObj.h"


CEngine::CEngine()
    : m_hInst(nullptr)
    , m_hWnd(nullptr)
    , m_Resolution{}
    , m_FrameCount(0)
    , m_Level(nullptr)
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

    // 윈도우 크기 설정, 위치 설정
    SetWindowPos(m_hWnd, nullptr, 10, 10, m_Resolution.x, m_Resolution.y, 0);

    // DC 생성   
    m_hDC = GetDC(m_hWnd);

    // GDIObject 생성
    CreateGDIObject();    
  
    // Manager 생성 및 초기화
    CTimeMgr::GetInst()->Init();
    CKeyMgr::GetInst()->Init();


    // 레벨 1개 생성하기
    m_Level = new CLevel;

    // 오브젝트 1개 생성해보기
    CObj* pObject = new CObj;
    pObject->SetPos( m_Resolution.x / 2.f, m_Resolution.y / 2.f);
    pObject->SetScale(50.f, 50.f);

    // 오브젝트를 레벨에 넣기
    m_Level->AddObject(pObject);

    // 오브젝트 1개 더 만들기
    pObject = new CObj;
    pObject->SetPos(100.f, m_Resolution.y / 2.f);
    pObject->SetScale(100.f, 100.f);
    m_Level->AddObject(pObject);


    // 레벨 시작
    m_Level->Begin();

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

    m_Level->Tick();
    m_Level->FinalTick();
    m_Level->Render();
}