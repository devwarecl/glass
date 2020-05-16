
include_directories(".")

set (target "wcl-ide")
set (sources 
	"glass/core.hpp" 
	"glass/common.cpp" 
	"glass/common.hpp" 
	"glass/AbstractWindow.hpp" 
	"glass/CustomWindow.hpp" 
	"glass/MessageLoop.cpp" 
	"glass/MessageLoop.hpp" 
	"glass/Window.cpp" 
	"glass/Window.hpp" 
	"glass/WindowClassRegistry.cpp" 
	"glass/WindowClassRegistry.hpp" 
	"Main.cpp" 
)

add_executable(${target} WIN32 ${sources})
