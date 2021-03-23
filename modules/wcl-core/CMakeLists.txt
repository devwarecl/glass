
set(target "wcl-core")

set(sources 
	"include/wcl/core.hpp"
	"include/wcl/core/Application.hpp"
	"include/wcl/core/Frame.hpp"
	"include/wcl/core/Control.hpp"
	"include/wcl/core/Rect.hpp"

	"src/Application.cpp"
	"src/Frame.cpp"
	"src/Control.cpp"

	"src/Window.hpp"
	"src/Window.cpp"
)

add_library(${target} ${sources})

target_include_directories(${target} PUBLIC "include/")
