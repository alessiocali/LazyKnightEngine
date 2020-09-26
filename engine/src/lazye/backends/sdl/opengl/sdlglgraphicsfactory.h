#pragma once

#include <lazye/graphics/graphicsfactory.h>

namespace lazye
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