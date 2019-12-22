
#pragma once 

#ifndef __wclc_generator_hpp__
#define __wclc_generator_hpp__

#include "Parser.hpp"
#include <map>

namespace wclc {
    class Generator {
    public:
        Generator();
        ~Generator();

        void setFrame(const Frame &frame);

        std::string generateHeader();
        std::string generateSource();

    private:
        Frame frame;
    };
}

#endif
