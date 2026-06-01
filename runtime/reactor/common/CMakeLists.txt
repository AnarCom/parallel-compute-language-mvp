add_library(ReactorCommon
    interface.cpp
    type_system.cpp
    lifecycle.cpp
    firing.cpp
    events.cpp
    event_emitter.cpp
    event_logger.cpp
    error_handler.cpp
)

target_include_directories(ReactorCommon PUBLIC ${CMAKE_SOURCE_DIR} PRIVATE .)
target_link_libraries(ReactorCommon PUBLIC)

set_source_files_properties(error_handler.cpp PROPERTIES COMPILE_FLAGS "-w")
set_source_files_properties(error_handler.hpp PROPERTIES COMPILE_FLAGS "-w")
set_source_files_properties(event_emitter.cpp PROPERTIES COMPILE_FLAGS "-w")
set_source_files_properties(event_emitter.hpp PROPERTIES COMPILE_FLAGS "-w")
set_source_files_properties(event_logger.cpp PROPERTIES COMPILE_FLAGS "-w")
set_source_files_properties(event_logger.hpp PROPERTIES COMPILE_FLAGS "-w")
set_source_files_properties(events.cpp PROPERTIES COMPILE_FLAGS "-w")
set_source_files_properties(events.hpp PROPERTIES COMPILE_FLAGS "-w")
set_source_files_properties(firing.cpp PROPERTIES COMPILE_FLAGS "-w")
set_source_files_properties(firing.hpp PROPERTIES COMPILE_FLAGS "-w")
set_source_files_properties(lifecycle.cpp PROPERTIES COMPILE_FLAGS "-w")
set_source_files_properties(lifecycle.hpp PROPERTIES COMPILE_FLAGS "-w")