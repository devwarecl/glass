

#include "Window.hpp"

#include <cassert>

namespace wcl::core {
    void Window::create(HWND hWndParent) {
        const auto className = mClassName.c_str();
        const auto text = mCreationText.c_str();
        const DWORD style = hWndParent != nullptr ?  (WS_CHILD | WS_VISIBLE) : 0;
        const HMODULE hModule = ::GetModuleHandle(NULL);
        const int id = 0;
        
        if (mCreationAreaOpt) {
            const auto &area = mCreationAreaOpt.value();

            const int x1 = area.left;
            const int y1 = area.top;

            const int x2 = x1 + area.width;
            const int y2 = y1 + area.height;

            mHandle = ::CreateWindow(className, text, style, area.left, area.top, area.width, area.height, hWndParent, (HMENU)id, hModule, NULL);
        } else {
            mHandle = ::CreateWindow(className, text, style, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hWndParent, (HMENU)id, hModule, NULL);
        }

        assert(mHandle);

        ::SendMessage(mHandle, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);
    }
}
