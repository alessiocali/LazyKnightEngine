#pragma once
#include <lazye/lazye.h>

#include <lazye/math/transform.h>

#include <vector>
#include <memory>

namespace lazye
{
    class Mesh;

    class lazyedll Model final
    {
    public:
        Model();
        ~Model();

        inline void SetTransform(const Transform& transform) { m_Transform = transform; }
        inline const Matrix44f& GetTransformMatrix() { return m_Transform.GetMatrix(); }
        inline const std::vector<std::unique_ptr<Mesh>>& GetMeshes() const { return m_Meshes; }

        void AddMesh(std::unique_ptr<Mesh> mesh);

    private:
        Transform m_Transform;
        std::vector<std::unique_ptr<Mesh>> m_Meshes;
    };
}