
#include <wcl/core/Edit.h>

#include <wcl/core/WidgetPrivate.h>

namespace wcl::core {
    Edit::Edit() {
        getImpl()->mClassName = "EDIT";
        getImpl()->mStyle = WS_CHILD;
    }
}
