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