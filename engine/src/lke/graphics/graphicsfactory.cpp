#include <lke/graphics/graphicsfactory.h>

#include <lke/backends/backenddefines.h>

#ifdef USE_WINDOW_SYSTEM_SDL
    #ifdef USE_GRAPHICS_API_OPENGL
        #include <lke/backends/sdl/opengl/sdlglgraphicsfactory.h>
    #endif
#endif // Graphics Backend

namespace lke
{
    GraphicsFactory& GraphicsFactory::GetInstance()
    {
#ifdef USE_WINDOW_SYSTEM_SDL
    #ifdef USE_GRAPHICS_API_OPENGL
        static SDLGLGraphicsFactory instance;
    #else // USE_GRAPHICS_API_OPENGL
        static_assert(false, "No valid Graphics API Compatible with this Window System");
    #endif
#endif // USE_WINDOW_SYSTEM_SDL

        return instance;
    }
}