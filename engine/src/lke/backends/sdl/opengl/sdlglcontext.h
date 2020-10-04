#pragma once
#include <lke/lke.h>

#include <SDL2/SDL_video.h>

namespace lke
{
    class SDLGLContext final
    {
    public:
        ~SDLGLContext();

        void Init(SDL_Window* sdlWindow);
        void Resize(int width, int height);

    private:
        SDL_GLContext m_GLContext = nullptr;
    };
}