if ( NOT USE_GRAPHICS_API_OPENGL )
    message( FATAL_ERROR "SDL to OpenGL integration requires OpenGL backend to be built!")
endif()

target_sources(
    ${EngineTargetName}

    PRIVATE

    sdlglgraphicsfactory.h
    sdlglgraphicsfactory.cpp

    sdlglcontext.h
    sdlglcontext.cpp
    
    sdlglrenderingcontext.h
    sdlglrenderingcontext.cpp

    sdlglsprite.h
    sdlglsprite.cpp

    sdlglwindow.h
    sdlglwindow.cpp
)