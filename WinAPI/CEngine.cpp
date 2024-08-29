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
    // DC ����
    ReleaseDC(m_hWnd, m_hDC);

    // SecondBuffer ���� �޸� ����
    DeleteDC(m_hSecondDC);
    DeleteObject(m_hSecondBitmap);


    // Pen �� Brush ����
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

    // HWND ������ ID Ÿ��
    // Ŀ�� ������Ʈ ( OS �������� �����Ǵ� ��ü )
    m_hWnd = CreateWindowW(L"Key", L"MyGame", (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX),
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInst, nullptr);

    if (!m_hWnd)   
        return E_FAIL;
    
    ShowWindow(m_hWnd, true);
    UpdateWindow(m_hWnd);

    // ������ ũ�⸦ �ػ󵵿� �°� ����
    ChangeWindowSize(m_Resolution);

    // DC ����   
    m_hDC = GetDC(m_hWnd);

    // GDIObject ����
    CreateGDIObject();    
  
    // Manager ���� �� �ʱ�ȭ
    CTimeMgr::GetInst()->Init();
    CKeyMgr::GetInst()->Init();
    CLevelMgr::GetInst()->Init();

    // ������۸��� ���� �߰����� ����
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

    // ���� ����
    CLevelMgr::GetInst()->Progress();

    // ������
    // ȭ�� Ŭ����
    {
        SELECT_BRUSH(BRUSH_TYPE::GRAY);
        Rectangle(m_hSecondDC, -1, -1, (int)m_Resolution.x + 1, (int)m_Resolution.y + 1);
    }

    CLevelMgr::GetInst()->Render();

    // SecondBitmap �ִ� ����� MainWindowBitmap ���� �����ؿ´�.
    BitBlt(m_hDC, 0, 0, (int)m_Resolution.x, (int)m_Resolution.y, m_hSecondDC, 0, 0, SRCCOPY);
}


void CEngine::ChangeWindowSize(Vec2 _vResolution)
{
    m_Resolution = _vResolution;   

    RECT rt = { 0, 0, m_Resolution.x, m_Resolution.y };

    // ���������찡 Menu �� �ִ��� Ȯ��
    HMENU hMenu = GetMenu(m_hWnd);

    AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, !!hMenu);

    SetWindowPos(m_hWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
}

void CEngine::CreateSecondBuffer()
{
    // ������ ��Ʈ�ʰ� ������ ũ��(�ػ�) ��Ʈ���� ����
    m_hSecondBitmap = CreateCompatibleBitmap(m_hDC, (int)m_Resolution.x, (int)m_Resolution.y);

    // DC ����
    // Pen : Black
    // Brush : White
    // Bitmap : 1 pixel ��Ʈ��
    m_hSecondDC = CreateCompatibleDC(m_hDC);

    // DC �� Bitmap �� ����Ÿ������ �����ϰ� ������ ����Ű�� ��Ʈ���� ������û 
    DeleteObject(SelectObject(m_hSecondDC, m_hSecondBitmap));   
}