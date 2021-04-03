/*
 * The MIT License (MIT)
 *
 * Copyright © 2021 Felipe Apablaza C.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this 
 * software and associated documentation files (the “Software”), to deal in the Software 
 * without restriction, including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons 
 * to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or 
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <wcl/core/Frame.hpp>
#include <wcl/core/Control.hpp>
#include <wcl/core/MenuBar.hpp>

#include <map>

#include <wcl/core/WidgetPrivate.h>

#include "Window.hpp"
#include "MenuHandle.hpp"


namespace wcl::core {

    // static std::map<HWND, Frame*> sFrameMap;

    //struct Frame::Impl {
    //public:
    //    std::wstring mCreationTitle;
    //    const wchar_t *mClassName = L"Frame";
    //    HWND mHandle = nullptr;
    //    std::vector<std::unique_ptr<Control>> mChildControls;

    //    int mControlsCreated = 10000;
    //    std::map<HWND, Control*> mHandleControlMap;
    //    std::map<int, Control*> mIdControlMap;

    //    MenuBar mMenuBar;
    //};

    void registerFrameClass(const char *className);
}


namespace wcl::core {
    Frame::Frame() {
        registerFrameClass("wcl::core::Frame");

        getImpl()->mClassName = "wcl::core::Frame";
        getImpl()->mStyle = WS_OVERLAPPEDWINDOW;
    }


    Frame::~Frame() {}


    //void Frame::addChildImpl(Control *control) {
    //    mImpl->mChildControls.emplace_back(control);
    //    mImpl->mControlsCreated ++;
    //}


    //MenuBar* Frame::getMenuBar() {
    //    return &mImpl->mMenuBar;
    //}
}


namespace wcl::core {
    // std::map<HWND, Frame*> Frame::Impl::sFrameMap;


    LRESULT FrameWindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
        switch (Msg) {
            case WM_CREATE: {
                auto cs = (CREATESTRUCT *)lParam;
                // Frame::Impl::sFrameMap[hWnd] = reinterpret_cast<Frame*>(cs->lpCreateParams);
                break;
            }

            case WM_DESTROY: {
                ::PostQuitMessage(0);
                // Frame::Impl::sFrameMap.erase(hWnd);

                return 0;
            }

            //case WM_COMMAND: {
            //    auto frame = Frame::Impl::sFrameMap[hWnd];
            //
            //    auto hWndButton = reinterpret_cast<HWND>(lParam);
            //    auto button = frame->mImpl->mHandleControlMap[hWndButton];
            //
            //    button->raise("click");
            //
            //    return 0;
            //}
        }

        return ::DefWindowProcW(hWnd, Msg, wParam, lParam);
    }

    void registerFrameClass(const char *className) {
        WNDCLASSEX wcex = {};

        wcex.lpszClassName  = className;
        wcex.hInstance      = ::GetModuleHandle(NULL);
        wcex.cbSize         = sizeof(WNDCLASSEX);
        wcex.lpfnWndProc    = &FrameWindowProc;
        wcex.style          = CS_HREDRAW | CS_VREDRAW;
        wcex.cbClsExtra     = 0;
        wcex.cbWndExtra     = 0;
        wcex.hInstance      = ::GetModuleHandle(NULL);
        wcex.hIcon          = LoadIcon(::GetModuleHandle(NULL), IDI_APPLICATION);
        wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
        wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW);
        wcex.lpszMenuName   = NULL;
        wcex.hIconSm        = LoadIcon(wcex.hInstance, IDI_APPLICATION);

        assert(::RegisterClassEx(&wcex));
    }
}
