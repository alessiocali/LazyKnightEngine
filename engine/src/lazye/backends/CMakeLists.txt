# We might support switching in the future, for the moment it will stay the default
set ( USE_WINDOW_SYSTEM_SDL TRUE )
set ( USE_GRAPHICS_API_OPENGL TRUE)
set ( USE_MODEL_LOADER_ASSIMP TRUE )
set ( USE_TEXTURE_LOADER_SDL TRUE )

configure_file( cmake/BackendDefines.h.in backenddefines.h )

target_sources( 
    ${EngineTargetName}
    PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}/backenddefines.h
)

if ( USE_WINDOW_SYSTEM_SDL OR USE_TEXTURE_LOADER_SDL )
    add_subdirectory( sdl )
endif()

if ( USE_GRAPHICS_API_OPENGL )
    add_subdirectory( opengl )
endif()

if ( USE_MODEL_LOADER_ASSIMP )
    add_subdirectory( assimp )
endif()