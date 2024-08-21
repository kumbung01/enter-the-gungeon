#include "pch.h"

#include "WinAPI.h"
#include "CEngine.h"


HINSTANCE g_hInst = nullptr;

// 전역 변수
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// SAL : 주석 언어
int APIENTRY wWinMain(HINSTANCE hInstance   // 프로세스 주소(ID)
                    , HINSTANCE hPrevInstance // 안쓰이는 인자
                    , LPWSTR lpCmdLine
                    , int   nCmdShow)
{
    g_hInst = hInstance; // 프로세스 시작 주소

    WNDCLASSEXW wcex = {};

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = &WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPI));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINAPI);
    wcex.lpszClassName = L"Key";
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    RegisterClassExW(&wcex);

    // Engine 초기화
    if (FAILED(CEngine::GetInst()->Init(g_hInst, POINT{ 1280, 768 })))
        return FALSE;


    // 단축키 테이블 
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI));

    // 메시지 변수
    MSG msg = {};

    // GetMessage
    // - 메세지 큐에 있는 메세지를 받아온다.
    // - 메세지가 큐에 없으면, 함수가 반환되지 않는다.
    // - 꺼낸 메세지가 WM_QUIT 이면, false 를 반환, 그 외에는 True 반환        

    // 메세지가 없으면, 프로그램이 동작하지 않는 구조이다.
    // 게임을 만들기에 적합하지 않음
    // 강제로 일정시간마다 일정한 메세지를 발생시킨다. 
    //  - Timer 를 이용해서 WM_TIMER 메세지를 일정시간마다 발생시킨다.
    //  - 메세지큐에 메시지가 없어도 프로그램이 중단되어있지 않는 구조가 필요
    // GetMessage -> PeekMessage
    
    // GetMessage 가 반환되었다 == 메세지가 있었다.
    // 반환값이 false == 메세지가 WM_QUIT 이다.
    // 반환값이 true ==  메세지가 WM_QUIT 아니다. 

    // PeekMessage 가 반환되었다 == 메세지가 있었을 수도 있고, 없었을 수도 있다.
    // 반환값이 true == 메세지가 있었다.
    // 반환값이 false == 메세지가 없었다.
    while (true)
    {        
        // 메세지큐에 메세지가 있다.
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message)
                break;

            // 메세지 처리
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }

        // 메세지큐에 메세지가 없다.
        else
        {
            // 게임 실행
            CEngine::GetInst()->Progress();
        }       
    }

    return (int) msg.wParam;
}


// 1. 전역변수
float g_X = 500.f;
float g_Y = 300.f;

float g_Width = 100.f;
float g_Height = 100.f;



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
                DialogBox(g_hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
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
            
            // 무효화 영역 ( 화면을 다시 갱신해야 하는 영역 )

            // 사각형 그리기
            Rectangle(hdc
                    , g_X - g_Width / 2.f
                    , g_Y - g_Height / 2.f
                    , g_X + g_Width / 2.f
                    , g_Y + g_Height / 2.f);


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
            g_Y -= 1.f;      
            InvalidateRect(hWnd, nullptr, true);
            break;
        case 'S':
            g_Y += 1.f;
            InvalidateRect(hWnd, nullptr, true);
            break;
        case 'A':
            g_X -= 1.f;
            InvalidateRect(hWnd, nullptr, true);
            break;
        case 'D':
            g_X += 1.f;
            InvalidateRect(hWnd, nullptr, true);
            break;
        }
    }
    case WM_TIMER:
    {
        int a = 0;
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
