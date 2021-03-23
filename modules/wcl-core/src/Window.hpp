
#pragma once 

#define UNICODE
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <string>
#include <optional>

#include <wcl/core/Rect.hpp>

namespace wcl::core {
    struct Window {
        HWND mHandle = nullptr;
        int mId = 0;
        std::wstring mClassName;
        std::wstring mCreationText;
        std::optional<Rect> mCreationAreaOpt;

        void create(HWND mParent);
    };
}
