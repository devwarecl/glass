
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

        const auto &connections = mConnections;

        getImpl()->appendMsgHandler(WM_COMMAND, [connections] (const MessageParams &params) {
            const Command command = translateCommand(params);

            if (command.source.type == wcl::core::CommandSourceType::ControlNotification || command.source.type == wcl::core::CommandSourceType::Menu) {
                if (command.data->notificationNode == BN_CLICKED) {
                    const auto it = connections.find(Button::Notifications::Clicked);

                    if (it != connections.end()) {
                        it->second();
                    }
                }
            }

            return 0;
        });

        return result;
    }


    void Button::connect(Button::Notifications notification, std::function<void ()> fn) {
        auto it = mConnections.find(notification);

        if (it != mConnections.end()) {
            it->second = fn;
        } else {
            mConnections[notification] = fn;
        }
    }
}
