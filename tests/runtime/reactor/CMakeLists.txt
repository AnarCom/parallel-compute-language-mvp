# Find the installed GoogleTest package
find_package(GTest REQUIRED)

add_executable(TestTypeSystemRunner test_types.cpp test_type_system_extended.cpp)
target_link_libraries(TestTypeSystemRunner PRIVATE GTest::GTest GTest::Main ParallelReactor)
add_test(NAME TestTypeSystem COMMAND TestTypeSystemRunner)

add_executable(TestParallelRunner test_cycle.cpp)
target_link_libraries(TestParallelRunner PRIVATE GTest::GTest GTest::Main ParallelReactor)
add_test(NAME TestParallel COMMAND TestParallelRunner)

add_executable(TestDistributedRunner test_distributed_config.cpp)
target_link_libraries(TestDistributedRunner PRIVATE GTest::GTest GTest::Main DistributedReactor)
add_test(NAME TestDistributed COMMAND TestDistributedRunner)

# Add manual test executable (no gtest dependency)
add_executable(ManualTestTypeSystem manual_test_type_system.cpp)
target_link_libraries(ManualTestTypeSystem PRIVATE ParallelReactor ReactorCommon)
add_test(NAME ManualTypeSystemTest COMMAND ManualTestTypeSystem)
