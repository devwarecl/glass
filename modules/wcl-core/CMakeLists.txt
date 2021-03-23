
set(target "wcl-core")

set(sources 
	"include/wcl/core.hpp"
	"include/wcl/core/Application.hpp"
	"include/wcl/core/Frame.hpp"
	"include/wcl/core/Control.hpp"

	"src/Application.cpp"

	"src/Frame.cpp"
	"src/Frame.Impl.cpp"
	"src/Frame.Impl.hpp"

	"src/Control.cpp"
	"src/Control.Impl.cpp"
	"src/Control.Impl.hpp"
)

add_library(${target} ${sources})

target_include_directories(${target} PUBLIC "include/")
