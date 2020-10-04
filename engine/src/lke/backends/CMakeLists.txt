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