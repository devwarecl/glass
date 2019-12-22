
#pragma once

#ifndef __wcl_sizer_hpp__
#define __wcl_sizer_hpp__

#include <list>

#include "Window.hpp"

namespace wcl {

    enum class SizerStyle {
        None = 0,
        ExpandHorizontally = 1,                            // TODO: Implement in Sizer::OnSize
        ExpandVertically = 2,                            // TODO: Implement in Sizer::OnSize
        Expand = ExpandHorizontally | ExpandVertically
    };

    class Sizer {
    public:
        ~Sizer();

        void Add(Window *window, SizerStyle style);

        void OnSize(int width, int height);

    private:
        typedef std::pair<Window*, SizerStyle> WindowSizerStyle;
        std::list<WindowSizerStyle> windows;
    };

    inline Sizer::~Sizer() {}

    inline void Sizer::Add(Window *window, SizerStyle style) {
        assert(window);

        this->windows.push_back( Sizer::WindowSizerStyle(window, style) );
    }

    inline void Sizer::OnSize(int width, int height) {
        for (auto &pair : this->windows) {
            switch (pair.second) {
            case SizerStyle::Expand:
                Window *window = pair.first;
                window->SetPos(NULL, 0, 0, width, height, SWP_FRAMECHANGED);
                window->OnSize(width, height);    // TODO: Replace with 'SendMessage'
                break;
            }
        }
    }
}

#endif    // __wcl_sizer_hpp__
