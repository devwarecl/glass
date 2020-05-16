
set (target "wcl-ide")
set (sources 
	"glass.cpp" 
	"glass.hpp" 
	"Main.cpp" 
)

add_executable(${target} WIN32 ${sources})
