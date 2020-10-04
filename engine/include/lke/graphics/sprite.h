#pragma once
#include <lke/lke.h>

#include <memory>

#include <lke/graphics/camera.h>
#include <lke/math/transform.h>

namespace lke
{
    class Camera;
    class Mesh;
    class Texture;

    class lkedll Sprite final
    {
    public:
        Sprite(const std::string& spritePath);
        ~Sprite();

        void Draw(const Matrix44f& transform, const Matrix44f& view, const Matrix44f& projection);

    private:
        std::shared_ptr<Texture> m_Texture;

        static Mesh& GetBaseMesh();
    };
}