
project (wcl)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories("src/wcl")

add_subdirectory("src/wcl")
add_subdirectory("src/wclc")
add_subdirectory("src/wcl-runner")
add_subdirectory("src/wcl-ide")

add_subdirectory("modules/wcl-core")
add_subdirectory("modules/wcl-editor")
