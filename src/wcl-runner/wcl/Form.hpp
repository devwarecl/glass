
#pragma once 

#include <string>
#include <vector>
#include "Rect.hpp"

namespace wcl {
    class Control;

    class Form {
    public:
        Form();
        ~Form();

        void setText(const std::string &value);

        std::string getText() const;

        void setClientRect(const Rect &rect);

        Rect getClientRect() const;

        std::vector<Control*> getChildren() const;

    private:
        struct Private;
        Private *m_impl = nullptr;
    };
}
