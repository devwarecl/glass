
#pragma once

#ifndef __wcl_imagelist_hpp__
#define __wcl_imagelist_hpp__

#include <memory>
#include <Commctrl.h>
#include <wcl/Exception.hpp>

namespace wcl {

    class ImageList {
    public:
        ImageList();
        ~ImageList();

        void Create(int cx, int cy, UINT flags, int cInitial, int cGrows);
        void Destroy();

        int Add(HBITMAP hImage, HBITMAP hMask);
        int AddMasked(HBITMAP hImage, COLORREF colorMask);
        void Remove(const int index);

        HIMAGELIST GetHandle() const {
            return this->hImageList;
        }

    public:
        HIMAGELIST hImageList = NULL;
    };
    
    typedef std::unique_ptr<ImageList> ImageListPtr;

    inline ImageList::ImageList() {}

    inline ImageList::~ImageList() {
        this->Destroy();
    }

    inline void ImageList::Create(int cx, int cy, UINT flags, int cInitial, int cGrows) {
        this->Destroy();

        this->hImageList = ::ImageList_Create(cx, cy, flags, cInitial, cGrows);
    }

    inline void ImageList::Destroy() {
        if (this->hImageList) {
            ::ImageList_Destroy(this->hImageList);
            this->hImageList = NULL;
        }
    }

    inline int ImageList::Add(HBITMAP hImage, HBITMAP hMask) {
        int result = 0;

        if ((result = ::ImageList_Add(this->hImageList, hImage, hMask)) == -1) {
            throw wcl::Exception("Error while adding a bitmap to the ImageList");
        }

        return result;
    }

    inline int ImageList::AddMasked(HBITMAP hImage, COLORREF colorMask) {
        int result = 0;

        if ((result = ::ImageList_AddMasked(this->hImageList, hImage, colorMask)) == -1) {
            throw wcl::Exception("Error while adding a masked bitmap to the ImageList");
        }

        return result;
    }

    inline void ImageList::Remove(const int index) {
        ::ImageList_Remove(this->hImageList, index);
    }
}

#endif    //__wcl_imagelist_hpp__
