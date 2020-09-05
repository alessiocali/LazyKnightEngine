#pragma once
#include <lazye/lazye.h>

#include <lazye/graphics/window.h>

#include <lazye/backends/sdl/sdlhelper.h>
#include <lazye/backends/sdl/sdlsystem.h>

#include <SDL_stdinc.h>

namespace lazye
{
    /**
     * A Window implementation that wraps and manages an SDL_Window C structure
     */
    class SDLWindowBase : public Window, private ISDLSubSystemUser<SDL_INIT_EVERYTHING>
    {
    public:
        bool IsOpen() const override;

        void SetTitle(const std::string& title) override;
        void SetPosition(Position position) override;
        void Resize(Size size) override;
        void SetMode(Mode mode) override;
        void Display() override;
        void Close() override;

    protected:
        SDLHelper::SDL_WindowPtr m_SDLWindow;

        void InitWindow(Uint32 windowFlags);

    private:
        Uint32 GetFullScreenFlagsFromMode(Mode mode);
        void ProcessEvents();
        void ProcessEvent(const SDL_Event& event);
    };
}