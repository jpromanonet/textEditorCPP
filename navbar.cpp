#include <Windows.h>
#include "save.h"
#include "open.h"
#include "navbar.h" // Include the navbar module header

void CreateMenuBar(HWND hwnd) {
    HMENU hMenuBar = CreateMenu();
    HMENU hFileMenu = CreateMenu();

    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hFileMenu, L"File");
    AppendMenu(hFileMenu, MF_STRING, IDM_OPEN, L"Open");
    AppendMenu(hFileMenu, MF_STRING, IDM_SAVE, L"Save");

    SetMenu(hwnd, hMenuBar);
}

void HandleMenuCommands(HWND hwnd, WPARAM wParam) {
    switch (LOWORD(wParam)) {
    case IDM_SAVE:
        SaveFile(hwnd);
        break;

    case IDM_OPEN:
        OpenFile(hwnd);
        break;

        // Handle other menu commands as needed
    }
}
