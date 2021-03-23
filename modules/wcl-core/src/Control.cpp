
#include <wcl/core/Control.hpp>

#include "Control.Impl.hpp"

namespace wcl::core {
    Control::Control(const std::wstring &className) : mImpl(new Control::Impl) {
        mImpl->mClassName = className;
    }


    Control::Control(const std::wstring &className, const std::wstring &text) : mImpl(new Control::Impl) {
        mImpl->mClassName = className;
        mImpl->mCreationText = text;
    }


    Control::Control(const std::wstring &className, const std::wstring &text, const Rect &area) : mImpl(new Control::Impl) {
        mImpl->mClassName = className;
        mImpl->mCreationText = text;
        mImpl->mCreationAreaOpt = area;
    }


    Control::~Control() {}


    void Control::setText(const std::wstring &value) {
        ::SetWindowText(mImpl->mHandle, value.c_str());
    }


    std::wstring Control::getText() const {
        const int length = ::GetWindowTextLengthW(mImpl->mHandle);

        std::wstring value;
        value.resize(static_cast<size_t>(length) + 1);

        ::GetWindowText(mImpl->mHandle, const_cast<wchar_t*>(value.c_str()), length + 1);

        return value;
    }


    Rect Control::getArea() const {
        RECT rect;

        ::GetWindowRect(mImpl->mHandle, &rect);

        return {
            rect.left, rect.top, 
            rect.right - rect.left, rect.bottom - rect.top, 
        };
    }


    Rect Control::getClientArea() const{
        RECT rect;

        ::GetClientRect(mImpl->mHandle, &rect);

        return {
            rect.left, rect.top, 
            rect.right - rect.left, rect.bottom - rect.top, 
        };
    }
}
