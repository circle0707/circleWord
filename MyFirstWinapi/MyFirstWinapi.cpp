// MyFirstWinapi.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "MyFirstWinapi.h"
#include <tchar.h>//_T사용 위하여

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MYFIRSTWINAPI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MYFIRSTWINAPI));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYFIRSTWINAPI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(CreateSolidBrush(RGB(30,60,100)));
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MYFIRSTWINAPI);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, L"MCLS Word SoftWare Korean...", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 640, 700, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    static TCHAR str[60000];
    static int count;
    static int ypos;
    RECT rect = { 0,40,1000,1000 };
    switch (message)
    {
    case WM_CREATE:
        {
        count = 0;
        ypos = 0;
        }
        break;
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
    case WM_CHAR:
        {
            hdc = GetDC(hWnd);
            if (wParam == VK_BACK && count > 0) {
                count--;
            }
            else if (wParam == VK_TAB) {
                str[count] = VK_SPACE;
                for (int i = 1; i <= 6; i++) {
                    str[count + i] = VK_SPACE;
                }
                count += 6;
            }
            else {
                str[count++] = wParam;
            }
            str[count] = NULL;
            InvalidateRgn(hWnd, NULL, true);
            ReleaseDC(hWnd, hdc);
        }
        break;
    case WM_PAINT:
        {
            hdc = BeginPaint(hWnd, &ps);
            TextOut(hdc, 10, 10, _T("이 쏘프트웨어는 공개입니다..., 만든누리 : MCLS,  판본1째판 0째마당"), _tcslen(_T("이 쏘프트웨어는 공개입니다..., 만든누리 : MCLS,  판본1째판 0째마당")));
            DrawText(hdc, str, _tcslen(str), &rect, DT_TOP | DT_LEFT);
            /*RECT rect;
            rect.left = 20;
            rect.top = 100;
            rect.right = 200;
            rect.bottom = 200;
            TextOut(hdc, 10, 10, _T("愛國歌"), _tcslen(_T("愛國歌")));
            TextOut(hdc, 100, 10, _T("동해물과 백두산이 마르고 닳도록"),_tcslen(_T("동해물과 백두산이 마르고 닳도록")));
            TextOut(hdc, 100, 27, _T("하느님이 보우하사 우리나라 만세"), _tcslen(_T("하느님이 보우하사 우리나라 만세")));
            TextOut(hdc, 100, 44, _T("무궁화 삼천리 화려강산"), _tcslen(_T("무궁화 삼천리 화려강산")));
            TextOut(hdc, 100, 61, _T("대한 사람 대한으로 길이 보전하세"), _tcslen(_T("대한 사람 대한으로 길이 보전하세")));*/

            //DrawText(hdc, _T("나는야 부엉이"), _tcslen(_T("나는야 부엉이")), &rect, DT_SINGLELINE || DT_CENTER || DT_VCENTER);
            EndPaint(hWnd, &ps);
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
