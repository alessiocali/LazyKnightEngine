#include <lke/backends/sdl/opengl/sdlglrenderingcontext.h>

#include <glad/glad.h>

#include <lke/graphics/mesh.h>
#include <lke/graphics/model.h>
#include <lke/graphics/sprite.h>

#include <lke/backends/opengl/openglmesh.h>

namespace lke
{
    void SDLGLRenderingContext::Clear()
    {
        glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], 1.f);
        glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);
    }
}