#include <Windows.h>
#include "navbar.h" // Include the navbar module header
#include "open.h"   // Include the open module header
#include "save.h"   // Include the save module header

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HWND hEdit; // Global handle to the edit control

// Margin sizes in pixels
const int PageMarginTop = 10;
const int PageMarginBottom = 50;
const int PageMarginLeft = 100;
const int PageMarginRight = 100;

void CreateMenuBar(HWND hwnd);
void HandleMenuCommands(HWND hwnd, WPARAM wParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
    static TCHAR szAppName[] = TEXT("SimpleTextEditor");
    HWND hwnd;
    MSG msg;
    WNDCLASS wndclass;

    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = szAppName;

    if (!RegisterClass(&wndclass))
    {
        MessageBox(NULL, TEXT("This program requires Windows NT!"), szAppName, MB_ICONERROR);
        return 0;
    }

    hwnd = CreateWindow(szAppName, TEXT("Simple Text Editor"), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);

    hEdit = CreateWindow(TEXT("EDIT"), TEXT(""),
        WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL |
        ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
        0, 0, 0, 0, hwnd, (HMENU)1, hInstance, NULL);

    CreateMenuBar(hwnd); // Create the menu bar

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rect;

    switch (message)
    {
    case WM_CREATE:
        // ... (additional code if needed)
        break;

    case WM_SIZE:
        MoveWindow(hEdit, PageMarginLeft, PageMarginTop, LOWORD(lParam) - (PageMarginLeft + PageMarginRight), HIWORD(lParam) - (2 * PageMarginTop), TRUE);
        break;

    case WM_SETFOCUS:
        SetFocus(hEdit);
        break;

    case WM_COMMAND:
        HandleMenuCommands(hwnd, wParam); // Handle menu commands from the navbar
        break;

    case WM_PAINT:
    {
        hdc = BeginPaint(hwnd, &ps);
        GetClientRect(hwnd, &rect);

        // Fill left margin with grey
        RECT leftMarginRect = rect;
        leftMarginRect.right = PageMarginLeft;
        FillRect(hdc, &leftMarginRect, (HBRUSH)GetStockObject(GRAY_BRUSH));

        // Fill right margin with grey
        RECT rightMarginRect = rect;
        rightMarginRect.left = rect.right - PageMarginRight;
        FillRect(hdc, &rightMarginRect, (HBRUSH)GetStockObject(GRAY_BRUSH));

        // Fill top and bottom margins with grey
        RECT topMarginRect = rect;
        topMarginRect.bottom = PageMarginTop;
        FillRect(hdc, &topMarginRect, (HBRUSH)GetStockObject(GRAY_BRUSH));

        RECT bottomMarginRect = rect;
        bottomMarginRect.top = rect.bottom - PageMarginBottom;
        FillRect(hdc, &bottomMarginRect, (HBRUSH)GetStockObject(GRAY_BRUSH));

        // ... (additional code if needed)

        EndPaint(hwnd, &ps);
        break;
    }


    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}