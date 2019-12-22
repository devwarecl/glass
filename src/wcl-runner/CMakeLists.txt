
set (target wcl-runner)

set (sources_wcl_private
	"wcl/private/Window.hpp"
)

set (sources_wcl
	"RunnerMain.cpp"
	"wcl/Button.cpp"
	"wcl/Button.hpp"
	"wcl/Control.cpp"
	"wcl/Control.hpp"
	"wcl/Form.hpp"
	"wcl/Form.cpp"
	"wcl/Label.hpp"
	"wcl/Label.cpp"
	"wcl/Rect.hpp"
	"wcl/Rect.cpp"
	"wcl/Module.hpp"
	"wcl/Module.cpp"
)

set (sources 
	"RunnerMain.cpp"
)

source_group("\\" FILES ${sources})
source_group("\\wcl" FILES ${sources_wcl})
source_group("\\wcl\\private" FILES ${sources_wcl_private})

add_executable(${target} ${sources} ${sources_wcl} ${sources_wcl_private})
