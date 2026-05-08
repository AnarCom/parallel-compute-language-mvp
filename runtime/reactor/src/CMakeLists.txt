# Add a library target for your code
add_library(LibReactor cycle_impl.cpp interface.cpp)
target_include_directories(LibReactor PUBLIC ${CMAKE_SOURCE_DIR}/src)