
#include "HeaderTemplate.hpp"

namespace wclc {
    std::string header_template = R"(
#pragma once

#ifndef __${namespace}_${class}_hpp__
#define __${namespace}_${class}_hpp__

#include <wcl/Frame.hpp>

${header_members}

${header_menu}
${header_accelerators}

namespace ${namespace} {
    class ${class} : public wcl::Frame {
    public:
        ${class} ();
        ~${class} ();
        
        virtual void OnCreate() override;
        
    private:
        ${member_menu}
        ${member_accelerators}
        ${member_childs}
    };
}

#endif
)";
}

