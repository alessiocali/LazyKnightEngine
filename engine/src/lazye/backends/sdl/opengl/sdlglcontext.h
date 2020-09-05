#pragma once
#include <lazye/lazye.h>

#include <SDL2/SDL_video.h>

namespace lazye
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