
set (target "wcl-ide")
set (sources 
	"MainApplication.cpp" 
	"MainApplication.hpp" 
	"MainWindow.cpp" 
	"MainWindow.hpp" 
	"Main.cpp" 
)

add_executable(${target} WIN32 ${sources})
