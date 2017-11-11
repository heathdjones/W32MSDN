// W32MSDN1ST.cpp : Defines the entry point for the application.
// this line just here to test GIT
// third commitbb
// commit 5?

#include "stdafx.h"
#include "W32MSDN1ST.h"
#include <iostream>
using namespace std;

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
void                OnSize(HWND hwnd, UINT flag, int width, int height); // added
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

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_W32MSDN1ST, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_W32MSDN1ST));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg); // this func related to keyboard input
            DispatchMessage(&msg); // tells the OS to call the window procedure of the window that is the target of the message
        }
        Sleep(2); // added by me
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_W32MSDN1ST));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_W32MSDN1ST);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId, wmEvent;
    PAINTSTRUCT ps;
    HDC hdc;
    RECT clientRect;
    RECT textRect;
    HRGN bgRgn;
    HBRUSH hBrush;
    HPEN hPen;

    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
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
            /*  ORIGINAL CODE FROM GUIDE
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
            */
            hdc = BeginPaint(hWnd, &ps);

            // Fill the client area with a brush
            GetClientRect(hWnd, &clientRect);
            bgRgn = CreateRectRgnIndirect(&clientRect);
            hBrush = CreateSolidBrush(RGB(200, 200, 200));
            FillRgn(hdc, bgRgn, hBrush);


            hPen = CreatePen(PS_DOT, 1, RGB(0, 255, 0));
            SelectObject(hdc, hPen);
            SetBkColor(hdc, RGB(0, 0, 0));
            Rectangle(hdc, 10, 10, 200, 200);

            // Text caption
            SetBkColor(hdc, RGB(255, 255, 255));
            SetRect(&textRect, 10, 210, 200, 200);
            DrawText(hdc, TEXT("PS_DOT"), -1, &textRect, DT_CENTER | DT_NOCLIP);


            hPen = CreatePen(PS_DASHDOTDOT, 1, RGB(0, 255, 255));
            SelectObject(hdc, hPen);
            SetBkColor(hdc, RGB(255, 0, 0));
            SelectObject(hdc, CreateSolidBrush(RGB(0, 0, 0)));
            Rectangle(hdc, 210, 10, 400, 200);

            // Text caption
            SetBkColor(hdc, RGB(255, 200, 200));
            SetRect(&textRect, 210, 210, 400, 200);
            DrawText(hdc, TEXT("PS_DASHDOTDOT"), -1, &textRect, DT_CENTER | DT_NOCLIP);


            hPen = CreatePen(PS_DASHDOT, 1, RGB(255, 0, 0));
            SelectObject(hdc, hPen);
            SetBkColor(hdc, RGB(255, 255, 0));
            SelectObject(hdc, CreateSolidBrush(RGB(100, 200, 255)));
            Rectangle(hdc, 410, 10, 600, 200);

            // Text caption
            SetBkColor(hdc, RGB(200, 255, 200));
            SetRect(&textRect, 410, 210, 600, 200);
            DrawText(hdc, TEXT("PS_DASHDOT"), -1, &textRect, DT_CENTER | DT_NOCLIP);


            // When fnPenStyle is PS_SOLID, nWidth may be more than 1.
            // Also, if you set the width of any pen to be greater than 1, 
            // then it will draw a solid line, even if you try to select another style.
            hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
            SelectObject(hdc, hPen);
            // Setting the background color doesn't matter 
            // when the style is PS_SOLID
            SetBkColor(hdc, RGB(255, 255, 255));
            SelectObject(hdc, CreateSolidBrush(RGB(200, 100, 50)));
            Rectangle(hdc, 10, 300, 200, 500);

            // Text caption
            SetBkColor(hdc, RGB(200, 200, 255));
            SetRect(&textRect, 10, 510, 200, 500);
            DrawText(hdc, TEXT("PS_SOLID"), -1, &textRect, DT_CENTER | DT_NOCLIP);

            hPen = CreatePen(PS_DASH, 1, RGB(0, 255, 0));
            SelectObject(hdc, hPen);
            SetBkColor(hdc, RGB(0, 0, 0));
            SelectObject(hdc, CreateSolidBrush(RGB(200, 200, 255)));
            Rectangle(hdc, 210, 300, 400, 500);

            // Text caption
            SetBkColor(hdc, RGB(255, 255, 200));
            SetRect(&textRect, 210, 510, 400, 200);
            DrawText(hdc, TEXT("PS_DASH"), -1, &textRect, DT_CENTER | DT_NOCLIP);

            hPen = CreatePen(PS_NULL, 1, RGB(0, 255, 0));
            SelectObject(hdc, hPen);
            // Setting the background color doesn't matter 
            // when the style is PS_NULL
            SetBkColor(hdc, RGB(0, 0, 0));
            SelectObject(hdc, CreateSolidBrush(RGB(255, 255, 255)));
            Rectangle(hdc, 410, 300, 600, 500);

            // Text caption
            SetBkColor(hdc, RGB(200, 255, 255));
            SetRect(&textRect, 410, 510, 600, 500);
            DrawText(hdc, TEXT("PS_NULL"), -1, &textRect, DT_CENTER | DT_NOCLIP);

            // Clean up
            DeleteObject(bgRgn);
            DeleteObject(hBrush);
            DeleteObject(hPen);

            GetStockObject(WHITE_BRUSH);
            GetStockObject(DC_PEN);

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_SIZE:
    {
        int width = LOWORD(lParam);  // Macro to get the low-order word.
        int height = HIWORD(lParam); // Macro to get the high-order word.

                                     // Respond to the message:
        OnSize(hWnd, (UINT)wParam, width, height);
    }
    break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
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

// handle window resizing, just here for an example
void OnSize(HWND hwnd, UINT flag, int width, int height)
{
    // Handle resizing
}
