add_library(ReactorCommon interface.cpp type_system.cpp)

target_include_directories(ReactorCommon PUBLIC ${CMAKE_SOURCE_DIR} PRIVATE .)
target_link_libraries(ReactorCommon PUBLIC)