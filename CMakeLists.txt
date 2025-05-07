cmake_minimum_required(VERSION 3.16)
project(JEngine VERSION 1.0 LANGUAGES CXX)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Use clang++ and set flags
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

# Find SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Find SDL2_ttf
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_TTF_INCLUDE_DIRS})

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create library target
add_library(JEngine ${SOURCES})

# Public include directories (for consumers)
target_include_directories(JEngine
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(JEngine
    ${SDL2_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
)

# Install library
install(TARGETS JEngine
    EXPORT JEngineTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

# Install public headers
install(DIRECTORY include/ DESTINATION include)

# Export targets
install(EXPORT JEngineTargets
    FILE JEngineTargets.cmake
    NAMESPACE JEngine::
    DESTINATION lib/cmake/JEngine
)

# Generate config files
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/JEngineConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_LIST_DIR}/cmake/JEngineConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/JEngineConfig.cmake"
    INSTALL_DESTINATION lib/cmake/JEngine
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/JEngineConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/JEngineConfigVersion.cmake"
    DESTINATION lib/cmake/JEngine
)

# Add uninstall target
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY
)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
)
