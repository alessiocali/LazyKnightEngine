#include <lazye/assets/textureloader.h>

#include <lazye/backends/backenddefines.h>

#ifdef USE_TEXTURE_LOADER_SDL
    #include <lazye/backends/sdl/assets/sdltextureloader.h>
#endif

namespace lazye
{
    TextureLoader& TextureLoader::GetInstance()
    {
#ifdef USE_TEXTURE_LOADER_SDL
        static SDLTextureLoader s_Instance;
#else
        static_assert(false, "No asset loader was defined during project creation");
#endif

        return s_Instance;
    }
}