
#include <wcl/core/MenuBar.hpp>
#include <wcl/core/Menu.hpp>

#define UNICODE
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <vector>

#include "MenuHandle.hpp"

namespace wcl::core {
    struct MenuBar::Impl {
        MenuHandle mHandle;
        std::vector<std::wstring> mMenuTexts;
        std::vector<std::unique_ptr<Menu>> mMenues;
    };


    MenuBar::MenuBar() : mImpl(new MenuBar::Impl()) {}


    MenuBar::~MenuBar() {}


    Menu* MenuBar::addMenu(const std::wstring &text) {
        mImpl->mMenuTexts.push_back(text);

        auto menu = new Menu();

        mImpl->mMenues.emplace_back(menu);

        return menu;
    }


    bool MenuBar::create() {
        if (mImpl->mMenuTexts.size() == 0) {
            return false;
        }

        mImpl->mHandle.hMenu = ::CreateMenu();

        for (size_t i=0; i<mImpl->mMenuTexts.size(); i++) {
            const auto &menuText = mImpl->mMenuTexts[i];
            
            auto &menu = mImpl->mMenues[i];

            menu->create();

            ::AppendMenuW(mImpl->mHandle.hMenu, MF_POPUP, reinterpret_cast<UINT_PTR>(menu->getHandle()->hMenu), menuText.c_str());
        }

        return true;
    }


    MenuHandle* MenuBar::getHandle() {
        return &mImpl->mHandle;
    }
}
