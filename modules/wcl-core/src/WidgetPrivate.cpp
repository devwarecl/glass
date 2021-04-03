
#include <wcl/core/WidgetPrivate.h>

namespace wcl::core {
    WidgetPrivate::~WidgetPrivate() {}


    bool WidgetPrivate::create() {
        mHwnd = ::CreateWindowEx(
            mExStyle, mClassName,  "", mStyle, 
            mX, mY, mWidth, mHeight, 
            mParentHandle, NULL,
            ::GetModuleHandle(NULL),
            NULL
        );

        return mHwnd != nullptr;
    }
}
