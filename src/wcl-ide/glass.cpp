
#include "glass.hpp"

#include <Windows.h>

namespace glass {
    inline bool to_bool(const BOOL value) {
        return value == TRUE ? true : false;
    }


    inline BOOL to_BOOL(const bool value) {
        return value == true ? TRUE : FALSE;
    }
}


namespace glass {
    Window::Window(const std::string className, const DWORD dwStyle, const DWORD dwExStyle) 
        : className(className), dwStyle(dwStyle), dwExStyle(dwExStyle) {

        assert(className != "");
    }

    void Window::create(Window *parent, const std::string &text, const Rect &rect) {
        assert(className != "");

        hWnd = ::CreateWindowExA(
            dwExStyle, className.c_str(),  text.c_str(),  dwStyle, 
            rect.left, rect.top,
            rect.width, rect.height, 
            parent ? reinterpret_cast<HWND>(parent->getHandle()) : NULL,
            NULL,
            ::GetModuleHandle(NULL), 
            this
        );

        assert(hWnd);
        assert(::IsWindow(hWnd));
    }

    void Window::setVisible(const bool value) {
        assert(hWnd);
        assert(::IsWindow(hWnd));

        ::ShowWindow(hWnd, to_BOOL(value));
    }

    bool Window::isVisible() const {
        assert(hWnd);
        assert(::IsWindow(hWnd));

        return to_bool(::IsWindowVisible(hWnd));
    }

    void Window::setText(const std::string &value) {
        assert(hWnd);
        assert(::IsWindow(hWnd));

        ::SetWindowTextA(hWnd, value.c_str());
    }

    std::string Window::getText() const {
        assert(hWnd);
        assert(::IsWindow(hWnd));

        const auto size = static_cast<size_t>(::GetWindowTextLengthA(hWnd));

        if (size == 0) {
            return "";
        }

        std::string value;
        value.resize(size + 1);

        ::GetWindowTextA(
            hWnd, 
            const_cast<char*>(value.data()), 
            static_cast<int>(value.size())
        );

        return value;
    }


    HWND Window::getHandle() const {
        return hWnd;
    }


    void Window::setRect(const Rect &value) {
        assert(hWnd);
        assert(::IsWindow(hWnd));

        ::SetWindowPos(hWnd, NULL, value.left, value.top, value.width, value.height, SWP_FRAMECHANGED);
    }


    Rect Window::getRect() const {
        assert(hWnd);
        assert(::IsWindow(hWnd));

        RECT rect = {};

        ::GetWindowRect(hWnd, &rect);

        return {
            rect.left, 
            rect.top, 
            rect.right - rect.left,
            rect.bottom - rect.top
        };
    }


    void Window::setClientArea(const Rect &value) {
        assert(hWnd);
        assert(::IsWindow(hWnd));
    }


    Rect Window::getClientArea() const {
        assert(hWnd);
        assert(::IsWindow(hWnd));

        return {0, 0, 0, 0};
    }
}


namespace glass {
    Button::Button() : Window("BUTTON", WS_CHILD, NULL) {}
}


namespace glass {
    Registry::~Registry() {
        for (const std::string &className : classNames) {
            ::UnregisterClassA(className.c_str(), ::GetModuleHandle(NULL));
        }
    }

    void Registry::add(const char *className, WNDPROC wndProc) {
        WNDCLASSEX wcex = {};

        wcex.lpszClassName  = className;
        wcex.hInstance      = ::GetModuleHandle(NULL);
        wcex.cbSize         = sizeof(WNDCLASSEX);
        wcex.lpfnWndProc    = wndProc;
        wcex.style          = CS_HREDRAW | CS_VREDRAW;
        wcex.cbClsExtra     = 0;
        wcex.cbWndExtra     = 0;
        wcex.hInstance      = ::GetModuleHandle(NULL);
        wcex.hIcon          = LoadIcon(::GetModuleHandle(NULL), IDI_APPLICATION);
        wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
        wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW);
        wcex.lpszMenuName   = NULL;
        wcex.hIconSm        = LoadIcon(wcex.hInstance, IDI_APPLICATION);

        ::RegisterClassEx(&wcex);
        classNames.insert(wcex.lpszClassName);
    }
}


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


#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
