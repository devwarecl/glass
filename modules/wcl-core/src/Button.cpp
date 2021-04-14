
#include <wcl/core/Button.h>

#include <optional>

#include <wcl/core/Command.h>
#include <wcl/core/WidgetPrivate.h>

namespace wcl::core {
    Button::Button() {
        getImpl()->mClassName = L"BUTTON";
        getImpl()->mStyle = WS_CHILD;
    }


    bool Button::create(const Rect &area, Widget *parent) {
        const bool result = Widget::create(area, parent);
        /*
        const auto hWndParent = GetParent(this->getImpl()->getHwnd());
        const auto key = MessageKey{reinterpret_cast<HWND>(hWndParent), WM_COMMAND};
        
        const auto hWnd = reinterpret_cast<HWND>(this->getImpl()->getHwnd());
        const auto &connections = mConnections;

        gMessageKeyHandlerMap[key].push_back( [hWnd, connections] (const MessageParams &params) {
            const Command command = translateCommand(params);

            if (command.source.type == wcl::core::CommandSourceType::ControlNotification) {
                if (command.data->handle == hWnd && command.data->notificationNode == BN_CLICKED) {
                    const auto it = connections.find(Button::Notifications::Clicked);

                    if (it != connections.end()) {
                        it->second();
                    }
                }
            }

            return 0;
        });
        */

        return result;
    }


    void Button::connect(Button::Notifications notification, std::function<void ()> fn) {
        auto it = mConnections.find(notification);

        if (it != mConnections.end()) {
            it->second = fn;
        }
    }
}
