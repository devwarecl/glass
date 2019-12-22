
#pragma once

#ifndef __wcl_exception_hpp__
#define __wcl_exception_hpp__

#include <string>
#include <stdexcept>
#include <Windows.h>

namespace wcl {
    class Exception : public std::runtime_error {
    public:
        Exception(const std::string &msg);
        
    private:
        static std::string ErrorCodeToString(DWORD errorCode);
    };

    inline Exception::Exception(const std::string &msg) : runtime_error(msg + ": \"" + Exception::ErrorCodeToString(::GetLastError()) + "\"") {}

    inline std::string Exception::ErrorCodeToString(DWORD errorCode) {
        // error string formatting WinAPI call extracted from
        // http://www.paskov.biz/blog/clasterror/

        std::string msg;
            
        const int errorTextLength = 1024;
        CHAR lpErrorText[1024];

        ::FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, 0, errorCode, 0, lpErrorText, errorTextLength, 0 );
        msg = lpErrorText;
    
        return msg;
    }
}

#endif // __wcl_exception_hpp__
