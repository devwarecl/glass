
#include <wcl/core/StringUtil.h>

#include <codecvt>

namespace wcl::core {
    std::string narrow(const std::wstring &wstr) {
        //setup converter
        using convert_type = std::codecvt_utf8<wchar_t>;
        std::wstring_convert<convert_type, wchar_t> converter;

        //use converter (.to_bytes: wstr->str, .from_bytes: str->wstr)
        return converter.to_bytes( wstr );
    }


    std::wstring widen(const std::string &str) {
        //setup converter
        using convert_type = std::codecvt_utf8<wchar_t>;
        std::wstring_convert<convert_type, wchar_t> converter;

        //use converter (.to_bytes: wstr->str, .from_bytes: str->wstr)

        return converter.from_bytes(str);
    }
}
