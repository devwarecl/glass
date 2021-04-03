
#pragma once 

#include <Windows.h>

namespace wcl::core {
    class WidgetPrivate {
    public:
        WidgetPrivate() {}

        ~WidgetPrivate();

        bool create();

        HWND getHwnd() const {
            return mHwnd;
        }

    public:
        HWND mHwnd = nullptr;
        const char *mClassName = nullptr;
        DWORD mStyle = 0L;
        DWORD mExStyle = 0L;
        HWND mParentHandle = nullptr;
        int mX = CW_USEDEFAULT, mY = CW_USEDEFAULT;
        int mWidth = CW_USEDEFAULT, mHeight = CW_USEDEFAULT;
    };
}
