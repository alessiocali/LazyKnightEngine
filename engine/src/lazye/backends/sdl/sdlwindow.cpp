#include <lazye/backends/sdl/sdlwindow.h>

#include <lazye/backends/sdl/sdlhelper.h>

#include <lazye/backends/sdl/sdlheader.h>

namespace lazye
{
    SDLWindow::SDLWindow()
    {
        m_SDLWindow = SDLHelper::SDL_WindowPtr(
            SDL_CreateWindow(
                DEFAULT_WINDOW_TITLE, 
                0, 
                0, 
                DEFAULT_WINDOW_SIZE.width, 
                DEFAULT_WINDOW_SIZE.height, 
                SDL_WINDOW_SHOWN
            )
        );

        SetMode(DEFAULT_WINDOW_MODE);

        m_Context.Init(m_SDLWindow.get());
    }

    bool SDLWindow::IsOpen() const
    {
        return (SDL_GetWindowFlags(m_SDLWindow.get()) & SDL_WINDOW_SHOWN) != 0;
    }

    void SDLWindow::SetTitle(const std::string& title)
    {
        SDL_SetWindowTitle(m_SDLWindow.get(), title.c_str());
    }

    void SDLWindow::SetPosition(Position position)
    {
        SDL_SetWindowPosition(m_SDLWindow.get(), position.x, position.y);
    }

    void SDLWindow::Resize(Size size)
    {
        SDL_SetWindowSize(m_SDLWindow.get(), size.width, size.height);
    }

    void SDLWindow::SetMode(Mode mode)
    {
        Uint32 fullScreenFlags = GetFullScreenFlagsFromMode(mode);
        SDL_SetWindowFullscreen(m_SDLWindow.get(), fullScreenFlags);
    }

    void SDLWindow::Display()
    {
        ProcessEvents();
        m_Context.Present();
    }

    void SDLWindow::Close()
    {
        SDL_HideWindow(m_SDLWindow.get());
    }

    RenderingContext& SDLWindow::GetRenderingContext()
    {
        return m_Context;
    }

    Uint32 SDLWindow::GetFullScreenFlagsFromMode(Mode mode)
    {
        switch (mode)
        {
        case Mode::Fullscreen:
            return SDL_WINDOW_FULLSCREEN;
        case Mode::Windowed:
            return 0;
        default:
            return 0;
        }
    }

    void SDLWindow::ProcessEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ProcessEvent(event);
        }
    }

    void SDLWindow::ProcessEvent(const SDL_Event& event)
    {
        switch (event.type)
        {
        case SDL_QUIT:
            Close();
            break;
        }
    }
}