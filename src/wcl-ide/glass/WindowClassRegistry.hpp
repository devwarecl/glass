
#pragma once

#include <set>
#include <string>
#include "common.hpp"

namespace glass {
    class Registry {
    public:
        ~Registry();

        void add(const char *className, WNDPROC wndProc);
        
        template<typename DerivedWindow>
        void add() {
            this->add(computeClassName<DerivedWindow>(), &DerivedWindow::WindowProc);
        }

    private:
        std::set<std::string> classNames;
    };
}
