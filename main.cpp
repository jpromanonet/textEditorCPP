#include <Windows.h>
#include "save.h"
#include "open.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void SaveFile(HWND hwnd);
void OpenFile(HWND hwnd);

#define IDM_SAVE 1001 // Define an ID for the "Save" menu item
#define IDM_OPEN 1002 // Define an ID for the "Save" menu item

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
    {
        HMENU hMenu = CreateMenu(); // Create the menu bar

        HMENU hFileMenu = CreateMenu(); // Create the "File" dropdown menu

        AppendMenu(hFileMenu, MF_STRING, IDM_OPEN, L"&Open"); // Add "Save" item
        AppendMenu(hFileMenu, MF_STRING, IDM_SAVE, L"&Save"); // Add "Save" item

        AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, L"&File"); // Add "File" dropdown to menu bar

        HMENU hEditMenu = CreateMenu(); // Create the "Edit" dropdown menu
        //AppendMenu(hFileMenu, MF_STRING, IDM_SAVE, L"&Save");

        AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hEditMenu, L"&Edit"); // Add "File" dropdown to menu bar

        SetMenu(hwnd, hMenu); // Attach the menu bar to the window

        CreateWindow(TEXT("EDIT"), TEXT(""),
            WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL |
            ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
            0, 30, 0, 0, hwnd, (HMENU)1, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
    }
    break;

    case WM_SIZE:
    {
        RECT rect;
        GetClientRect(hwnd, &rect);

        MoveWindow(GetDlgItem(hwnd, 1), 0, 30, rect.right, rect.bottom - 30, TRUE);
    }
    break;

    case WM_SETFOCUS:
        SetFocus(GetDlgItem(hwnd, 1));
        break;

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case IDM_SAVE: // Save item clicked
            SaveFile(hwnd); // Call the SaveFile function from the module
            break;

        case IDM_OPEN: // Open item clicked
            OpenFile(hwnd); // Call the OpenFile function from the module
            break;

            // ... Handle other menu items here ...
        }
    }
    break;

    case WM_PAINT:
    {
        hdc = BeginPaint(hwnd, &ps);
        GetClientRect(hwnd, &rect);
        rect.top += 30; // Leave space for the menu bar

        DrawText(hdc, TEXT("Welcome to the Simple Text Editor!"), -1, &rect,
            DT_SINGLELINE | DT_CENTER | DT_VCENTER);

        EndPaint(hwnd, &ps);
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}