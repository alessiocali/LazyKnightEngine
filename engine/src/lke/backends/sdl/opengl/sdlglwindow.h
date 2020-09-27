#pragma once

#include <lke/backends/sdl/sdlwindowbase.h>

#include <lke/backends/sdl/opengl/sdlglrenderingcontext.h>
#include <lke/backends/sdl/opengl/sdlglcontext.h>

namespace lke
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