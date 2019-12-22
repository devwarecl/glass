
ADD_EXECUTABLE(wclc 
    wclc.cpp
    Compiler.cpp Compiler.hpp 
    CompilerXML.cpp CompilerXML.hpp 
    HeaderTemplate.cpp HeaderTemplate.hpp 
    SourceTemplate.cpp SourceTemplate.hpp 
    Generator.cpp Generator.hpp
    Parser.cpp Parser.hpp
    ParserXML.cpp ParserXML.hpp
)
TARGET_LINK_LIBRARIES(wclc comctl32 ${Boost_LIBRARIES})
# TARGET_LINK_LIBRARIES(wclc comctl32)

SET_PROPERTY(TARGET wclc PROPERTY CXX_STANDARD 14)

INSTALL(TARGETS wclc DESTINATION ".")
