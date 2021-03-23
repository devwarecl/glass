
#pragma once 

#include <string>
#include <memory>

namespace wcl::core {
    class Menu;
    class MenuBar {
    public:
        MenuBar();

        ~MenuBar();

        Menu* addMenu(const std::wstring &text);

    private:
        struct Impl;
        std::unique_ptr<Menu> mImpl;
    };
}
