#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

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
        CreateWindow(TEXT("EDIT"), TEXT(""),
            WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL |
            ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
            0, 0, 0, 0, hwnd, (HMENU)1, ((LPCREATESTRUCT)lParam)->hInstance, NULL);

        CreateWindow(TEXT("BUTTON"), TEXT("Save"),
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            10, 310, 60, 25, hwnd, (HMENU)2, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
        break;

    case WM_SIZE:
        MoveWindow(GetDlgItem(hwnd, 1), 0, 0, LOWORD(lParam), HIWORD(lParam) - 30, TRUE);
        MoveWindow(GetDlgItem(hwnd, 2), 10, HIWORD(lParam) - 25, 60, 25, TRUE);
        break;

    case WM_SETFOCUS:
        SetFocus(GetDlgItem(hwnd, 1));
        break;

    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        GetClientRect(hwnd, &rect);
        DrawText(hdc, TEXT("Welcome to the Simple Text Editor!"), -1, &rect,
            DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        EndPaint(hwnd, &ps);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}
