#include <lazye/backends/sdl/opengl/sdlglcontext.h>

#include <lazye/backends/sdl/sdlwindow.h>
#include <lazye/backends/opengl/openglapi.h>

namespace lazye
{
    SDLGLContext::~SDLGLContext()
    {
        if (m_GLContext != nullptr)
        {
            SDL_GL_DeleteContext(m_GLContext);
        }
    }

    void SDLGLContext::Init(SDL_Window* sdlWindow)
    {
        m_GLContext = SDL_GL_CreateContext(sdlWindow);
        Assert(m_GLContext != nullptr);

        OpenGLAPI::GetInstance().Init(static_cast<GLADloadproc>(SDL_GL_GetProcAddress));

        Assert(SDL_GL_SetSwapInterval(1) >= 0);

        int width, height;
        SDL_GetWindowSize(sdlWindow, &width, &height);
        Resize(width, height);
    }

    void SDLGLContext::Resize(int width, int height)
    {
        glViewport(0, 0, width, height);
    }
}