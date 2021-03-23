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
#include <optional>
#include <memory>
#include <functional>
#include <vector>

namespace wcl::core {

    struct Window;
    struct Rect;

    class Frame;
    class Control {
        friend class Frame;

    public:
        ~Control();

        void setText(const std::wstring &value);

        std::wstring getText() const;

        Rect getArea() const;

        Rect getClientArea() const;

    public:
        std::vector<std::function<void ()>> clickEvent;

    protected:
        Window* getWindow() const;

        Control(const std::wstring &className);

        Control(const std::wstring &className, const std::wstring &text);

        Control(const std::wstring &className, const std::wstring &text, const Rect &area);

    private:
        struct Impl;
        std::unique_ptr<Impl> mImpl;
    };


    class Button : public Control {
        friend class Frame;

    protected:
        Button() : Control(L"BUTTON") {}

        Button(const std::wstring &text) : Control(L"BUTTON", text) {}

        Button(const std::wstring &text, const Rect &area) : Control(L"BUTTON", text, area) {}
    };


    class Edit : public Control  {
        friend class Frame;

    protected:
        Edit() : Control(L"EDIT") {}

        Edit(const std::wstring &text) : Control(L"EDIT", text) {}

        Edit(const std::wstring &text, const Rect &area) : Control(L"EDIT", text, area) {}
    };
    

    class Label : public Control {
        friend class Frame;

    protected:
        Label() : Control(L"STATIC") {}

        Label(const std::wstring &text) : Control(L"STATIC", text) {}

        Label(const std::wstring &text, const Rect &area) : Control(L"STATIC", text, area) {}
    };
}
