
#pragma once 

#include <string>
#include <memory>

namespace wcl::core {
    struct MenuHandle;

    class MenuItem;
    class Menu {
    public:
        Menu();

        ~Menu();

        MenuItem* addItem(const std::wstring &text);

        Menu* addMenu(const std::wstring &text);

        void addSeparator();

        void create();

        MenuHandle* getHandle();

    private:
        struct Impl;
        std::unique_ptr<Impl> mImpl;
    };
}
