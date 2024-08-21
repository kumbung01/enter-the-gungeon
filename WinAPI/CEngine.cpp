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

        m_FrameCount = 0;
        PrevCount = CurCount;
    }

}
