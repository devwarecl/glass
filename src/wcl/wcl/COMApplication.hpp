
#pragma once

#ifndef __wcl_comapplication_hpp__
#define __wcl_comapplication_hpp__

#include "Application.hpp"
#include "Exception.hpp"
#include "COMException.hpp"
#include "COMResult.hpp"

namespace wcl {

    class COMApplication : public Application {
    public:
        COMApplication();
        ~COMApplication();
    };

    inline COMApplication::COMApplication() {
        COMResultException hr = ::CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    }

    inline COMApplication::~COMApplication() {
        ::CoUninitialize();
    }
}

#endif // __wcl_comapplication_hpp__

