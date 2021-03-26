
#pragma once 

#include <string>
#include <memory>

namespace wcl::core {
    struct MenuHandle;

    class Frame;
    class Menu;
    class MenuBar {
    public:
        MenuBar();

        ~MenuBar();

        bool create();

        Menu* addMenu(const std::wstring &text);

        MenuHandle* getHandle();

    private:
        struct Impl;
        std::unique_ptr<Impl> mImpl;
    };
}
