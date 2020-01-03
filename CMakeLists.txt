cmake_minimum_required(VERSION 3.16.2)

project(
    GameProgrammingExcercises
    VERSION     0.1
    DESCRIPTION 
"An introduction to various game programming practices\
 and programming books via a series of excercises, samples\
 and a custom engine built with minimum effort in mind."
    LANGUAGES   CXX
)

set(BUILD_LAZYE_SHARED ${BUILD_SHARED_LIBS} CACHE BOOL "Build lazye dynamically or statically" FORCE)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Add directories for dependencies, the engine and the practice part
add_subdirectory(extern)
add_subdirectory(engine)
add_subdirectory(practice)