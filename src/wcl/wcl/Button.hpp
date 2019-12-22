
#pragma once

#ifndef __wcl_button_hpp__
#define __wcl_button_hpp__

#include "Window.hpp"
#include <string>

namespace wcl {
    class Button : public Window {
    public:
        Button();
    };

    inline Button::Button() : Window(WC_BUTTONW) {}
}

#endif 
