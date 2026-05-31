cmake_minimum_required(VERSION 3.15)
project(GOJO LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(REACTOR_MAX_RUNNER_THREADS "8" CACHE STRING "Number of runner threads for the improved reactor")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

if(POLICY CMP0167)
  cmake_policy(SET CMP0167 NEW)
endif()

add_subdirectory(runtime)
add_subdirectory(examples)

enable_testing()
add_subdirectory(tests)
