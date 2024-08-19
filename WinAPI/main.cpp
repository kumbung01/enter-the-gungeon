// WinAPI.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "WinAPI.h"

#include <vector>

#define MAX_LOADSTRING 100

#define MY_MACRO(Name) Name##Test


// 전역 변수
HINSTANCE   hInst = nullptr;


// 함수 선언
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// SAL : 주석 언어
int APIENTRY wWinMain(HINSTANCE hInstance   // 프로세스 주소(ID)
                    , HINSTANCE hPrevInstance // 안쓰이는 인자
                    , LPWSTR lpCmdLine
                    , int   nCmdShow)
{
    WNDCLASSEXW wcex = {};

    wcex.cbSize         = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = &WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINAPI);
    wcex.lpszClassName  = L"Key";
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    RegisterClassExW(&wcex);

    // HWND 윈도우 ID 타입
    // 커널 오브젝트 ( OS 차원에서 관리되는 객체 )
    HWND hWnd = CreateWindowW(L"Key", L"MyGame", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    // 윈도우 크기 설정, 위치 설정
    SetWindowPos(hWnd, nullptr, 10, 10, 1280, 768, 0);
    ShowWindow(hWnd, true);
    UpdateWindow(hWnd);


    // 단축키 테이블 
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI));



    // 메시지 변수
    MSG msg = {};

    // GetMessage
    // - 메세지 큐에 있는 메세지를 받아온다.
    // - 메세지가 큐에 없으면, 함수가 반환되지 않는다.
    // - 꺼낸 메세지가 WM_QUIT 이면, false 를 반환, 그 외에는 True 반환    
    std::vector<UINT> vecMsg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        vecMsg.push_back(msg.message);

        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
  
   return TRUE;
}


// 메세지를 처리하는 함수
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            
            // 사각형 그리기
            Rectangle(hdc, 10, 10, 110, 110);

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_MOUSEMOVE: 
    {
        int a = 0;
    }
        break;

    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case 'W':
        {
            int a = 0;
        }
            break;

        case 'S':
        {
            int a = 0;
        }
            break;
        }
    }


        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
