#include <lazye/backends/sdl/sdlwindowbase.h>

#include <lazye/backends/sdl/sdlhelper.h>

#include <lazye/backends/sdl/sdlheader.h>

namespace lazye
{
    void SDLWindowBase::InitWindow(Uint32 windowFlags)
    {
        m_SDLWindow = SDLHelper::SDL_WindowPtr(
            SDL_CreateWindow(
                DEFAULT_WINDOW_TITLE,
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                DEFAULT_WINDOW_SIZE.width,
                DEFAULT_WINDOW_SIZE.height,
                windowFlags
            )
        );

        SetMode(DEFAULT_WINDOW_MODE);
    }

    bool SDLWindowBase::IsOpen() const
    {
        return (SDL_GetWindowFlags(m_SDLWindow.get()) & SDL_WINDOW_SHOWN) != 0;
    }

    void SDLWindowBase::SetTitle(const std::string& title)
    {
        SDL_SetWindowTitle(m_SDLWindow.get(), title.c_str());
    }

    void SDLWindowBase::SetPosition(Position position)
    {
        SDL_SetWindowPosition(m_SDLWindow.get(), position.x, position.y);
    }

    void SDLWindowBase::Resize(Size size)
    {
        SDL_SetWindowSize(m_SDLWindow.get(), size.width, size.height);
    }

    void SDLWindowBase::SetMode(Mode mode)
    {
        Uint32 fullScreenFlags = GetFullScreenFlagsFromMode(mode);
        SDL_SetWindowFullscreen(m_SDLWindow.get(), fullScreenFlags);
    }

    void SDLWindowBase::Display()
    {
        ProcessEvents();
    }

    void SDLWindowBase::Close()
    {
        SDL_HideWindow(m_SDLWindow.get());
    }

    Uint32 SDLWindowBase::GetFullScreenFlagsFromMode(Mode mode)
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

    void SDLWindowBase::ProcessEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ProcessEvent(event);
        }
    }

    void SDLWindowBase::ProcessEvent(const SDL_Event& event)
    {
        switch (event.type)
        {
        case SDL_QUIT:
            Close();
            break;
        }
    }
}