
#pragma once

#ifndef __wcl_treeview_hpp__
#define __wcl_treeview_hpp__

#include <wcl/Window.hpp>
#include <wcl/ImageList.hpp>
#include <Commctrl.h>

namespace wcl {

    struct TreeViewItemData : public TVITEM {
        static TreeViewItemData Create(/*HTREEITEM hItem, */const std::wstring &text);
        static TreeViewItemData Create(/*HTREEITEM hItem, */const std::wstring &text, const int image, const int selectedImage);
    };

    inline TreeViewItemData TreeViewItemData::Create(/*HTREEITEM hItem, */const std::wstring &text) {
        TreeViewItemData item = {};

        // item.hItem = hItem;
        item.mask = TVIF_TEXT;
        item.pszText = (LPWSTR)text.c_str();

        return item;
    }

    inline TreeViewItemData TreeViewItemData::Create(/*HTREEITEM hItem, */const std::wstring &text, const int image, const int selectedImage) {
        TreeViewItemData item = {};

        // item.hItem = hItem;
        item.mask = TVIF_TEXT | TVIF_IMAGE;
        item.pszText = (LPWSTR)text.c_str();
        item.iImage = image;
        item.iSelectedImage = selectedImage;

        return item;
    }

    class TreeView : public Window {
    public:
        TreeView();

        void SetImageList(const int imageListType, const ImageList *imageList);

        HTREEITEM InsertItem(const TreeViewItemData &itemData, HTREEITEM parent, HTREEITEM insertAfter);

        HTREEITEM InsertItem(const TVINSERTSTRUCT insert);

    private:

    };
    
    typedef std::unique_ptr<TreeView> TreeViewPtr;

    inline TreeView::TreeView() : Window(WC_TREEVIEW) {}

    inline void TreeView::SetImageList(const int imageListType, const ImageList *imageList) {
        this->SendMessage_(TVM_SETIMAGELIST, imageListType, imageList->GetHandle());
    }

    inline HTREEITEM TreeView::InsertItem(const TreeViewItemData &itemData, HTREEITEM parent, HTREEITEM insertAfter) {
        TVINSERTSTRUCT insert = {};

        insert.item = static_cast<TVITEM>(itemData);
        insert.hParent = parent;
        insert.hInsertAfter = insertAfter;

        HTREEITEM hItem = (HTREEITEM)this->SendMessage_(TVM_INSERTITEM, 0, (LPARAM)&insert);

        return hItem;
    }

    inline HTREEITEM TreeView::InsertItem(const TVINSERTSTRUCT insert) {
        HTREEITEM hItem = (HTREEITEM)this->SendMessage_(TVM_INSERTITEM, 0, (LPARAM)&insert);

        return hItem;
    }
}

#endif
