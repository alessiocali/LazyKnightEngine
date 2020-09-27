# Find SDL packages
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# Link dependencies
target_link_libraries( 
    ${EngineTargetName}
    PRIVATE
        SDL2::SDL2
        ${SDL2_IMAGE_LIBRARIES}
)

# Add SDL includes
target_include_directories(
    ${EngineTargetName}
    PRIVATE
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
)

target_sources( ${EngineTargetName}
    PRIVATE
    sdlheader.h

    sdlhelper.h

    sdlsystem.h
    sdlsystem.cpp

    sdlwindowbase.h
    sdlwindowbase.cpp
)

if ( USE_TEXTURE_LOADER_SDL )
    add_subdirectory(assets)
endif()

if ( USE_GRAPHICS_API_OPENGL )
    add_subdirectory(opengl)
endif()