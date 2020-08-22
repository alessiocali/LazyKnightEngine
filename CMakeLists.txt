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
"Yet and Yet Again Another Game Engine in C++, because why not.\
 The name goes for 'LazyEngine' because it was supposed to reuse\
 as many dependencies as possible, but I'm not so sure about that\
 anymore."
    LANGUAGES   CXX
)

set(BUILD_LAZYE_SHARED ${BUILD_SHARED_LIBS})
set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(GeneratorExpressions.cmake)
include(Helpers.cmake)

set(EngineTargetName LazyE)

# Add directories for the engine and the samples
add_subdirectory(engine)
add_subdirectory(samples)