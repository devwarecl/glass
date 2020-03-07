
#include <Windows.h>

LRESULT CALLBACK WndProc(_In_ HWND   hWnd, _In_ UINT   message, _In_ WPARAM wParam, _In_ LPARAM lParam) {
    switch (message) {
        case WM_COMMAND: {
            int controlId = HIWORD(wParam);
            ::MessageBox(hWnd, "Hola", "Chao", MB_OK);
            return 0;
        }
    
        case WM_CLOSE: {
            PostMessage(hWnd, WM_QUIT, 0, 0);
            return 0;
        }
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}


#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {
    WNDCLASSEX wcex;

    wcex.cbSize         = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = ::GetModuleHandle(NULL);
    wcex.hIcon          = LoadIcon(::GetModuleHandle(NULL), IDI_APPLICATION);
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = "Form1";
    wcex.hIconSm        = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex)) {
       MessageBox(NULL, "Error while registring a Window Class", "wcl-runner", NULL);
       return 1;
    }

    HWND hwnd = CreateWindowEx(0, "Form1", "Prueba", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, 0, 0, hInstance, 0);

    if (!hwnd) {
       MessageBox(NULL, "Error while creating a Window instance", "wcl-runner", NULL);
       return 1;
    }

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        if (msg.message == WM_QUIT) {
            return 0;
        } else {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}
