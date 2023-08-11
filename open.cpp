#include <Windows.h>
#include <Commdlg.h> // Include for common dialogs
#include "open.h"    // Include your module's header file

void OpenFile(HWND hwnd) {
    OPENFILENAME ofn;
    wchar_t fileName[MAX_PATH] = L""; // Use wchar_t for wide-character strings

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFilter = L"Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0"; // Use wide-character string literals
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn)) {
        HWND hEdit = GetDlgItem(hwnd, 1);

        HANDLE hFile = CreateFileW(fileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); // Use CreateFileW for wide-character strings
        if (hFile != INVALID_HANDLE_VALUE) {
            DWORD fileSize = GetFileSize(hFile, NULL);
            char* buffer = new char[fileSize + 1];

            DWORD bytesRead;
            ReadFile(hFile, buffer, fileSize, &bytesRead, NULL);
            buffer[bytesRead] = '\0';

            // Convert narrow-character buffer to wide-character string
            wchar_t* wideBuffer = new wchar_t[bytesRead + 1];
            MultiByteToWideChar(CP_UTF8, 0, buffer, -1, wideBuffer, bytesRead + 1);

            SetWindowTextW(hEdit, wideBuffer); // Use SetWindowTextW for wide-character strings

            CloseHandle(hFile);
            delete[] buffer;
            delete[] wideBuffer;
        }
    }
}

