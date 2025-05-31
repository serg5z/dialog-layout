#include <windows.h>
#include <layout.h>

#include "resource.h"


INT_PTR CALLBACK MainDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_INITDIALOG:
            // Attach the dialog layout using dialog-layout library
            attach_layout(GetModuleHandle(NULL), hDlg, MAKEINTRESOURCE(ID_MAINDIALOG_LAYOUT));
            return TRUE;

        case WM_COMMAND:
            switch (LOWORD(wParam)) {
            case IDOK:
            case IDCANCEL:
                EndDialog(hDlg, LOWORD(wParam));
                return TRUE;
            }
            break;
    }
    return FALSE;
}

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                      LPWSTR lpCmdLine, int nCmdShow) {
    DialogBoxParamW(
        hInstance,
        MAKEINTRESOURCE(ID_MAINDIALOG),
        NULL,
        MainDlgProc,
        0
    );
    return 0;
}

