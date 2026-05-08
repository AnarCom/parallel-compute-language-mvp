# Find the installed GoogleTest package
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

add_executable(TestTypeSystemRunner test_types.cpp test_type_system_extended.cpp)
target_link_libraries(TestTypeSystemRunner PRIVATE GTest::GTest GTest::Main ParallelReactor)
add_test(NAME TestTypeSystem COMMAND TestTypeSystemRunner)

add_executable(TestParallelRunner test_cycle.cpp)
target_link_libraries(TestParallelRunner PRIVATE GTest::GTest GTest::Main ParallelReactor)
add_test(NAME TestParallel COMMAND TestParallelRunner)

add_executable(TestDistributedConfigRunner test_distributed_config.cpp)
target_link_libraries(TestDistributedConfigRunner PRIVATE GTest::GTest GTest::Main DistributedReactor)
add_test(NAME TestDistributedConfig COMMAND TestDistributedConfigRunner)

add_executable(TestDistributedRedisClientRunner test_distributed_redis_client.cpp)
target_link_libraries(TestDistributedRedisClientRunner PRIVATE GTest::GTest GTest::Main DistributedReactor)
add_test(NAME TestDistributedRedisClient COMMAND TestDistributedRedisClientRunner)

# Add manual test executable (no gtest dependency)
add_executable(ManualTestTypeSystem manual_test_type_system.cpp)
target_link_libraries(ManualTestTypeSystem PRIVATE ParallelReactor ReactorCommon)
add_test(NAME ManualTypeSystemTest COMMAND ManualTestTypeSystem)

# -------------------------------------------------------------------
# Runtime reactor tests
# -------------------------------------------------------------------

set(REACTOR_TEST_SOURCES
    runtime/reactor/test_lifecycle.cpp
    runtime/reactor/test_firing_model.cpp
    runtime/reactor/test_events.cpp
    runtime/reactor/test_error_handler.cpp
    runtime/reactor/test_integration.cpp
)

foreach(TEST_SOURCE ${REACTOR_TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)

    add_executable(${TEST_NAME} ${TEST_SOURCE})

    target_link_libraries(${TEST_NAME}
        PRIVATE
        ReactorCommon
        Threads::Threads
    )

    target_include_directories(${TEST_NAME}
        PRIVATE
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/runtime/reactor
    )

    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()

message(STATUS "Configured runtime reactor tests:")
foreach(TEST_SOURCE ${REACTOR_TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    message(STATUS "  - ${TEST_NAME}")
endforeach()