
set (target "wclc")
set (sources
    wclc.cpp
    Compiler.cpp 
	Compiler.hpp 
    CompilerXML.cpp 
	CompilerXML.hpp 
    HeaderTemplate.cpp 
	HeaderTemplate.hpp 
    SourceTemplate.cpp 
	SourceTemplate.hpp 
    Generator.cpp 
	Generator.hpp
    Parser.cpp 
	Parser.hpp
    ParserXML.cpp 
	ParserXML.hpp
)

source_group (\\  FILES ${sources})

add_executable(${target} ${sources})

# target_link_libraries(wclc comctl32 ${Boost_LIBRARIES})
target_link_libraries(wclc comctl32)

set_property(TARGET wclc PROPERTY CXX_STANDARD 14)

install(TARGETS wclc DESTINATION ".")
