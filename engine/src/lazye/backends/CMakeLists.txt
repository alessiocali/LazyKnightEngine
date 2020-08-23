# We might support switching in the future, for the moment it will stay the default
set ( USE_GRAPHICS_BACKEND_SDL TRUE )

configure_file( cmake/BackendDefines.h.in backenddefines.h )

target_sources( 
    ${EngineTargetName}
    PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}/backenddefines.h
)

if ( USE_GRAPHICS_BACKEND_SDL )
    add_subdirectory( sdl )
endif()