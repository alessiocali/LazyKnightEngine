#include <lke/backends/sdl/opengl/sdlglwindow.h>

namespace lke
{
    static constexpr std::uint16_t GL_MAJOR_VERSION = 3;
    static constexpr std::uint16_t GL_MINOR_VERSION = 3;

    SDLGLWindow::SDLGLWindow()
        : SDLWindowBase()
    {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, GL_MAJOR_VERSION);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, GL_MINOR_VERSION);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        int effectiveMajorVersion, effectiveMinorVersion;
        SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &effectiveMajorVersion);
        SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &effectiveMinorVersion);

        Assert(effectiveMajorVersion == GL_MAJOR_VERSION);
        Assert(effectiveMinorVersion == GL_MINOR_VERSION);

        InitWindow(SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

        m_GLContext.Init(m_SDLWindow.get());
    }

    void SDLGLWindow::Resize(Size size)
    {
        SDLWindowBase::Resize(size);
        m_GLContext.Resize(size.width, size.height);
    }

    void SDLGLWindow::Display()
    {
        SDLWindowBase::Display();
        SDL_GL_SwapWindow(m_SDLWindow.get());
    }

    RenderingContext& SDLGLWindow::GetRenderingContext()
    {
        return m_RenderingContext;
    }
}