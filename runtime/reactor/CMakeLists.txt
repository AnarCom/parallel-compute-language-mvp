cmake_minimum_required(VERSION 3.15)
project(Reactor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20) # Set C++ standard

# Enable testing with CTest
#enable_testing()

# Add source files (e.g., your library code)
set (SOURCE_FILES src/cycle_impl.cpp src/interface.cpp)

add_library(Reactor ${SOURCE_FILES})
target_include_directories(Reactor PUBLIC ${CMAKE_SOURCE_DIR}/src)

# Add tests subdirectory
#add_subdirectory(tests)