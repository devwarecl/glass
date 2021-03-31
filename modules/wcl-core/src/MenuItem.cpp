
#include <wcl/core/MenuItem.hpp>

#include "MenuHandle.hpp"

namespace wcl::core {
    struct MenuItem::Impl {
        MenuHandle mHandle;
    };


    MenuItem::MenuItem() : mImpl(new MenuItem::Impl()) {}


    MenuItem::~MenuItem() {}


    bool MenuItem::isEnabled() const {
        

        return true;
    }


    void MenuItem::setEnabled(const bool value) {

    }


    bool MenuItem::isChecked() const {
        return true;
    }


    void MenuItem::setChecked(const bool value) {

    }
}
