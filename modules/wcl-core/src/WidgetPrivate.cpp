
#include <wcl/core/WidgetPrivate.h>

namespace wcl::core {
    WidgetPrivate::~WidgetPrivate() {}


    bool WidgetPrivate::create(int x, int y, int w, int h, HWND hWndParent) {
        mHwnd = ::CreateWindowEx(
            mExStyle, mClassName,  "", mStyle, 
            x, y, w, h, 
            hWndParent, NULL,
            ::GetModuleHandle(NULL),
            NULL
        );

        if (mHwnd) {
            ::SendMessage(mHwnd, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);
        }
        
        return mHwnd != nullptr;
    }
}