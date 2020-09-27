#include <lke/graphics/renderingcontext.h>

#include <lke/graphics/camera.h>

namespace lke
{
    RenderingContext::RenderingContext() = default;
    RenderingContext::~RenderingContext() = default;

    void RenderingContext::SetCamera(std::unique_ptr<Camera> camera)
    {
        m_Camera = std::move(camera);
    }

    void RenderingContext::UpdateCamera()
    {
        if (m_Camera != nullptr)
        {
            m_Camera->UpdateViewMatrix();
        }
    }

    std::tuple<const Matrix44f&, const Matrix44f&> RenderingContext::GetViewProjectionMatrices() const
    {
        return m_Camera ? m_Camera->GetViewProjectionMatrices() : std::tuple { Matrix44f::GetIdentity(), Matrix44f::GetIdentity() };
    }
}