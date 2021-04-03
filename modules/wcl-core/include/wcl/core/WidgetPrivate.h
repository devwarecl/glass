
#pragma once 

#include <Windows.h>

namespace wcl::core {
    class WidgetPrivate {
    public:
        WidgetPrivate() {}

        ~WidgetPrivate();

        bool create(int x, int y, int w, int h, HWND hWndParent);

        HWND getHwnd() const {
            return mHwnd;
        }

    public:
        HWND mHwnd = nullptr;
        const char *mClassName = nullptr;
        DWORD mStyle = 0L;
        DWORD mExStyle = 0L;
    };
}
