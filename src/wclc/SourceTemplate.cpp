
#include "SourceTemplate.hpp"

namespace wclc {
    std::string source_template = R"(
#include "${class}.hpp"
#include <wcl/gen/Menu.hpp>

namespace ${namespace} {

    ${command_enum}
    
    ${class}::${class}() : Frame(L"${window_class}") {}

    ${class}::~${class}() {}

    void ${class}::OnCreate() {
        ${construction_menu}    
    }
}
)";
}

