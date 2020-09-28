#pragma once

#include <memory>
#include <vector>

#include <lke/math/matrix.h>
#include <lke/math/vectors.h>

namespace lke
{
    class Texture;

    class lkedll Mesh
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