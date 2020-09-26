#pragma once
#include <lazye/lazye.h>

#include <lazye/graphics/graphicsfactory.h>

namespace lazye
{
    class SDLGraphicsFactory : public GraphicsFactory
    {
    public:
        const Matrix44f& GetCameraCorrectionMatrix() const override { return Matrix44f::GetIdentity(); }

        std::unique_ptr<Window> CreateWindow() const override;
        std::unique_ptr<Mesh> CreateMesh(std::size_t vertexCount) const override;
        std::unique_ptr<Texture> CreateTexture() const override;

    private:
        friend GraphicsFactory& GraphicsFactory::GetInstance();
        SDLGraphicsFactory() = default;
    };
}