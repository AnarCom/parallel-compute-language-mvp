cmake_minimum_required(VERSION 3.15)
project(Reactor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20) # Set C++ standard

# Enable testing with CTest
enable_testing()

# Add source subdirectory (e.g., your library code)
add_subdirectory(src)

# Add tests subdirectory
add_subdirectory(tests)