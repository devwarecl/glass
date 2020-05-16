
#pragma once

#include <string>
#include <glass/common.hpp>

namespace glass {
    struct Rect {
        int left, top;
        int width, height;
    };

    typedef long Handle;

    class AbstractWindow {
    public:
        virtual ~AbstractWindow() {}

        virtual void setVisible(const bool value) = 0;

        virtual bool isVisible() const = 0;

        virtual void setText(const std::string &value) = 0;

        virtual std::string getText() const = 0;

        virtual HWND getHandle() const = 0;

        virtual void setRect(const Rect &value) = 0;

        virtual Rect getRect() const = 0;

        virtual void setClientArea(const Rect &value) = 0;

        virtual Rect getClientArea() const = 0;
    };
}
