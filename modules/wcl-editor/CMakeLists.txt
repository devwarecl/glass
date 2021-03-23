
set(target "wcl-editor")
set(sources "src/main.cpp")

add_executable(${target} ${sources})
target_link_libraries(${target} wcl-core)
