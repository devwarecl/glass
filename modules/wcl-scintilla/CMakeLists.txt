
set (target wcl-scintilla)

set (sources 
	"include/wcl/sci/Scintilla.h"
	"src/Scintilla.cpp"
)

add_library(${target} ${sources})
target_include_directories(${target} PUBLIC "include")
target_link_libraries(${target} wcl-core)
