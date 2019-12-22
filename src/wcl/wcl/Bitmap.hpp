#pragma once

#ifndef __wcl_bitmap_hpp__
#define __wcl_bitmap_hpp__

#include <memory>
#include <string>
#include <WinDef.h>
#include <Wingdi.h>
#include <Winuser.h>

#include <wcl/Exception.hpp>
#include <wcl/util/String.hpp>

namespace wcl {
    class Bitmap {
    public:
        ~Bitmap();

        HBITMAP GetHandle() const;

        void Delete();

    private:
        HBITMAP hBitmap = NULL;

    public:
        static std::unique_ptr<Bitmap> Load(const std::wstring &file);
    };


    inline Bitmap::~Bitmap() {
        this->Delete();
    }

    inline HBITMAP Bitmap::GetHandle() const {
        return this->hBitmap;
    }

    inline void Bitmap::Delete() {
        if (this->hBitmap) {
            ::DeleteObject(this->hBitmap);
            this->hBitmap = NULL;
        }
    }

    inline std::unique_ptr<Bitmap> Bitmap::Load(const std::wstring &file) {
        auto bitmap = std::make_unique<Bitmap>();
        UINT flags = LR_LOADFROMFILE | LR_CREATEDIBSECTION;

        bitmap->hBitmap = (HBITMAP)::LoadImage(NULL, file.c_str(), IMAGE_BITMAP, 0, 0, flags);

        if (!bitmap->hBitmap) {
            throw wcl::Exception("Error while loading the bitmap '" + ToString(file) + "'");
        }

        return bitmap;
    }
}

#endif    // __wcl_bitmap_hpp__
