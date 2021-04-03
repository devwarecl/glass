
#pragma once 

#include <wcl/core/Rect.hpp>
#include <wcl/core/Widget.hpp>

#include <Windows.h>

namespace wcl::core {
    Rect CreateRect(const RECT &rect);
}
