#pragma once

#include <lazye/backends/sdl/sdlheader.h>

namespace lazye::SDLHelper
{
    template<typename SDLType>
    using SDLDeleterFunction = void(*)(SDLType*);

    template<typename SDLType, SDLDeleterFunction<SDLType> DeleterFunction>
    struct SDL_Deleter
    {
        void operator()(SDLType* sdlObject)
        {
            DeleterFunction(sdlObject);
        }
    };

    /**
     *  RAII around SDL_Lock/UnlockSurface. Use with caution, the Surface lifetime must outspan this object.
     */
    struct SDL_SurfaceLocker
    {
        SDL_SurfaceLocker(SDL_Surface* surface) 
            : m_Surface(surface)
        {
            if (SDL_MUSTLOCK(m_Surface))
            {
                SDL_LockSurface(m_Surface);
            }
        }

        ~SDL_SurfaceLocker() 
        { 
            if (SDL_MUSTLOCK(m_Surface))
            {
                SDL_UnlockSurface(m_Surface);
            }
        }

    private:
        SDL_Surface* m_Surface;
    };

    using SDL_WindowDeleter = SDL_Deleter<SDL_Window, SDL_DestroyWindow>;
    using SDL_RendererDeleter = SDL_Deleter<SDL_Renderer, SDL_DestroyRenderer>;
    using SDL_SurfaceDeleter = SDL_Deleter<SDL_Surface, SDL_FreeSurface>;
    using SDL_TextureDeleter = SDL_Deleter<SDL_Texture, SDL_DestroyTexture>;

    using SDL_WindowPtr = std::unique_ptr<SDL_Window, SDL_WindowDeleter>;
    using SDL_RendererPtr = std::unique_ptr<SDL_Renderer, SDL_RendererDeleter>;
    using SDL_SurfacePtr = std::unique_ptr<SDL_Surface, SDL_SurfaceDeleter>;
    using SDL_TexturePtr = std::unique_ptr<SDL_Texture, SDL_TextureDeleter>;
}