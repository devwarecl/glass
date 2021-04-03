
#include "WinUtil.hpp"

namespace wcl::core {
    Rect CreateRect(const RECT &rect) {
        return {
            rect.left, rect.top, 
            rect.right - rect.left, rect.bottom - rect.top, 
        };
    }
}
