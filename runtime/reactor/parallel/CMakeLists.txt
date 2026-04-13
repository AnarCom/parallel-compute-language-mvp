add_library(ParallelReactor repository.cpp)

target_include_directories(ParallelReactor PUBLIC ${CMAKE_SOURCE_DIR} PRIVATE .)
target_link_libraries(ParallelReactor PUBLIC ReactorCommon)