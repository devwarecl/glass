#pragma once

#ifndef __wcl_module_hpp__
#define __wcl_module_hpp__

#include <memory>
#include <wcl/Exception.hpp>

namespace wcl {

    class Module {
    public:
        explicit Module(const std::string &name);
        ~Module();

        void* getAddress(const std::string &procName);

    private:
        HMODULE module = nullptr;
    };

    typedef std::unique_ptr<Module> ModulePtr;

    inline Module::Module(const std::string &name) {
        HMODULE module = ::LoadLibraryA(name.c_str());

        if (!module) {
            throw wcl::Exception("Couldn't load the module '" + name + "'");
        }
    
        this->module = module;
    }

    inline Module::~Module() {
        ::FreeLibrary(this->module);
    }

    inline void* Module::getAddress(const std::string &procName) {
        return reinterpret_cast<void*>(::GetProcAddress(this->module, procName.c_str()));
    }
}

#endif
