
#include <wcl/core/Menu.hpp>
#include <wcl/core/MenuItem.hpp>

#include "MenuHandle.hpp"

#include <vector>

namespace wcl::core {
    enum class MenuChildType {
        Separator,
        Item,
        Menu
    };


    struct MenuChild {
        MenuChildType mType;
        std::wstring mText;
        std::unique_ptr<Menu> mMenu;
        std::unique_ptr<MenuItem> mItem;

        static MenuChild item(const std::wstring &text) {
            return {
                MenuChildType::Item,
                text,
                {}, 
                {}
            };
        }

        static MenuChild menu(const std::wstring &text) {
            return {
                MenuChildType::Menu,
                text,
                {}, 
                {}
            };
        }

        static MenuChild separator() {
            return {
                MenuChildType::Separator,
                L"",
                {}, 
                {}
            };
        }
    };


    struct Menu::Impl {
        MenuHandle mHandle;
        std::vector<MenuChild> mChildren;
    };


    Menu::Menu() : mImpl(new Menu::Impl()) {}


    Menu::~Menu() {}


    void Menu::create() {
        mImpl->mHandle.hMenu = ::CreateMenu();

        for (const auto &child : mImpl->mChildren) {
            switch (child.mType) {
            case MenuChildType::Separator:
                ::AppendMenuW(mImpl->mHandle.hMenu, MF_SEPARATOR, 0, nullptr);
                break;

            case MenuChildType::Item:
                ::AppendMenuW(mImpl->mHandle.hMenu, MF_STRING, 0, child.mText.c_str());
                break;

            case MenuChildType::Menu:
                // TODO
                break;
            }
        }
    }


    MenuItem* Menu::addItem(const std::wstring &text) {
        mImpl->mChildren.push_back(MenuChild::item(text));

        return nullptr;
    }


    Menu* Menu::addMenu(const std::wstring &text) {
        mImpl->mChildren.push_back(MenuChild::menu(text));

        return nullptr;
    }


    void Menu::addSeparator() {
        mImpl->mChildren.push_back(MenuChild::separator());
    }


    const MenuHandle* Menu::getHandle() const {
        return &mImpl->mHandle;
    }
}
