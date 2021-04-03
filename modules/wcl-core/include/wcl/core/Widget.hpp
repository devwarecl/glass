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

#pragma once 

#include <string>

#include "Rect.hpp"

namespace wcl::core {
    class WidgetPrivate;
    class Widget {
    protected:
        explicit Widget();

    public:
        virtual ~Widget();

        bool create();

        void show() {
            setVisible(true);
        }

        void hide() {
            setVisible(false);
        }

        void toggleVisible() {
            setVisible(! isVisible());
        }

        void setVisible(const bool value);

        bool isVisible() const;

        Rect getArea() const;

        Rect getClientArea() const;

        void setText(const std::string &text);

        std::string getText() const;

    protected:
        WidgetPrivate* getImpl() {
            return mImpl;
        }

        const WidgetPrivate* getImpl() const {
            return mImpl;
        }

    protected:
        virtual void onCreated() {}

    private:
        WidgetPrivate *mImpl = nullptr;
    };
}
