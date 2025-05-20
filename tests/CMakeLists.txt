# Gather test files
file(GLOB TEST_SOURCES "*.cpp")

# Create test executable
add_executable(JEngineTests ${TEST_SOURCES})

target_link_libraries(JEngineTests gtest gtest_main JEngine)
add_test(NAME JEngineTests COMMAND JEngineTests)
