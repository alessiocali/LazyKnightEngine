#pragma once
#include <lazye/lazye.h>

#include <lazye/backends/sdl/sdlwindowbase.h>
#include <lazye/backends/sdl/sdlrenderingcontext.h>

namespace lazye
{
    /**
     * A Window implementation that wraps and manages an SDL_Window C structure
     */
    class SDLWindow : public SDLWindowBase
    {
    public:
        SDLWindow();

        virtual void Display() override;

        RenderingContext& GetRenderingContext() override;

    private:
        SDLRenderingContext m_Context;
    };
}