
set (wcl_src
    wcl/wcl.hpp 
    wcl/AcceleratorTable.hpp 
    wcl/Application.hpp 
    wcl/Bitmap.hpp 
    wcl/Button.hpp 
    wcl/COMApplication.hpp 
    wcl/COMException.hpp 
    wcl/COMResult.hpp 
    wcl/Dialog.hpp 
    wcl/Edit.hpp 
    wcl/Exception.hpp 
    wcl/Frame.hpp 
    wcl/ImageList.hpp
    wcl/Menu.hpp 
    wcl/Module.hpp 
    wcl/Rect.hpp 
    wcl/Scintilla.cpp 
    wcl/Scintilla.hpp 
    wcl/Sizer.hpp 
    wcl/Static.hpp 
    wcl/TabControl.hpp 
    wcl/TreeView.hpp
    wcl/Window.hpp 
    wcl/WindowBase.hpp 
    wcl/WindowClass.hpp 
    wcl/WindowHandle.hpp 
)

set (wcl_gen_src
    wcl/gen/Menu.hpp 
)

set (wcl_ex_src
    wcl/ex/TabbedPanel.hpp 
)

set (wcl_util_src
    wcl/util/String.hpp 
)

source_group (wcl       FILES ${wcl_src})
source_group (wcl\\gen  FILES ${wcl_gen_src})
source_group (wcl\\ex   FILES ${wcl_ex_src})
source_group (wcl\\util	FILES ${wcl_util_src})

add_library (wcl 
    ${wcl_src}
    ${wcl_gen_src}
    ${wcl_ex_src}
    ${wcl_util_src}
    ${wcl_xml_src}
)
