
#include <wcl/core/Application.hpp>

#define UNICODE
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace wcl::core {
    Application::Application() {
        ::SetProcessDPIAware();
    }

    int Application::run() { 
        MSG msg;

        while (::GetMessage(&msg, NULL, 0, 0)) {
            if (msg.message == WM_QUIT) {
                return 0;
            } else {
                ::TranslateMessage(&msg);
                ::DispatchMessage(&msg);
            }
        }

        return (int) msg.wParam;
    }
}


#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
