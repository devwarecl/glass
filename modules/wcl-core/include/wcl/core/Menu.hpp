
#pragma once 

#include <string>
#include <memory>

namespace wcl::core {
    class MenuItem;
    class Menu {
    public:
        Menu();

        ~Menu();

        MenuItem* addItem(const std::wstring &text);

        Menu* addMenu(const std::wstring &text);

        void addSeparator();

    private:
        struct Impl;
        std::unique_ptr<Menu> mImpl;
    };
}
