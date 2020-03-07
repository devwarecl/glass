
#pragma once

#ifndef __wcl_window_hpp__
#define __wcl_window_hpp__

#include <cassert>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>

#include "Rect.hpp"
#include "WindowBase.hpp"
#include "Exception.hpp"

namespace wcl {
    
    class Window;
    typedef std::unique_ptr<Window> WindowPtr;
    
    class Window : public WindowBase {
    protected:
        static LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
        
    public:
        explicit Window(const std::wstring &className);
        virtual ~Window();
    
    public:
        virtual void OnCommand(const int id) {}
        virtual void OnCreate() {}
        virtual void OnDestroy() {}
        virtual void OnClose() {}
        virtual void OnSize(const int width, const int height) {}
        virtual void OnNotify(const int id, const NMHDR* nmhdr) {}
        
    public:
        BOOL Create (
            const std::wstring &windowName, 
            DWORD dwStyle, 
            int x = CW_USEDEFAULT, 
            int y = CW_USEDEFAULT, 
            int nWidth = CW_USEDEFAULT, 
            int nHeight = CW_USEDEFAULT, 
            HWND hWndParent = NULL, 
            HMENU hMenu = NULL, 
            HINSTANCE hInstance = ::GetModuleHandle(NULL), 
            LPVOID lpParam = NULL
        );

        BOOL CreateEx (
            DWORD dwExStyle,             
            const std::wstring &windowName, 
            DWORD dwStyle, 
            int x = CW_USEDEFAULT, 
            int y = CW_USEDEFAULT, 
            int nWidth = CW_USEDEFAULT, 
            int nHeight = CW_USEDEFAULT, 
            HWND hWndParent = NULL, 
            HMENU hMenu = NULL, 
            HINSTANCE hInstance = ::GetModuleHandle(NULL), 
            LPVOID lpParam = NULL
        );

        void AddChild(wcl::WindowPtr child);

        wcl::WindowPtr RemoveChild(const int index);

        wcl::Window* GetChild(const int index);
        const wcl::Window* GetChild(const int index) const;

        const int GetChildCount() const;
        
        std::vector<wcl::Window*> GetChildVector() const {
            std::vector<wcl::Window*> childVector;

            std::transform(childs.begin(), childs.end(), childVector.begin(), [](const WindowPtr &child) {
                return child.get();
            });

            return childVector;
        }

        int GetChildIndex(const Window *child_) const {
            assert(child_);

            int index = 0;

            for (const auto &child : childs) {
                if (child.get() == child_) {
                    return index;
                }

                ++index;
            }

            return -1;
        }

        virtual LRESULT Procedure(UINT Msg, WPARAM wParam, LPARAM lParam);
        
    protected:
        std::wstring className;
        std::vector<wcl::WindowPtr> childs;
        WNDPROC windowProc;
    };

    inline LRESULT CALLBACK Window::WindowProcedure(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
        Window* window = reinterpret_cast<Window*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
        
        return window->Procedure(Msg, wParam, lParam);
    }
    
    inline Window::Window(const std::wstring &className) {
        this->className = className;
    }

    inline LRESULT Window::Procedure(UINT Msg, WPARAM wParam, LPARAM lParam) {
        switch (Msg) {
            case WM_DESTROY:    this->OnDestroy();                    break;
            case WM_CLOSE:        this->OnClose();                    break;
            case WM_COMMAND:    this->OnCommand(LOWORD(wParam));    break;
            
            case WM_SIZE:        
                this->OnSize(LOWORD(lParam), HIWORD(lParam));    
                break;
            
            case WM_NOTIFY:    {
                const int id = static_cast<const int>(wParam);
                const NMHDR* nmhdr = reinterpret_cast<const NMHDR*>(lParam);
                
                this->OnNotify(id, nmhdr);

                break;
            }
        }
        
        return this->windowProc(this->Handle, Msg, wParam, lParam);
    }
    
    inline Window::~Window() {
        this->Destroy();
    }

    inline BOOL Window::Create(const std::wstring &windowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam) {
        return this->CreateEx(0L, windowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
    }

    inline BOOL Window::CreateEx(DWORD dwExStyle, const std::wstring &windowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam) {
        HWND hWnd = ::CreateWindowExW(dwExStyle, this->className.c_str(), windowName.c_str(), dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);

        if (!hWnd) {
            throw wcl::Exception("Couldn't create the specified window.");
        }
        
        if (!this->Handle.hWnd) {
            this->Handle.hWnd = hWnd;
        }
        
        this->windowProc = (WNDPROC)this->GetLongPtr(GWLP_WNDPROC);
        this->SetLongPtr(GWLP_USERDATA, (LONG_PTR)this);
        this->SetLongPtr(GWLP_WNDPROC, (LONG_PTR)&Window::WindowProcedure);
        
        // Set the default font
        NONCLIENTMETRICS metrics = {};
        metrics.cbSize = sizeof(NONCLIENTMETRICS);
        
        ::SystemParametersInfo(
            SPI_GETNONCLIENTMETRICS,
            sizeof(NONCLIENTMETRICS),
            &metrics, 
            0
        );
        
        HFONT hFont = ::CreateFontIndirect(&metrics.lfMessageFont);
        this->SendMessage_(WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
        
        // Call OnCreate...
        this->OnCreate();
        
        return this->Handle.hWnd != NULL;
    }

    inline void Window::AddChild(wcl::WindowPtr child) {
        if (this->GetHandle() != ::GetParent(child->GetHandle())) {
            ::SetParent(child->GetHandle(), this->GetHandle());
        }

        childs.push_back(std::move(child));
    }

    inline wcl::WindowPtr Window::RemoveChild(const int index) {
        auto childIterator = childs.begin();

        std::advance(childIterator, index);

        wcl::WindowPtr child = std::move(childs[index]);

        childs.erase(childIterator);

        ::SetParent(child->GetHandle(), NULL);

        return child;
    }

    inline wcl::Window* Window::GetChild(const int index) {
        assert(index >= 0);
        assert(index < this->GetChildCount());

        return childs[index].get();
    }

    inline const wcl::Window* Window::GetChild(const int index) const {
        assert(index >= 0);
        assert(index < this->GetChildCount());

        return childs[index].get();
    }

    inline const int Window::GetChildCount() const {
        return static_cast<int>(childs.size());
    }
}

#endif
