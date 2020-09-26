# We might support switching in the future, for the moment it will stay the default
set ( USE_GRAPHICS_BACKEND_SDL TRUE )
set ( USE_ASSET_LOADER_ASSIMP TRUE )

option ( USE_GRAPHICS_API_OPENGL "Enables OpenGL as a Graphics API. This is the default." ON )

configure_file( cmake/BackendDefines.h.in backenddefines.h )

target_sources( 
    ${EngineTargetName}
    PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}/backenddefines.h
)

if ( USE_GRAPHICS_BACKEND_SDL )
    add_subdirectory( sdl )
endif()

if ( USE_GRAPHICS_API_OPENGL )
    add_subdirectory( opengl )
endif()

if ( USE_ASSET_LOADER_ASSIMP )
    add_subdirectory( assimp )
endif()