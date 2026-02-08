# Find the installed GoogleTest package
find_package(GTest REQUIRED)

# Add a test executable
add_executable(TestReactorRunner test_cycle.cpp)

# Link the test executable with GTest libraries and your own library
target_link_libraries(TestReactorRunner PRIVATE GTest::GTest GTest::Main LibReactor)

# Add the test to CTest for automatic discovery and running
add_test(NAME TestReactor COMMAND TestReactorRunner)
