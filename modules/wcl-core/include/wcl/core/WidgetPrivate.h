
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

    class MessageDispatcher {
    public:
        void appendHandler(const HWND hWnd, const UINT nMsg, MessageHandler handler);

        bool callHandlers(const HWND hWnd, const UINT nMsg, WPARAM wParam, LPARAM lParam);

    private:
        std::map<MessageKey, std::vector<MessageHandler>> mMessageKeyHandlerMap;
    };


    extern MessageDispatcher gMessageDispatcher;

    class WidgetPrivate {
    public:
        WidgetPrivate() {}

        ~WidgetPrivate();

        bool create(int x, int y, int w, int h, HWND hWndParent);

        HWND getHwnd() const {
            return mHwnd;
        }

        void appendMsgHandler(const int Msg, MessageHandler handler) const;

    public:
        HWND mHwnd = nullptr;
        const wchar_t *mClassName = nullptr;
        DWORD mStyle = 0L;
        DWORD mExStyle = 0L;
    };
}
