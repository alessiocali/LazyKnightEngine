cmake_minimum_required(VERSION 3.14)

project(
    GameProgrammingExcercises
    VERSION     0.1
    DESCRIPTION 
"An introduction to various game programming practices\
 and programming books via a series of excercises, samples\
 and a custom engine built with minimum effort in mind."
    LANGUAGES   CXX
)

# Until I find a damn way to copy the output dlls into the executable path
set(BUILD_SHARED_LIBS FALSE CACHE BOOL "Only build static libs.")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Add directories for dependencies, the engine and the practice part
add_subdirectory(extern)
add_subdirectory(engine)
add_subdirectory(practice)