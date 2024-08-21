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

    // HWND ������ ID Ÿ��
    // Ŀ�� ������Ʈ ( OS �������� �����Ǵ� ��ü )
    m_hWnd = CreateWindowW(L"Key", L"MyGame", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInst, nullptr);

    if (!m_hWnd)   
        return E_FAIL;
    
    ShowWindow(m_hWnd, true);
    UpdateWindow(m_hWnd);

    // ������ ũ�� ����, ��ġ ����
    SetWindowPos(m_hWnd, nullptr, 10, 10, m_Resolution.x, m_Resolution.y, 0);

    // DC ����
    //  - Draw ������ ==> Window Bitmap
    //  - Balck Pen
    //  - White Brush
    m_hDC = GetDC(m_hWnd);

    // �� ����
    HPEN hRedPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));

    // �귯�� ����
    HBRUSH hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));

    // DC �� ��� �귯���� ��ü
    HPEN hPrevPen = (HPEN)SelectObject(m_hDC, hRedPen);
    HBRUSH hPrevBrush = (HBRUSH)SelectObject(m_hDC, hBlueBrush);

    Rectangle(m_hDC, 10, 10, 210, 210);

    // ���� ��, �귯���� ����
    SelectObject(m_hDC, hPrevPen);
    SelectObject(m_hDC, hPrevBrush);

    // ����� ��, �귯�� ������û
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
        // 1�ʿ� �ѹ��� if ����
        m_FrameCount;

        wchar_t strBuff[255] = {};
        swprintf_s(strBuff, 255, L"FPS : %d", m_FrameCount);


        m_FrameCount = 0;
        PrevCount = CurCount;
    }

}
