#include <lazye/backends/sdl/sdlwindow.h>

#include <lazye/backends/sdl/sdlhelper.h>

#include <lazye/backends/sdl/sdlheader.h>

namespace lazye
{
    SDLWindow::SDLWindow()
        : SDLWindowBase()
    {
        InitWindow(SDL_WINDOW_SHOWN);
        m_Context.Init(m_SDLWindow.get());
    }

    void SDLWindow::Display()
    {
        SDLWindowBase::Display();
        m_Context.Present();
    }

    RenderingContext& SDLWindow::GetRenderingContext()
    {
        return m_Context;
    }
}