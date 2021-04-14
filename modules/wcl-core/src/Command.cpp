
#include <wcl/core/Command.h>

#include <wcl/core/WidgetPrivate.h>

namespace wcl::core {
    Command translateCommand(const MessageParams &params) {
        const auto notificationCode = HIWORD(params.wParam);
        const auto id = LOWORD(params.wParam);

        switch (notificationCode) {
            case 0: return {CommandSourceType::Menu, id, {}};
            case 1: return {CommandSourceType::Accelerator, id, {}};
        }

        return {
            CommandSourceType::ControlNotification, id,
            CommandData{notificationCode, reinterpret_cast<void*>(params.lParam)}
        };
    }
}
