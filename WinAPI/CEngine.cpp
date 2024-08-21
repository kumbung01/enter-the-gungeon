#include "pch.h"
#include "CEngine.h"

CEngine::CEngine()
    : m_hInst(nullptr)
    , m_hWnd(nullptr)
    , m_Resolution{}
    , m_FrameCount(0)
{
}

CEngine::~CEngine()
{
    ReleaseDC(m_hWnd, m_hDC);
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
    //  - Draw 목적지 ==> Window Bitmap
    //  - Balck Pen
    //  - White Brush
    m_hDC = GetDC(m_hWnd);

    // 펜 생성
    HPEN hRedPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));

    // 브러쉬 생성
    HBRUSH hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));

    // DC 의 펜과 브러쉬를 교체
    HPEN hPrevPen = (HPEN)SelectObject(m_hDC, hRedPen);
    HBRUSH hPrevBrush = (HBRUSH)SelectObject(m_hDC, hBlueBrush);

    Rectangle(m_hDC, 10, 10, 210, 210);

    // 원래 펜, 브러쉬로 변경
    SelectObject(m_hDC, hPrevPen);
    SelectObject(m_hDC, hPrevBrush);

    // 사용한 펜, 브러쉬 삭제요청
    DeleteObject(hRedPen);
    DeleteObject(hBlueBrush);

    return S_OK;
}

void CEngine::Progress()
{
    // FPS ( Frame Per Second )
    ++m_FrameCount;

    static UINT PrevCount = 0;
    static UINT CurCount = 0;
    
    CurCount = GetTickCount();

    if (1000 < CurCount - PrevCount)
    {
        // 1초에 한번씩 if 수행
        m_FrameCount;

        wchar_t strBuff[255] = {};
        swprintf_s(strBuff, 255, L"FPS : %d", m_FrameCount);


        m_FrameCount = 0;
        PrevCount = CurCount;
    }

}
