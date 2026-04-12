# Find the installed GoogleTest package
find_package(GTest REQUIRED)

# Add a test executable
add_executable(TestReactorRunner test_cycle.cpp test_types.cpp test_type_system_extended.cpp)

# Link the test executable with GTest libraries and your own library
target_link_libraries(TestReactorRunner PRIVATE GTest::GTest GTest::Main ParallelReactor)

# Add the test to CTest for automatic discovery and running
add_test(NAME TestReactor COMMAND TestReactorRunner)

# Add manual test executable (no gtest dependency)
add_executable(ManualTestTypeSystem manual_test_type_system.cpp)
target_link_libraries(ManualTestTypeSystem PRIVATE ParallelReactor ReactorCommon)
add_test(NAME ManualTypeSystemTest COMMAND ManualTestTypeSystem)
