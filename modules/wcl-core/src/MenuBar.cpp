
#include <wcl/core/MenuBar.hpp>

#define UNICODE
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <vector>

#include "MenuHandle.hpp"

namespace wcl::core {
    struct MenuBar::Impl {
        MenuHandle mHandle;
        std::vector<std::wstring> mMenues;
    };


    MenuBar::MenuBar() : mImpl(new MenuBar::Impl()) {}


    MenuBar::~MenuBar() {}


    Menu* MenuBar::addMenu(const std::wstring &text) {
        mImpl->mMenues.push_back(text);

        return nullptr;
    }


    bool MenuBar::create() {
        if (mImpl->mMenues.size() == 0) {
            return false;
        }

        mImpl->mHandle.hMenu = ::CreateMenu();

        for (const auto &menuText :  mImpl->mMenues) {
            const auto subMenuHandle = ::CreateMenu();

            ::AppendMenuW(mImpl->mHandle.hMenu, MF_POPUP, reinterpret_cast<UINT_PTR>(subMenuHandle), menuText.c_str());
        }

        return true;
    }


    MenuHandle* MenuBar::getHandle() {
        return &mImpl->mHandle;
    }
}
