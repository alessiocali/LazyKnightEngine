#pragma once
#include <lke/lke.h>

#include <lke/math/matrix.h>

#include <memory>
#include <string>

namespace lke
{
    class Window;
    class Sprite;
    class Mesh;
    class Texture;

    class lkedll GraphicsFactory
    {
    public:
        static GraphicsFactory& GetInstance();

        /**
         *  Yields a Matrix which corrects the default API reference system to lke's
         *  reference system (that is, Z-up Y-forward).
         *
         *  For example, in the case of OpenGL (Y-up Z-backward) that would translate into
         *  a 90-degree positive rotation along the X-axis.
         *
         *  @return The corrective transform for the current API
         */
        virtual const Matrix44f& GetCameraCorrectionMatrix() const = 0;

        virtual std::unique_ptr<Window> CreateWindow() const = 0;
        virtual std::unique_ptr<Texture> CreateTexture() const = 0;
        virtual std::unique_ptr<Mesh> CreateMesh(std::size_t vertexCount) const = 0;

    protected:
        GraphicsFactory() = default;
    };
}