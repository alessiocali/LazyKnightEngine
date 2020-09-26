#pragma once

#include <vector>
#include <lazye/math/vectors.h>

namespace lazye
{
    class lazyedll Mesh
    {
    public:
        virtual ~Mesh() = default;

        virtual void AddVertices(const std::vector<Vector3f>& vertices) = 0;
        virtual void SetIndices(const std::vector<unsigned int> indices) = 0;
    };
}