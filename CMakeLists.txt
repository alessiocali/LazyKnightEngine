cmake_minimum_required(VERSION 3.16.2)

set(
    CMAKE_TOOLCHAIN_FILE 
    ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake
    CACHE STRING "Vcpkg toolchain file"
)

project(
    LazyKnight
    VERSION         0.0.1
    DESCRIPTION     "A Game Engine because why not"
    LANGUAGES       CXX
)

set(BUILD_LAZYKNIGHT_SHARED ${BUILD_SHARED_LIBS})
set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(EngineTargetName LazyKnightEngine)

include(GeneratorExpressions.cmake)
include(Helpers.cmake)

# Add directories for the engine and the samples
add_subdirectory(engine)
add_subdirectory(samples)