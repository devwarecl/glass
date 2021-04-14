
#pragma once 

#include <Windows.h>

#include <map>
#include <functional>

namespace wcl::core {
    struct MessageKey {
        HWND hWnd;
        UINT nMsg;

        bool operator<(const MessageKey &rhs) const {
            if (hWnd < rhs.hWnd) {
                return true;
            }

            return nMsg < rhs.nMsg;
        }
    };

    struct MessageParams {
        WPARAM wParam;
        LPARAM lParam;
    };

    using MessageHandler = std::function<LRESULT (const MessageParams& params)>;

    extern std::map<MessageKey, std::vector<MessageHandler>> gMessageKeyHandlerMap;


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
        const wchar_t *mClassName = nullptr;
        DWORD mStyle = 0L;
        DWORD mExStyle = 0L;
    };
}
