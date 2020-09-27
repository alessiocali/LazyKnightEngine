#include <lazye/backends/sdl/sdlrenderingcontext.h>

#include <lazye/math/matrix.h>
#include <lazye/graphics/sprite.h>

#include <lazye/backends/sdl/sdlheader.h>

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

    void SDLRenderingContext::Present()
    {
        SDL_RenderPresent(m_SDLRenderer.get());
    }

}