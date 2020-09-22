#include <lazye/graphics/renderingcontext.h>

#include <lazye/graphics/camera.h>

namespace lazye
{
    RenderingContext::RenderingContext() = default;
    RenderingContext::~RenderingContext() = default;

    void RenderingContext::SetCamera(std::unique_ptr<Camera> camera)
    {
        m_Camera = std::move(camera);
    }
}