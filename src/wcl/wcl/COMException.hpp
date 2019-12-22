
#pragma once

#ifndef __wcl_comexception_hpp__
#define __wcl_comexception_hpp__

#include <stdexcept>
#include <string>
#include <boost/locale/encoding_utf.hpp>
#include <comdef.h>

namespace wcl {

    /**
     * @brief Exception caused of error on COM object.
     */
    class COMException : public std::runtime_error {
    public:
        explicit COMException(HRESULT hr);

        virtual const char* what() const noexcept override;

    private:
        std::string errorMessage;
    };

    inline std::string wstring_to_utf8(const std::wstring& str) {
        return boost::locale::conv::utf_to_utf<char>(str.c_str(), str.c_str() + str.size());
    }  
    
    inline COMException::COMException(HRESULT hr) : runtime_error("") {
        /*
        typedef std::codecvt_utf8<wchar_t> convert_type;
        
        _com_error error(hr);
        std::wstring wmsg = error.ErrorMessage();
        std::wstring_convert<convert_type, wchar_t> converter;
        
        this->errorMessage = converter.to_bytes(wmsg);
        */
        _com_error error(hr);
        this->errorMessage = wstring_to_utf8(error.ErrorMessage());
    }

    inline const char* COMException::what() const noexcept {
        return errorMessage.c_str();
    }
}

#endif
