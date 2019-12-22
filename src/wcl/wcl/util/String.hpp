
#pragma once

#ifndef __wcl_util_string_hpp__
#define __wcl_util_string_hpp__

#include <string>
#include <cstdlib>

namespace wcl {
    inline std::wstring ToWString(const std::string& source) {
        std::wstring destination;

        destination.resize(source.size());

        std::mbstowcs(
            const_cast<wchar_t*>(destination.c_str()),
            source.c_str(),
            source.size()
        );

        return destination;
    }

    inline std::string ToString(const std::wstring& source) {
        std::string destination;

        destination.resize(source.size());

        std::wcstombs(
            const_cast<char*>(destination.c_str()),
            source.c_str(),
            source.size()
        );

        return destination;
    }
}

#endif
