#include <lazye/assets/textureloader.h>

#include <lazye/backends/backenddefines.h>

#ifdef USE_TEXTURE_LOADER_SDL
    #ifdef USE_GRAPHICS_API_OPENGL
        #include <lazye/backends/sdl/opengl/sdlgltextureloader.h>
    #endif
#endif

namespace lazye
{
    TextureLoader& TextureLoader::GetInstance()
    {
#ifdef USE_TEXTURE_LOADER_SDL
    #ifdef USE_GRAPHICS_API_OPENGL
        static SDLGLTextureLoader s_Instance;
    #else
        static_assert(false, "No valid TextureLoader for SDL Image")
    #endif
#else
        static_assert(false, "No asset loader was defined during project creation");
#endif

        return s_Instance;
    }
}