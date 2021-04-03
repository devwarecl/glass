
#include <wcl/core/Button.h>

#include <wcl/core/WidgetPrivate.h>

namespace wcl::core {
    Button::Button() {
        getImpl()->mClassName = "BUTTON";
        getImpl()->mStyle = WS_CHILD;
    }
}
