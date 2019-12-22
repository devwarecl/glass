
#pragma once 

#include <Windows.h>
#include <string>

namespace wcl {
    /**
     * @brief Thin wrapper around a HWND
     */
    class Window {
    public:
        Window() = default;


        Window(const Window &other) = default;


        Window (HWND hWnd) {
            this->hWnd = hWnd;
        }


        Window& operator= (const Window &other) {
            hWnd = other.hWnd;

            return *this;
        }


        BOOL Close() {
            return ::CloseWindow(hWnd);
        }


        BOOL Destroy() {
            return ::DestroyWindow(hWnd);
        }


        BOOL Show(int nCmdShow) {
            return ::ShowWindow(hWnd, nCmdShow);
        }


        RECT GetClientRect() const {
            RECT rect;

            ::GetClientRect(hWnd, &rect);

            return rect;
        }


        BOOL SetPos(HWND hWndInsertAfter, int x, int y, int cx, int cy, UINT uFlags) {
            return ::SetWindowPos(hWnd, hWndInsertAfter, x, y, cx, cy, uFlags);
        }


        BOOL SetPos(HWND hWndInsertAfter, const RECT &rect, UINT uFlags) {
            return this->SetPos (
                hWndInsertAfter, 
                rect.left, 
                rect.top, 
                rect.right - rect.left, 
                rect.bottom - rect.top, 
                uFlags
            );
        }


        RECT GetRect() const {
            RECT rect = {};

            ::GetWindowRect(hWnd, &rect);

            return rect;
        }


        LONG_PTR GetLongPtr(int nIndex) const {
            return ::GetWindowLongPtr(hWnd, nIndex);
        }


        LONG_PTR SetLongPtr(int nIndex, LONG_PTR dwNewLong) {
            return ::SetWindowLongPtr(hWnd, nIndex, dwNewLong);
        }


        template<typename Type>
        Type GetLongPtr(const int index) const {
            return static_cast<Type>(this->GetLongPtr(index));
        }


        LRESULT SendMessage_(UINT Msg, WPARAM wParam = 0L, LPARAM lParam = 0L) {
            return ::SendMessage(hWnd, Msg, wParam, lParam);
        }


        LRESULT SendMessage_(UINT Msg, WPARAM wParam  = 0L, LPARAM lParam = 0L) const {
            return ::SendMessage(hWnd, Msg, wParam, lParam);
        }


        LRESULT PostMessage_(UINT Msg, WPARAM wParam, LPARAM lParam) {
            return ::PostMessage(hWnd, Msg, wParam, lParam);
        }


        HDC GetDC() const {
            return ::GetDC(hWnd);
        }    


        void SetText(const std::string &text) {
            this->SendMessage_(WM_SETTEXT, 0, text.c_str());
        }


        std::string GetText() const {
            const LRESULT TEXT_LENGTH = this->SendMessage_(WM_GETTEXTLENGTH);
        
            if (TEXT_LENGTH == 0) {
                return "";
            }

            std::string text;
            text.resize(static_cast<size_t>(TEXT_LENGTH - 1));

            this->SendMessage_(WM_GETTEXT, TEXT_LENGTH, text.c_str());

            return text;
        }


        template<typename Type1, typename Type2>
        LRESULT SendMessage_(UINT Msg, Type1 wParam, Type2 lParam) {
            return this->SendMessage_(Msg, WPARAM(wParam), LPARAM(lParam));
        }


        template<typename Type1>
        LRESULT SendMessage_(UINT Msg, Type1 wParam) {
            return this->SendMessage_(Msg, WPARAM(wParam));
        }


        template<typename Type1, typename Type2>
        LRESULT SendMessage_(UINT Msg, Type1 wParam, Type2 lParam) const {
            return this->SendMessage_(Msg, WPARAM(wParam), LPARAM(lParam));
        }


        template<typename Type1>
        LRESULT SendMessage_(UINT Msg, Type1 wParam) const {
            return this->SendMessage_(Msg, WPARAM(wParam));
        }

        operator HWND() const {
            return hWnd;
        }

        operator bool() const {
            return hWnd != NULL;
        }

        HWND hWnd = NULL;
    };
}
