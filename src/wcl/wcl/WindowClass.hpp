
#pragma once

#ifndef __wcl_windowclass_hpp__
#define __wcl_windowclass_hpp__

#include <Windows.h>
#include <cassert>

namespace wcl {
    
    struct WindowClass : public WNDCLASSEXW {
        WindowClass();
        explicit WindowClass(LPWSTR className);
        ~WindowClass();

        ATOM Register();
        BOOL Unregister();
    };

    inline WindowClass::WindowClass() {
        ::ZeroMemory(static_cast<WNDCLASSEXW*>(this), sizeof(WNDCLASSEXW));

        this->cbSize = sizeof(WNDCLASSEXW);
        this->hInstance = ::GetModuleHandle(NULL);
    }
    
    inline WindowClass::WindowClass(LPWSTR className) {
        assert(className);
        assert(className != L"");
        assert(className != std::wstring(L""));
        
        ::ZeroMemory(static_cast<WNDCLASSEXW*>(this), sizeof(WNDCLASSEXW));

        this->cbSize = sizeof(WNDCLASSEXW);
        this->hInstance = ::GetModuleHandle(NULL);
        this->lpszClassName = className;
    }

    inline WindowClass::~WindowClass() {
        BOOL result = this->Unregister();
    }

    inline ATOM WindowClass::Register() {
        assert(this->lpszClassName);
        assert(this->lpszClassName != L"");
        assert(this->lpszClassName != std::wstring(L""));
        
        ATOM atom = ::RegisterClassExW(this);
        
        if (!atom) {
            throw wcl::Exception("Couldn't register the window class");
        }
        
        return atom;
    }
    
    inline BOOL WindowClass::Unregister() {
        if (this->lpszClassName) {
            if (::UnregisterClassW(this->lpszClassName, this->hInstance)) {
                ::ZeroMemory(static_cast<WNDCLASSEXW*>(this), sizeof(WNDCLASSEXW));
            } else {
                throw wcl::Exception("Couldn't unregister the window class");
            }
        }
        
        return TRUE;
    }
}

#endif
