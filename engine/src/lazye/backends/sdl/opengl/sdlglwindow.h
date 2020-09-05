#pragma once

#include <lazye/backends/sdl/sdlwindowbase.h>

#include <lazye/backends/sdl/opengl/sdlglrenderingcontext.h>
#include <lazye/backends/sdl/opengl/sdlglcontext.h>

namespace lazye
{
    class SDLGLWindow final : public SDLWindowBase
    {
    public:
        SDLGLWindow();

        virtual void Resize(Size size) override;
        virtual void Display() override;

        virtual RenderingContext& GetRenderingContext() override;

    private:
        SDLGLRenderingContext m_RenderingContext;
        SDLGLContext m_GLContext;
    };
}