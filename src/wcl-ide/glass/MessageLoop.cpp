
#include "MessageLoop.hpp"

#include <Windows.h>

namespace glass {
    int MessageLoop::run() {
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
}
