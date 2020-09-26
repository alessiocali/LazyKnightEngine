#pragma once

#include <vector>
#include <lazye/math/matrix.h>
#include <lazye/math/vectors.h>

namespace lazye
{
    class Texture;

    class lazyedll Mesh
    {
    public:
        virtual ~Mesh() = default;

        virtual void AddVertices(const std::vector<Vector3f>& vertices) = 0;
        virtual void AddTextureMapping(const std::vector<Vector2f>& mapping) = 0;
        virtual void SetIndices(const std::vector<unsigned int>& indices) = 0;
        virtual void AssociateTextures(const std::vector<std::weak_ptr<Texture>>& textures) = 0;
        virtual void Draw(const Matrix44f& transform, const Matrix44f& view, const Matrix44f& projection) = 0;
    };
}