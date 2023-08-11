#include "save.h"
#include <CommDlg.h>

void SaveFile(HWND hwnd) {
    OPENFILENAMEW ofn;
    wchar_t fileName[MAX_PATH] = L""; // Use wchar_t for wide characters

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFilter = L"Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0"; // Use L prefix for wide strings
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_OVERWRITEPROMPT;

    if (GetSaveFileNameW(&ofn)) { // Use GetSaveFileNameW for wide characters
        HWND hEdit = GetDlgItem(hwnd, 1);
        int textLength = GetWindowTextLength(hEdit);
        wchar_t* buffer = new wchar_t[textLength + 1]; // Use wchar_t for wide characters
        GetWindowTextW(hEdit, buffer, textLength + 1); // Use GetWindowTextW for wide characters

        HANDLE hFile;
        hFile = CreateFileW(fileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); // Use CreateFileW for wide characters
        if (hFile != INVALID_HANDLE_VALUE) {
            DWORD bytesWritten;
            WriteFile(hFile, buffer, textLength * sizeof(wchar_t), &bytesWritten, NULL); // Use sizeof(wchar_t) for wide characters
            CloseHandle(hFile);
        }

        delete[] buffer;
    }
}
