
#pragma once

#include <Windows.h>

namespace glass {
    inline bool to_bool(const BOOL value) {
        return value == TRUE ? true : false;
    }

    inline BOOL to_BOOL(const bool value) {
        return value == true ? TRUE : FALSE;
    }
}
