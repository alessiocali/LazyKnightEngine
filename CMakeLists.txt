cmake_minimum_required(VERSION 3.16.2)

option(USE_VCPKG_TOOLCHAIN  "Use VCPKG for managing dependencies" ON)

if (USE_VCPKG_TOOLCHAIN)
    set(
        CMAKE_TOOLCHAIN_FILE
        ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake
        CACHE STRING "Vcpkg toolchain file"
    )
endif()

set(ProjectName LazyKnight)
set(ProjectNameSpace ${ProjectName})
set(LazyKnightVersion "0.0.1")
set(EngineTargetName Engine)

project(
    ${ProjectName}
    VERSION         ${LazyKnightVersion}
    DESCRIPTION     "A Game Engine because why not"
    LANGUAGES       CXX
)

option(BUILD_LAZYKNIGHT_SHARED  "Build LazyKnightEngine as a shared library" ON)
option(BUILD_LAZYKNIGHT_TESTS   "Build Tests for the Engine" ON)
option(BUILD_LAZYKNIGHT_SAMPLES "Build the Engine Samples" OFF)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(GeneratorExpressions.cmake)
include(Helpers.cmake)

# Add directories for the engine and the samples
add_subdirectory(engine)

if (BUILD_LAZYKNIGHT_SAMPLES)
    add_subdirectory(samples)
endif()