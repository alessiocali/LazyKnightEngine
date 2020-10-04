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