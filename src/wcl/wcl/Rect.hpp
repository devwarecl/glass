
#pragma once

#ifndef __wcl_rect_hpp__
#define __wcl_rect_hpp__

#include <Windows.h>

namespace wcl {
    struct Rect : public RECT {
        Rect();
        Rect(int left, int top, int right, int bottom);

        int GetWidth() const;
        int GetHeight() const;

        bool IsValid() const;
    };

    inline int Rect::GetWidth() const {
        return this->right - this->left;
    }

    inline int Rect::GetHeight() const {
        return this->bottom - this->top;
    }

    inline Rect::Rect() {
        this->left = this->top = 0;
        this->right = this->bottom = 0;
    }

    inline Rect::Rect(int left, int top, int right, int bottom) {
        this->left = left;
        this->top = top;
        this->right = right;
        this->bottom = bottom;
    }

    inline bool Rect::IsValid() const {
        return this->GetWidth() <= 0 || this->GetHeight() <= 0;
    }
}

#endif
