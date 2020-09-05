#include <lazye/backends/sdl/opengl/sdlglrenderingcontext.h>

#include <glad/glad.h>

#include <lazye/backends/sdl/opengl/sdlglsprite.h>

namespace lazye
{
    void SDLGLRenderingContext::Clear()
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void SDLGLRenderingContext::Render(const Sprite& sprite)
    {
        static_cast<const SDLGLSprite&>(sprite).Draw();
    }
}