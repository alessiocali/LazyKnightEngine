#include <lazye/backends/sdl/opengl/sdlglrenderingcontext.h>

#include <glad/glad.h>

#include <lazye/graphics/mesh.h>
#include <lazye/graphics/model.h>
#include <lazye/graphics/sprite.h>

#include <lazye/backends/opengl/openglmesh.h>

namespace lazye
{
    void SDLGLRenderingContext::Clear()
    {
        glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], 1.f);
        glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);
    }
}