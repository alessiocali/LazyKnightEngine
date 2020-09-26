#pragma once
#include <lazye/lazye.h>

#include <lazye/math/matrix.h>

#include <memory>
#include <string>

namespace lazye
{
    class Window;
    class Sprite;
    class Mesh;

    class lazyedll GraphicsFactory
    {
    public:
        static GraphicsFactory& GetInstance();

        /**
         *  Yields a Matrix which corrects the default API reference system to lazye's
         *  reference system (that is, Z-up Y-forward).
         *
         *  For example, in the case of OpenGL (Y-up Z-backward) that would translate into
         *  a 90-degree positive rotation along the X-axis.
         *
         *  @return The corrective transform for the current API
         */
        virtual const Matrix44f& GetCameraCorrectionMatrix() const = 0;

        virtual std::unique_ptr<Window> CreateWindow() const = 0;
        virtual std::unique_ptr<Sprite> CreateSprite(const std::string& spritePath) const = 0;
        virtual std::unique_ptr<Mesh> CreateMesh(std::size_t vertexCount) const = 0;

    protected:
        GraphicsFactory() = default;
    };
}