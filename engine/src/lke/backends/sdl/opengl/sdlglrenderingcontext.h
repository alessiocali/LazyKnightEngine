#pragma once

#include <lke/graphics/renderingcontext.h>

#include <lke/math/vectors.h>
#include <lke/graphics/camera.h>

namespace lke
{
    class SDLGLSprite;

    class SDLGLRenderingContext final : public RenderingContext
    {
    public:
        void SetClearColor(const Vector3f& color) override { m_ClearColor = color; };
        void Clear() override;

    private:
        Vector3f m_ClearColor;
    };
}