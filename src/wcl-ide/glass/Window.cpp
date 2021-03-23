
#include "Window.hpp"

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

        this->sendMessage(WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);
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
        assert(false);
    }


    Rect Window::getClientArea() const {
        assert(hWnd);
        assert(::IsWindow(hWnd));
        assert(false);

        return {0, 0, 0, 0};
    }
}
