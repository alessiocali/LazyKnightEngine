#include <lazye/graphics/graphicsfactory.h>

#include <lazye/backends/backenddefines.h>

#ifdef USE_GRAPHICS_BACKEND_SDL
    #ifdef USE_GRAPHICS_API_OPENGL
        #include <lazye/backends/sdl/opengl/sdlglgraphicsfactory.h>
    #else // USE_GRAPHICS_API_OPENGL
        #include <lazye/backends/sdl/sdlgraphicsfactory.h>
    #endif
#endif // Graphics Backend

namespace lazye
{
    GraphicsFactory& GraphicsFactory::GetInstance()
    {
#ifdef USE_GRAPHICS_BACKEND_SDL
    #ifdef USE_GRAPHICS_API_OPENGL
        static SDLGLGraphicsFactory instance;
    #else // USE_GRAPHICS_API_OPENGL
        static SDLGraphicsFactory instance;
    #endif
#endif // USE_GRAPHICS_BACKEND_SDL

        return instance;
    }
}