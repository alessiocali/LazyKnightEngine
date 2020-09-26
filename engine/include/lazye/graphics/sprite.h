#pragma once
#include <lazye/lazye.h>

#include <lazye/graphics/camera.h>
#include <lazye/math/transform.h>

namespace lazye
{
    class Camera;
    class Mesh;
    class Texture;

    class lazyedll Sprite final
    {
    public:
        Sprite(const std::string& spritePath);
        ~Sprite();

        void SetTransform(const Transform& transform) { m_Transform = transform; };

        void Draw(const Matrix44f& view, const Matrix44f& projection);

    private:
        Transform m_Transform;
        std::shared_ptr<Texture> m_Texture;

        static Mesh& GetBaseMesh();
    };
}