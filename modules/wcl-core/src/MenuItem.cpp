
#include <wcl/core/MenuItem.hpp>

#include <wcl/core/Menu.hpp>
#include "MenuHandle.hpp"


namespace wcl::core {
    struct MenuItem::Impl {
        const Menu* const mParent;
        const int mId;

        HMENU getParentHandle() const {
            return mParent->getHandle()->hMenu;
        }
    };


    MenuItem::MenuItem(const Menu *parent, const int id) 
        : mImpl(new MenuItem::Impl{parent, id}) {}


    MenuItem::~MenuItem() {}


    bool MenuItem::isEnabled() const {
        MENUITEMINFO itemInfo = {};
        itemInfo.cbSize = sizeof(MENUITEMINFO);
        itemInfo.fMask = MIIM_STATE;
    
        ::GetMenuItemInfo(mImpl->getParentHandle(), mImpl->mId, FALSE, &itemInfo);

        if (itemInfo.fState & MFS_ENABLED) {
            return true;
        }

        return false;

        /*
        std::wstring buffer;
        buffer.resize(static_cast<size_t>(itemInfo.cch) + 1);

        itemInfo.dwTypeData = buffer.data();

        ::GetMenuItemInfo(mImpl->getParentHandle(), mImpl->mId, FALSE, &itemInfo);
        */

        return true;
    }


    void MenuItem::setEnabled(const bool value) {
        ::EnableMenuItem(mImpl->getParentHandle(), mImpl->mId, MF_BYCOMMAND | (value ? MF_ENABLED : MF_DISABLED));
    }


    bool MenuItem::isChecked() const {
        return false;
    }


    void MenuItem::setChecked(const bool value) {

    }
}
