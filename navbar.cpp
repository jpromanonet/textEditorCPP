#include <Windows.h>
#include "save.h"
#include "open.h"
#include "navbar.h" // Include the navbar module header

void CreateMenuBar(HWND hwnd) {
    HMENU hMenuBar = CreateMenu();
    HMENU hFileMenu = CreateMenu();
    HMENU hEditMenu = CreateMenu();
    HMENU hViewMenu = CreateMenu();

    // File dropdown menu
    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hFileMenu, L"File");
    // Items into the file dropdown menu
        AppendMenu(hFileMenu, MF_STRING, IDM_OPEN, L"Open");
        AppendMenu(hFileMenu, MF_STRING, IDM_SAVE, L"Save");

	// Edit dropdown menu
	AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hEditMenu, L"Edit");

    // View dropdown menu
    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hViewMenu, L"View");

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
