
#pragma once

#ifndef __wcl_frame_hpp__
#define __wcl_frame_hpp__

#include <string>

#include "Window.hpp"
#include "WindowClass.hpp"
#include "Menu.hpp"
#include "AcceleratorTable.hpp"

namespace wcl {
    class Frame : public wcl::Window {
    public:
        Frame(const std::wstring &className);
        
        virtual ~Frame();
        
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
        
        ATOM DoRegister();
        
        virtual void OnRegister(WNDCLASSEXW &wc) {}
        
        void SetMenu(MenuPtr menu);
        
        void SetAcceleratorTable(AcceleratorTablePtr acceleratorTable);

        Menu* GetMenu();

        AcceleratorTable* GetAcceleratorTable();

    private:
        WindowClass wc;
        MenuPtr menu;
        AcceleratorTablePtr acceleratorTable;
    };
    
    inline Frame::Frame(const std::wstring &className) : Window(className) {}
    
    inline Frame::~Frame() {
        this->Destroy();
        wc.Unregister();
    }
    
    inline BOOL Frame::Create (const std::wstring &windowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam) {
        return this->CreateEx(WS_EX_CLIENTEDGE, windowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
    }

    inline BOOL Frame::CreateEx (DWORD dwExStyle, const std::wstring &windowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam) {
        if (!this->DoRegister()) {
            throw wcl::Exception("Couldn't register the frame class");
        }
        
        return Window::CreateEx (
            dwExStyle, 
            windowName, dwStyle, 
            x, y, nWidth, nHeight, 
            hWndParent, hMenu, hInstance, 
            this
        );
    }
    
    inline ATOM Frame::DoRegister() {
        wc.hCursor = ::LoadCursor(NULL, IDC_ARROW);
        wc.hIcon = ::LoadIcon(NULL, IDI_APPLICATION);
        wc.hbrBackground = (HBRUSH) COLOR_3DSHADOW;
        wc.lpfnWndProc = DefWindowProc;
        wc.lpszClassName = this->className.c_str();

        this->OnRegister(wc);
        
        ATOM atom = wc.Register();
        
        return atom;
    }

    inline void Frame::SetMenu(MenuPtr menu) {
        this->menu = std::move(menu);
        ::SetMenu(this->GetHandle(), this->menu->GetHandle());
    }
        
    inline void Frame::SetAcceleratorTable(AcceleratorTablePtr acceleratorTable) {
        this->acceleratorTable = std::move(acceleratorTable);
    }

    inline Menu* Frame::GetMenu() {
        return this->menu.get();
    }

    inline AcceleratorTable* Frame::GetAcceleratorTable() {
        return this->acceleratorTable.get();
    }
}

#endif
