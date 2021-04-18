
#include <wcl/core/WidgetPrivate.h>

#include <cassert>

namespace wcl::core {
    MessageDispatcher gMessageDispatcher;

    void MessageDispatcher::appendHandler(const HWND hWnd, const UINT nMsg, MessageHandler handler) {
        const MessageKey key {hWnd, nMsg};

        mMessageKeyHandlerMap[key].push_back(handler);
    }


    bool MessageDispatcher::callHandlers(const HWND hWnd, const UINT nMsg, WPARAM wParam, LPARAM lParam) {
        const auto it = mMessageKeyHandlerMap.find({hWnd, nMsg});

        if (it != mMessageKeyHandlerMap.end()) {
            for (auto &fn : it->second) {
                fn({wParam, lParam});
            }

            return true;
        }

        return false;
    }
}


namespace wcl::core {
    WidgetPrivate::~WidgetPrivate() {}


    bool WidgetPrivate::create(int x, int y, int w, int h, HWND hWndParent) {
        mHwnd = ::CreateWindowEx(
            mExStyle, mClassName, L"", mStyle, 
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


    void WidgetPrivate::appendMsgHandler(const int Msg, MessageHandler handler) const {
        assert(mHwnd);

        const HWND hWnd = ::GetParent(mHwnd);

        gMessageDispatcher.appendHandler(hWnd, Msg, handler);
    }
}
