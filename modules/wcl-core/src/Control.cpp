/*
 * The MIT License (MIT)
 *
 * Copyright © 2021 Felipe Apablaza C.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this 
 * software and associated documentation files (the “Software”), to deal in the Software 
 * without restriction, including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons 
 * to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or 
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <wcl/core/Control.hpp>

#define UNICODE
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "Window.hpp"


namespace wcl::core {
    struct Control::Impl {
        Window mWindow;
    };
}


namespace wcl::core {
    Control::Control(const std::wstring &className) : mImpl(new Control::Impl) {
        mImpl->mWindow.mClassName = className;
    }


    Control::Control(const std::wstring &className, const std::wstring &text) : mImpl(new Control::Impl) {
        mImpl->mWindow.mClassName = className;
        mImpl->mWindow.mCreationText = text;
    }


    Control::Control(const std::wstring &className, const std::wstring &text, const Rect &area) : mImpl(new Control::Impl) {
        mImpl->mWindow.mClassName = className;
        mImpl->mWindow.mCreationText = text;
        mImpl->mWindow.mCreationAreaOpt = area;
    }


    Control::~Control() {}


    void Control::setText(const std::wstring &value) {
        ::SetWindowText(mImpl->mWindow.mHandle, value.c_str());
    }


    std::wstring Control::getText() const {
        const int length = ::GetWindowTextLengthW(mImpl->mWindow.mHandle);

        std::wstring value;
        value.resize(static_cast<size_t>(length) + 1);

        ::GetWindowText(mImpl->mWindow.mHandle, const_cast<wchar_t*>(value.c_str()), length + 1);

        return value;
    }


    Rect Control::getArea() const {
        RECT rect;

        ::GetWindowRect(mImpl->mWindow.mHandle, &rect);

        return {
            rect.left, rect.top, 
            rect.right - rect.left, rect.bottom - rect.top, 
        };
    }


    Rect Control::getClientArea() const {
        RECT rect;

        ::GetClientRect(mImpl->mWindow.mHandle, &rect);

        return {
            rect.left, rect.top, 
            rect.right - rect.left, rect.bottom - rect.top, 
        };
    }

    Window* Control::getWindow() const {
        return &mImpl->mWindow;
    }
}
