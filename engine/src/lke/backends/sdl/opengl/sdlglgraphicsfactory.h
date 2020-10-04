#pragma once

#include <lke/graphics/graphicsfactory.h>

namespace lke
{
    class SDLGLGraphicsFactory : public GraphicsFactory
    {
    public:
        const Matrix44f& GetCameraCorrectionMatrix() const override;

        std::unique_ptr<Window> CreateWindow() const override;
        std::unique_ptr<Mesh> CreateMesh(std::size_t vertexCount) const override;
        std::unique_ptr<Texture> CreateTexture() const override;

    private:
        friend GraphicsFactory& GraphicsFactory::GetInstance();
        SDLGLGraphicsFactory() = default;
    };
}