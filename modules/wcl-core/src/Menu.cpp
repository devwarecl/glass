
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

        }

        static MenuChild menu(const std::wstring &text) {

        }

        static MenuChild separator() {
            
        }
    };


    struct Menu::Impl {
        MenuHandle mHandle;
        std::vector<MenuChild> mChildren;

        std::vector<std::wstring> mChildTexts;
        std::vector<MenuChildType> mChildTypes;
        std::vector<std::unique_ptr<Menu>> mChildMenues;
        std::vector<std::unique_ptr<MenuItem>> mChildItems;
    };


    Menu::Menu() : mImpl(new Menu::Impl()) {}


    Menu::~Menu() {}


    void Menu::create() {
        mImpl->mHandle.hMenu = ::CreateMenu();

        for (const auto &menuText : mImpl->mChildTexts) {
            if (menuText == L"-") {
                ::AppendMenuW(mImpl->mHandle.hMenu, MF_SEPARATOR, 0, nullptr);
            } else {
                ::AppendMenuW(mImpl->mHandle.hMenu, MF_STRING, 0, menuText.c_str());
            }
        }
    }


    MenuItem* Menu::addItem(const std::wstring &text) {
        

        mImpl->mChildTexts.push_back(text);

        return nullptr;
    }


    Menu* Menu::addMenu(const std::wstring &text) {
        return nullptr;
    }


    void Menu::addSeparator() {
        mImpl->mChildTexts.push_back(L"-");
    }


    MenuHandle* Menu::getHandle() {
        return &mImpl->mHandle;
    }
}
