#pragma once

#include <lazye/graphics/renderingcontext.h>

namespace lazye
{
    class SDLGLSprite;

    class SDLGLRenderingContext final : public RenderingContext
    {
    public:
        void Clear() override;
        void Render(const Sprite& sprite) override;
    };
}