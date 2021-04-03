
set(target "wcl-core")

set(sources 
	"include/wcl/core.hpp"
	"include/wcl/core/Application.hpp"
	"include/wcl/core/Frame.hpp"
	"include/wcl/core/Control.hpp"
	"include/wcl/core/Rect.hpp"
	"include/wcl/core/MenuBar.hpp"
	"include/wcl/core/Menu.hpp"
	"include/wcl/core/MenuItem.hpp"
	"include/wcl/core/Action.hpp"
	"include/wcl/core/EventRaiser.hpp"
	"include/wcl/core/Widget.hpp"
	"include/wcl/core/WidgetPrivate.h"
	"include/wcl/core/ComboBox.hpp"
	"include/wcl/core/Button.h"
	"include/wcl/core/Edit.h"
	"include/wcl/core/Label.h"
	
	"src/Application.cpp"
	"src/Frame.cpp"
	"src/Control.cpp"
	"src/MenuBar.cpp"
	"src/Menu.cpp"
	"src/MenuItem.cpp"
	"src/Action.cpp"
	"src/EventRaiser.cpp"
	"src/Widget.cpp"
	"src/WidgetPrivate.cpp"
	"src/ComboBox.cpp"
	"src/Button.cpp"
	"src/Edit.cpp"
	"src/Label.cpp"

	"src/Window.hpp"
	"src/Window.cpp"

	"src/MenuHandle.hpp"
	"src/MenuHandle.cpp"

	"src/WinUtil.hpp"
	"src/WinUtil.cpp"
)

add_library(${target} ${sources})

target_include_directories(${target} PUBLIC "include/")
