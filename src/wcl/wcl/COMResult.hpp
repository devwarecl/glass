
#pragma once

#ifndef __wcl_comresult_hpp__
#define __wcl_comresult_hpp__

#include <comdef.h>
#include "COMException.hpp"

namespace wcl {
    enum class COMResultCheck {
        Default,
        Exception
    };

    template<COMResultCheck Check>
    class COMResult {
    public:
        COMResult();
        COMResult(HRESULT hr);

        operator HRESULT() const;

        bool Fail() const;
        
    private:
        HRESULT hr = 0x00000000;
    };

    typedef COMResult<COMResultCheck::Default> COMResultDefault;
    typedef COMResult<COMResultCheck::Exception> COMResultException;

    template<COMResultCheck Check>
    inline COMResult<Check>::COMResult() {
    }

    template<COMResultCheck Check>
    inline COMResult<Check>::COMResult(HRESULT hr) {
        this->hr = hr;

        if (Check==COMResultCheck::Exception && this->Fail()) {
            throw COMException(this->hr);
        }
    }

    template<COMResultCheck Check>
    inline COMResult<Check>::operator HRESULT() const {
        return this->hr;
    }

    template<COMResultCheck Check>
    inline bool COMResult<Check>::Fail() const {
        if (FAILED(this->hr)) {
            return true;
        } else {
            return false;
        }
    }
}

#endif
