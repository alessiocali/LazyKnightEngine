#pragma once
#include <lazye/lazye.h>

#include <lazye/math/transform.h>

#include <vector>
#include <memory>
#include <unordered_map>

namespace lazye
{
    class Mesh;
    class Texture;

    class lazyedll Model final
    {
    public:
        Model();
        ~Model();

        void AddMesh(std::unique_ptr<Mesh> mesh, const std::vector<std::string>& associatedTextureNames = {});
        void AddTexture(const std::string& name, std::unique_ptr<Texture> texture);

        bool HasTexture(const std::string& name) const;

        void Draw(const Matrix44f& transform, const Matrix44f& view, const Matrix44f& projection) const;

    private:
        Transform m_Transform;

        std::vector<std::unique_ptr<Mesh>> m_Meshes;
        std::unordered_map<std::string, std::shared_ptr<Texture>> m_Textures;
    };
}