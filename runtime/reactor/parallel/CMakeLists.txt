add_library(ParallelReactor repository.cpp)

target_include_directories(ParallelReactor PUBLIC . ../common)
target_link_libraries(ParallelReactor PUBLIC ReactorCommon)