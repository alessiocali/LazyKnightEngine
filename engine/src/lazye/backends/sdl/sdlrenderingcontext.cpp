#include <lazye/backends/sdl/sdlrenderingcontext.h>

#include <lazye/backends/sdl/sdlheader.h>
#include <lazye/backends/sdl/sdlsprite.h>

#include <algorithm>

static constexpr Uint32 DEFAULT_RENDERER_FLAGS = SDL_RENDERER_ACCELERATED;
static constexpr int DEFAULT_RENDERING_DRIVERS = -1;

namespace lazye
{
    void SDLRenderingContext::Init(SDL_Window* sdlWindow)
    {
        m_SDLRenderer = SDLHelper::SDL_RendererPtr(SDL_CreateRenderer(sdlWindow, DEFAULT_RENDERING_DRIVERS, DEFAULT_RENDERER_FLAGS));
    }

    void SDLRenderingContext::SetClearColor(const Vector3f& color)
    {
        auto toUint = [](const float val)
        {
            const float toRGB = std::clamp(val * 255.0f, 0.f, 255.0f);
            return static_cast<std::uint8_t>(toRGB);
        };

        SDL_SetRenderDrawColor(m_SDLRenderer.get(), toUint(color[0]), toUint(color[1]), toUint(color[2]), 255);
    }

    void SDLRenderingContext::Clear()
    {
        SDL_RenderClear(m_SDLRenderer.get());
    }

    void SDLRenderingContext::Render(Sprite& sprite)
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