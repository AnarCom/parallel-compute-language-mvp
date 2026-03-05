
# minimum required CMAKE version
CMAKE_MINIMUM_REQUIRED(VERSION 3.7 FATAL_ERROR)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(parser)

# compiler must be 17
set(CMAKE_CXX_STANDARD 17)

include_directories(antlr4_runtime/src)

add_subdirectory(antlr4_runtime)
add_subdirectory(generated)

add_executable(${PROJECT_NAME} main.cpp visitor/visitor.cpp)

target_link_libraries(${PROJECT_NAME} antlr4_static generated)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
