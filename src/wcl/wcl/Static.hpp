
#pragma once

#ifndef __wcl_static_hpp__
#define __wcl_static_hpp__

#include "Window.hpp"

namespace wcl {
    class Static : public Window {
    public:
        Static();
    };
    
    inline Static::Static() : Window(L"STATIC") {}
}
    
#endif
