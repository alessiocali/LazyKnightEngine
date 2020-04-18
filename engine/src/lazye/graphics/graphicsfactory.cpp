#include <lazye/graphics/graphicsfactory.h>

#include <lazye/backends/backenddefines.h>

#ifdef USE_GRAPHICS_BACKEND_SFML
#include <lazye/backends/sfml/sfmlgraphicsfactory.h>
#endif // USE_GRAPHICS_BACKEND_SFML

namespace lazye
{
    GraphicsFactory& GraphicsFactory::GetInstance()
    {
#ifdef USE_GRAPHICS_BACKEND_SFML
        static SFMLGraphicsFactory instance;
#endif // USE_GRAPHICS_BACKEND_SFML

        return instance;
    }
}