cmake_minimum_required(VERSION 3.16.2)

set(
    CMAKE_TOOLCHAIN_FILE 
    ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake
    CACHE STRING "Vcpkg toolchain file"
)

project(
    GameProgrammingExcercises
    VERSION     0.1
    DESCRIPTION 
"An introduction to various game programming practices\
 and programming books via a series of excercises, samples\
 and a custom engine built with minimum effort in mind."
    LANGUAGES   CXX
)

set(BUILD_LAZYE_SHARED ${BUILD_SHARED_LIBS})
set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(GeneratorExpressions.cmake)
include(Helpers.cmake)

set(EngineTargetName LazyE)

# Add directories for the engine and the practice part
add_subdirectory(engine)
add_subdirectory(practice)