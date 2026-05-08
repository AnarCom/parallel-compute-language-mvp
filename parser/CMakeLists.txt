
# minimum required CMAKE version
CMAKE_MINIMUM_REQUIRED(VERSION 3.7 FATAL_ERROR)

project(Lang)

# compiler must be 17
set(CMAKE_CXX_STANDARD 17)

include_directories(antlr4_runtime/src)

add_subdirectory(antlr4_runtime)
add_subdirectory(generated)

add_executable(parser main.cpp)

target_link_libraries(parser antlr4_static generated)
