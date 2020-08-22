#include <lazye/graphics/graphicsfactory.h>

#include <lazye/backends/backenddefines.h>

#if defined(USE_GRAPHICS_BACKEND_SDL)
#include <lazye/backends/sdl/sdlgraphicsfactory.h>
#endif // Graphics Backend

namespace lazye
{
    GraphicsFactory& GraphicsFactory::GetInstance()
    {
#if defined(USE_GRAPHICS_BACKEND_SDL)
        static SDLGraphicsFactory instance;
#endif // USE_GRAPHICS_BACKEND_SDL

        return instance;
    }
}