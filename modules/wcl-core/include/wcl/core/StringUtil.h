
#pragma once 

#include <string>

namespace wcl::core {
    std::string narrow(const std::wstring &wstr);

    std::wstring widen(const std::string &str);
}
