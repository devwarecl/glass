
#pragma once

#ifndef __wcl_tabcontrol_hpp__
#define __wcl_tabcontrol_hpp__

#include <Commctrl.h>
#include <string>
#include "Window.hpp"

namespace wcl {

    struct TabControlItem : public TCITEM {
        static TabControlItem Text(const std::wstring &text);
    };

    class TabControl : public Window {
    public:
        TabControl();

    public:
        LRESULT InsertItem(const int index, const TabControlItem &item);

        LRESULT AdjustRect(BOOL bLarger, Rect *rect) const;

        LRESULT DeleteAllItems();

        LRESULT DeleteItem(const int index);

        LRESULT DeselectAll(BOOL allButThis);

        LRESULT GetCurFocus() const;

        LRESULT GetCurSel() const;

        LRESULT GetExtendedStyle() const;

        LRESULT GetImageList() const;

        LRESULT GetItem(const int index, TabControlItem *item) const;

        LRESULT GetItemCount() const;

        LRESULT GetItemRect(const int index, Rect *rect) const;

        LRESULT GetRowCount() const;

        LRESULT GetToolTips() const;

        LRESULT GetUnicodeFormat() const;

        LRESULT HighlightItem(const int index, BOOL hightlight);

        LRESULT HitTest(TCHITTESTINFO *info) const;

        LRESULT RemoveImage(const int index);

        LRESULT SetCurFocus(const int index);

        LRESULT SetCurSel(const int index);

        LRESULT SetImageList(const int imageListHandle);

        LRESULT SetItem(const int index, const TabControlItem &item);

        LRESULT SetToolTips(const int tooltipHandle);
    };

    inline TabControlItem TabControlItem::Text(const std::wstring &text) {
        TabControlItem item = {};

        item.pszText = const_cast<LPWSTR>(text.c_str());
        item.mask = TCIF_TEXT;

        return item;
    }

    inline TabControl::TabControl() : Window(WC_TABCONTROL) {}

    inline LRESULT TabControl::InsertItem(const int index, const TabControlItem &item) {
        return this->SendMessage_(TCM_INSERTITEM, index, &item);
    }

    inline LRESULT TabControl::AdjustRect(BOOL bLarger, Rect *rect) const {
        return this->SendMessage_(TCM_ADJUSTRECT, bLarger, rect);
    }

    inline LRESULT TabControl::DeleteAllItems() {
        return this->SendMessage_(TCM_DELETEALLITEMS);
    }

    inline LRESULT TabControl::DeleteItem(const int index) {
        return this->SendMessage_(TCM_DELETEITEM, index);
    }

    inline LRESULT TabControl::DeselectAll(BOOL allButThis) {
        return this->SendMessage_(TCM_DESELECTALL, allButThis);
    }

    inline LRESULT TabControl::GetCurFocus() const {
        return this->SendMessage_(TCM_GETCURFOCUS);
    }

    inline LRESULT TabControl::GetCurSel() const {
        return this->SendMessage_(TCM_GETCURSEL);
    }

    inline LRESULT TabControl::GetExtendedStyle() const {
        return this->SendMessage_(TCM_GETEXTENDEDSTYLE);
    }

    inline LRESULT TabControl::GetImageList() const {
        return this->SendMessage_(TCM_GETIMAGELIST);
    }

    inline LRESULT TabControl::GetItem(const int index, TabControlItem *item) const {
        return this->SendMessage_(TCM_GETITEM, index, item);
    }

    inline LRESULT TabControl::GetItemCount() const {
        return this->SendMessage_(TCM_GETITEMCOUNT);
    }

    inline LRESULT TabControl::GetItemRect(const int index, Rect *rect) const {
        return this->SendMessage_(TCM_GETITEMRECT, index, rect);
    }

    inline LRESULT TabControl::GetRowCount() const {
        return this->SendMessage_(TCM_GETROWCOUNT);
    }

    inline LRESULT TabControl::GetToolTips() const {
        return this->SendMessage_(TCM_GETTOOLTIPS);
    }

    inline LRESULT TabControl::GetUnicodeFormat() const {
        return this->SendMessage_(TCM_GETUNICODEFORMAT);
    }

    inline LRESULT TabControl::HighlightItem(const int index, BOOL hightlight) {
        return this->SendMessage_(TCM_HIGHLIGHTITEM, index, MAKEWPARAM(hightlight, 0));
    }

    inline LRESULT TabControl::HitTest(TCHITTESTINFO *info) const {
        return this->SendMessage_(TCM_HITTEST, NULL, info);
    }

    inline LRESULT TabControl::RemoveImage(const int index) {
        return this->SendMessage_(TCM_REMOVEIMAGE, index);
    }

    inline LRESULT TabControl::SetCurFocus(const int index) {
        return this->SendMessage_(TCM_SETCURFOCUS, index);
    }

    inline LRESULT TabControl::SetCurSel(const int index) {
        return this->SendMessage_(TCM_SETCURSEL, index);
    }

    inline LRESULT TabControl::SetImageList(const int imageListHandle) {
        return this->SendMessage_(TCM_SETIMAGELIST, 0L, imageListHandle);
    }

    inline LRESULT TabControl::SetItem(const int index, const TabControlItem &item) {
        return this->SendMessage_(TCM_SETITEM, index, &item);
    }

    inline LRESULT TabControl::SetToolTips(const int tooltipHandle) {
        return this->SendMessage_(TCM_SETTOOLTIPS, tooltipHandle);
    }
}

#endif 
