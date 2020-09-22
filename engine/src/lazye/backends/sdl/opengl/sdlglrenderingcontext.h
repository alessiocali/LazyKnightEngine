#pragma once

#include <lazye/graphics/renderingcontext.h>

#include <lazye/math/vectors.h>
#include <lazye/graphics/camera.h>

namespace lazye
{
    class SDLGLSprite;

    class SDLGLRenderingContext final : public RenderingContext
    {
    public:
        void SetClearColor(const Vector3f& color) override { m_ClearColor = color; };
        void Clear() override;
        void Render(const Sprite& sprite) override;

    private:
        Vector3f m_ClearColor;
    };
}