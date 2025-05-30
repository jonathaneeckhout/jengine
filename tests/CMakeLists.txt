include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

# Gather test files
file(GLOB TEST_SOURCES "*.cpp")

# Create test executable
add_executable(JEngineTests ${TEST_SOURCES})

target_link_libraries(JEngineTests PRIVATE
    JEngine
    gtest_main
)

add_test(NAME JEngineTests COMMAND JEngineTests)
