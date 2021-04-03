
#include <wcl/core/ComboBox.hpp>

#include <wcl/core/WidgetPrivate.h>

#include <windowsx.h>
#include "WinUtil.hpp"

namespace wcl::core {
    ComboBox::ComboBox() {
        getImpl()->mClassName = "COMBOBOX";
        getImpl()->mStyle = WS_CHILD;
    }


    ComboBox::~ComboBox() {}

    
    size_t ComboBox::getItemCount() const {
        auto hWnd = getImpl()->getHwnd();

        return static_cast<size_t>(ComboBox_GetCount(hWnd));
    }


    //std::string ComboBox::getItem(const size_t index) const {

    //}

    //void ComboBox::setItem(const size_t index, const std::string &value) {

    //}


    void ComboBox::addItem(const std::string &value) {
        auto hWnd = getImpl()->getHwnd();

        ComboBox_AddString(hWnd, value.c_str());
    }


    void ComboBox::remoteItem(const size_t index) {
        auto hWnd = getImpl()->getHwnd();

    }


    std::optional<size_t> ComboBox::getSelectedIndex() const {
        auto hWnd = getImpl()->getHwnd();

        const auto selectedIndex = ComboBox_GetCurSel(hWnd);

        if (selectedIndex == CB_ERR) {
            return {};
        }

        return static_cast<size_t>(selectedIndex);
    }


    void ComboBox::clear() {
        auto hWnd = getImpl()->getHwnd();

        ComboBox_ResetContent(hWnd);
    }
}
