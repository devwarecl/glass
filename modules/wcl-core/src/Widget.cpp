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


#include <wcl/core/Widget.hpp>

#include <cassert>
#include <wcl/core/WidgetPrivate.h>
#include "WinUtil.hpp"

namespace wcl::core {
    Widget::Widget() : mImpl(new WidgetPrivate()) {}


    Widget::~Widget() {
        if (mImpl) {
            delete mImpl;
            mImpl = nullptr;
        }
    }


    bool Widget::create() {
        assert(mImpl);

        if (mImpl->create(CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, nullptr)) {
            this->onCreated();
            return true;
        }

        return false;
    }


    bool Widget::create(const Rect &area, Widget *parent) {
        assert(mImpl);

        const HWND hWndParent = parent ? parent->getImpl()->getHwnd() : nullptr;

        if (mImpl->create(area.left, area.top, area.width, area.height, hWndParent)) {
            this->onCreated();
            return true;
        }

        return false;
    }


    void Widget::setVisible(const bool value) {
        auto hWnd = getImpl()->getHwnd();

        ::ShowWindow(hWnd, value ? SW_SHOW : SW_HIDE);
    }


    bool Widget::isVisible() const {
        auto hWnd = getImpl()->getHwnd();

        return ::IsWindowVisible(hWnd) == TRUE;
    }


    Rect Widget::getArea() const {
        auto hWnd = getImpl()->getHwnd();

        RECT rect;

        ::GetWindowRect(hWnd, &rect);

        return CreateRect(rect);
    }


    Rect Widget::getClientArea() const {
        auto hWnd = getImpl()->getHwnd();

        RECT rect;

        ::GetClientRect(hWnd, &rect);

        return CreateRect(rect);
    }


    void Widget::setText(const std::string &value) {
        auto hWnd = getImpl()->getHwnd();

        ::SetWindowText(hWnd, value.c_str());
    }


    std::string Widget::getText() const {
        auto hWnd = getImpl()->getHwnd();

        const int length = ::GetWindowTextLength(hWnd);

        std::string value;
        value.resize(static_cast<size_t>(length) + 1);

        ::GetWindowText(hWnd, const_cast<char*>(value.c_str()), length + 1);

        return value;
    }
}
