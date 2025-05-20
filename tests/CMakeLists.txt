find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(JEngine REQUIRED)

# Gather test files
file(GLOB TEST_SOURCES "*.cpp")

# Create test executable
add_executable(JEngineTests ${TEST_SOURCES})


target_link_libraries(JEngineTests
    gtest
    gtest_main
    JEngine
    JEngine::JEngine
    SDL2::SDL2
    SDL2_ttf::SDL2_ttf
)

add_test(NAME JEngineTests COMMAND JEngineTests)
