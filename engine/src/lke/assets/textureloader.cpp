#include <lke/assets/textureloader.h>

#include <lke/backends/backenddefines.h>

#ifdef USE_TEXTURE_LOADER_SDL
    #include <lke/backends/sdl/assets/sdltextureloader.h>
#endif

namespace lke
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