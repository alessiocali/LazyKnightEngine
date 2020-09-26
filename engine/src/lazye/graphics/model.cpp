#include <lazye/graphics/model.h>

#include <lazye/graphics/mesh.h>

namespace lazye
{
    Model::Model() = default;
    Model::~Model() = default;

    void Model::AddMesh(std::unique_ptr<Mesh> mesh)
    {
        m_Meshes.push_back(std::move(mesh));
    }
}