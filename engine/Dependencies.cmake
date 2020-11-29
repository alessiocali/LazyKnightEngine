# All dependencies need to be handled at the top level otherwise when building the static 
# library INTERFACE_LINK_LIBRARIES will refer to local directory IDs, making a mess
#
# For more informations, here are the fruits of my hours spent pouring over Google
#
# https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_LINK_LIBRARIES.html
# https://cmake.org/cmake/help/latest/manual/cmake-packages.7.html#creating-relocatable-packages
# https://gitlab.kitware.com/cmake/cmake/-/issues/17943

# We might support switching in the future, for the moment it will stay the default
set ( USE_WINDOW_SYSTEM_SDL     TRUE )
set ( USE_GRAPHICS_API_OPENGL   TRUE )
set ( USE_MODEL_LOADER_ASSIMP   TRUE )
set ( USE_TEXTURE_LOADER_SDL    TRUE )

## ASSIMP ##
if (USE_MODEL_LOADER_ASSIMP)
    # Find Assimp packages
    add_lke_dependencies(assimp)
    find_package(Assimp CONFIG REQUIRED)

    # Add Assimp includes
    target_link_libraries(${EngineTargetName} PRIVATE assimp::assimp)
endif()

## GLAD ##
if (USE_GRAPHICS_API_OPENGL)
    # Find OpenGL and helper packages
    add_lke_dependencies(glad)
    find_package(glad CONFIG REQUIRED)

    # Link dependencies
    target_link_libraries(${EngineTargetName} PRIVATE glad::glad)

    # Add OpenGL includes
    target_include_directories(${EngineTargetName} PRIVATE ${GLAD_INCLUDE_DIRS})
endif()

## SDL ##
if ( USE_WINDOW_SYSTEM_SDL OR USE_TEXTURE_LOADER_SDL )
    # Find SDL packages
    add_lke_dependencies(SDL2 sdl2-image)

    find_package(SDL2 CONFIG REQUIRED)
    find_package(sdl2-image CONFIG REQUIRED)

    # Link dependencies
    target_link_libraries(${EngineTargetName} PRIVATE SDL2::SDL2 SDL2::SDL2_image)
endif()