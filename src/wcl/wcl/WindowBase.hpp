
#pragma once

#ifndef __wcl_windowbase_hpp__
#define __wcl_windowbase_hpp__

#include "WindowHandle.hpp"

namespace wcl {

    typedef WindowHandleSmart WindowHandle;

    class WindowBase {
    public:
        WindowBase();
        
        virtual ~WindowBase();

        BOOL Close();

        BOOL Destroy();

        BOOL Show(int nCmdShow = SW_SHOWDEFAULT);

        Rect GetClientRect() const;

        BOOL SetPos(HWND hWndInsertAfter, int x, int y, int cx, int cy, UINT uFlags);

        BOOL SetPos(HWND hWndInsertAfter, const Rect &rect, UINT uFlags = SWP_DRAWFRAME);

        Rect GetRect() const;

        LONG_PTR GetLongPtr(int nIndex) const;

        LONG_PTR SetLongPtr(int nIndex, LONG_PTR longPtr);

        LRESULT SendMessage_(UINT Msg, WPARAM wParam=0L, LPARAM lParam=0L);
        LRESULT SendMessage_(UINT Msg, WPARAM wParam=0L, LPARAM lParam=0L) const;

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

        LRESULT PostMessage_(UINT Msg, WPARAM wParam=0L, LPARAM lParam=0L);

        operator HWND() const;
        
        HWND GetHandle() const {
            return this->Handle;
        }
        
        HDC GetDC() const;

        void SetText(const std::wstring &text);

        std::wstring GetText() const;

    private:
        WindowBase(const WindowBase&) = delete;
        WindowBase& operator=(const WindowBase&) = delete;

    protected:
        WindowHandle Handle;
    };

    inline WindowBase::WindowBase() {}

    inline WindowBase::~WindowBase() {
        this->Destroy();
    }
    
    inline BOOL WindowBase::Close() {
        return ::CloseWindow(this->Handle);
    }

    inline BOOL WindowBase::Destroy() {
        return this->Handle.Destroy();
    }

    inline BOOL WindowBase::Show(int nCmdShow) {
        return ::ShowWindow(this->Handle, nCmdShow);
    }

    inline WindowBase::operator HWND() const {
        return this->Handle;
    }

    inline Rect WindowBase::GetClientRect() const {
        Rect rect;

        ::GetClientRect(this->Handle, &rect);

        return rect;
    }

    inline BOOL WindowBase::SetPos(HWND hWndInsertAfter, int x, int y, int cx, int cy, UINT uFlags) {
        return ::SetWindowPos(this->Handle, hWndInsertAfter, x, y, cx, cy, uFlags);
    }

    inline BOOL WindowBase::SetPos(HWND hWndInsertAfter, const Rect &rect, UINT uFlags) {
        return this->SetPos(hWndInsertAfter, rect.left, rect.top, rect.GetWidth(), rect.GetHeight(), uFlags);
    }

    inline Rect WindowBase::GetRect() const {
        Rect rect = {};

        ::GetWindowRect(this->Handle, &rect);

        return rect;
    }

    inline LONG_PTR WindowBase::GetLongPtr(int nIndex) const {
        return ::GetWindowLongPtr(this->Handle, nIndex);
    }

    inline LONG_PTR WindowBase::SetLongPtr(int nIndex, LONG_PTR dwNewLong) {
        return ::SetWindowLongPtr(this->Handle, nIndex, dwNewLong);
    }

    inline LRESULT WindowBase::SendMessage_(UINT Msg, WPARAM wParam, LPARAM lParam) {
        return ::SendMessage(this->Handle, Msg, wParam, lParam);
    }

    inline LRESULT WindowBase::SendMessage_(UINT Msg, WPARAM wParam, LPARAM lParam) const {
        return ::SendMessage(this->Handle, Msg, wParam, lParam);
    }

    inline LRESULT WindowBase::PostMessage_(UINT Msg, WPARAM wParam, LPARAM lParam) {
        return ::PostMessage(this->Handle, Msg, wParam, lParam);
    }

    inline HDC WindowBase::GetDC() const {
        return ::GetDC(this->Handle);
    }    

    inline void WindowBase::SetText(const std::wstring &text) {
        this->SendMessage_(WM_SETTEXT, 0, text.c_str());
    }

    inline std::wstring WindowBase::GetText() const {
        const LRESULT TEXT_LENGTH = this->SendMessage_(WM_GETTEXTLENGTH);
        
        if (TEXT_LENGTH == 0) {
            return L"";
        }

        std::wstring text;
        text.resize(static_cast<size_t>(TEXT_LENGTH - 1));

        this->SendMessage_(WM_GETTEXT, TEXT_LENGTH, text.c_str());

        return text;
    }
}

#endif
