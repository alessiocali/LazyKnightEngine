# Find SDL packages
find_package(SDL2 CONFIG REQUIRED)
find_package(sdl2-image CONFIG REQUIRED)

# Link dependencies
target_link_libraries( 
    ${EngineTargetName}
    PRIVATE
        SDL2::SDL2
        SDL2::SDL2_image
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