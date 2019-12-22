
#pragma once 

#ifndef __wclc_compiler_hpp__
#define __wclc_compiler_hpp__

#include "Parser.hpp"
#include "Generator.hpp"

#include <memory>
#include <string>
#include <map>
#include <boost/filesystem/path.hpp>

namespace wclc {
    class Compiler {
    public:
        Compiler(Parser *parser, Generator *generator);

        std::map<std::string, std::string> compile(const boost::filesystem::path &input_file, const boost::filesystem::path &output_path);

    private:
        Parser *parser;
        Generator *generator;
    };
}

#endif
