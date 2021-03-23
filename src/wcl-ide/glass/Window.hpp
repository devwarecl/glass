
#pragma once

#include "AbstractWindow.hpp"

#include <cassert>

namespace glass {
    class Window : public AbstractWindow {
    public:
        explicit Window(const std::string className, const DWORD dwStyle, const DWORD dwExStyle);

        void create(Window *parent, const Rect &rect, const std::string &text) {
            create(parent, text, rect);
        }

        void create(Window *parent, const std::string &text, const Rect &rect);

        bool isCreated() const {
            return hWnd != NULL;
        }

        void setVisible(const bool value) override;

        bool isVisible() const override;

        void setText(const std::string &value) override;

        std::string getText() const override;

        HWND getHandle() const override;

        void setRect(const Rect &value) override;

        Rect getRect() const override;

        void setClientArea(const Rect &value) override;

        Rect getClientArea() const override;

    protected:
        LONG_PTR getLongPtr(int nIndex) const {
            assert(hWnd);
            assert(::IsWindow(hWnd));
            return ::GetWindowLongPtr(hWnd, nIndex);
        }

        LONG_PTR getLongPtr(int nIndex, LONG_PTR longPtr) {
            assert(hWnd);
            assert(::IsWindow(hWnd));
            return ::SetWindowLongPtr(hWnd, nIndex, longPtr);
        }

        LRESULT sendMessage(UINT Msg, WPARAM wParam=0L, LPARAM lParam=0L) {
            assert(hWnd);
            assert(::IsWindow(hWnd));
            return ::SendMessage(hWnd, Msg, wParam, lParam);
        }

        LRESULT sendMessage(UINT Msg, WPARAM wParam=0L, LPARAM lParam=0L) const {
            assert(hWnd);
            assert(::IsWindow(hWnd));
            return ::SendMessage(hWnd, Msg, wParam, lParam);
        }

        LRESULT postMessage(UINT Msg, WPARAM wParam, LPARAM lParam) {
            assert(hWnd);
            assert(::IsWindow(hWnd));
            return ::PostMessage(hWnd, Msg, wParam, lParam);
        }

    protected:
        HWND hWnd = NULL;
        const std::string className;
        const DWORD dwStyle;
        const DWORD dwExStyle;
    };
}
