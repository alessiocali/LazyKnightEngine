#include <lazye/backends/sdl/sdlrenderingcontext.h>

#include <lazye/backends/sdl/sdlheader.h>
#include <lazye/backends/sdl/sdlsprite.h>

static constexpr Uint32 DEFAULT_RENDERER_FLAGS = SDL_RENDERER_ACCELERATED;
static constexpr int DEFAULT_RENDERING_DRIVERS = -1;

namespace lazye
{
    void SDLRenderingContext::Init(SDL_Window* sdlWindow)
    {
        m_SDLRenderer = SDLHelper::SDL_RendererPtr(SDL_CreateRenderer(sdlWindow, DEFAULT_RENDERING_DRIVERS, DEFAULT_RENDERER_FLAGS));
    }

    void SDLRenderingContext::Clear()
    {
        SDL_RenderClear(m_SDLRenderer.get());
    }

    void SDLRenderingContext::Render(const Sprite& sprite)
    {
        const SDLSprite& sdlSprite = static_cast<const SDLSprite&>(sprite);
        if (!sdlSprite.IsLoaded())
        {
            // This abomination will go away eventually, the Sprite Class is doomed already (TODO: 3D based implementation)
            const_cast<SDLSprite&>(sdlSprite).Load(m_SDLRenderer.get());
        }

        SDL_Texture* texture = sdlSprite.GetTexture();

        int width, height;
        SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

        const Vector2f& pos = sdlSprite.GetPosition();
        int x = static_cast<int>(pos[0]);
        int y = static_cast<int>(pos[1]);
        SDL_Rect sdlRect = { x, y, width, height };
        SDL_RenderCopy(m_SDLRenderer.get(), texture, nullptr, &sdlRect);
    }

    void SDLRenderingContext::Present()
    {
        SDL_RenderPresent(m_SDLRenderer.get());
    }

}