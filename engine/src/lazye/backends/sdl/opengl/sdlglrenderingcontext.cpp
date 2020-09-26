#include <lazye/backends/sdl/opengl/sdlglrenderingcontext.h>

#include <glad/glad.h>

#include <lazye/backends/sdl/opengl/sdlglsprite.h>
#include <lazye/graphics/mesh.h>
#include <lazye/graphics/model.h>

#include <lazye/backends/opengl/openglmesh.h>

namespace lazye
{
    void SDLGLRenderingContext::Clear()
    {
        glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], 1.f);
        glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);
    }

    void SDLGLRenderingContext::Render(Sprite& sprite)
    {
        if (m_Camera) { m_Camera->UpdateViewMatrix(); }

        const Matrix44f& view = m_Camera ? m_Camera->GetViewMatrix() : Matrix44f::GetIdentity();
        const Matrix44f& projection = m_Camera ? m_Camera->GetProjectionMatrix() : Matrix44f::GetIdentity();
        static_cast<const SDLGLSprite&>(sprite).Draw(view, projection);
    }

    void SDLGLRenderingContext::Render(Model& model)
    {
        if (m_Camera) { m_Camera->UpdateViewMatrix(); }

        auto [view, projection] = m_Camera ? m_Camera->GetViewProjectionMatrices() : std::tuple{ Matrix44f::GetIdentity(), Matrix44f::GetIdentity() };

        for (auto& mesh : model.GetMeshes())
        {
            if (mesh == nullptr)
            {
                Assert(false, "Null mesh in model");
                continue;
            }

            static_cast<OpenGLMesh&>(*mesh).Draw(model.GetTransformMatrix(), view, projection);
        }
    }

}