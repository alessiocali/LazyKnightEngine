#include <lazye/graphics/model.h>

#include <lazye/graphics/mesh.h>
#include <lazye/graphics/texture.h>

namespace lazye
{
    Model::Model() = default;
    Model::~Model() = default;

    void Model::AddMesh(std::unique_ptr<Mesh> mesh, const std::vector<std::string>& associatedTextureNames /* = { }*/)
    {
        auto& insertedMesh = m_Meshes.emplace_back(std::move(mesh));

        std::vector<std::weak_ptr<Texture>> texturesToAssociate;
        texturesToAssociate.reserve(associatedTextureNames.size());

        for (const auto& textureName : associatedTextureNames)
        {
            if (HasTexture(textureName))
            {
                texturesToAssociate.emplace_back(m_Textures[textureName]);
            }
        }

        insertedMesh->AssociateTextures(texturesToAssociate);
    }

    void Model::AddTexture(const std::string& name, std::unique_ptr<Texture> texture)
    {
        Assert(!HasTexture(name), "Trying to insert two textures with the same name in this model");
        m_Textures[name] = std::move(texture);
    }

    bool Model::HasTexture(const std::string& name) const
    {
        return m_Textures.count(name) > 0;
    }

    void Model::Draw(const Matrix44f& transform, const Matrix44f& view, const Matrix44f& projection) const
    {
        for (auto& mesh : m_Meshes)
        {
            if (mesh == nullptr)
            {
                Assert(false, "Null mesh in model");
                continue;
            }

            mesh->Draw(transform, view, projection);
        }
    }
}