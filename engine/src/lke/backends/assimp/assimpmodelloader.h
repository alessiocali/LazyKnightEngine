#pragma once
#include <lke/assets/modelloader.h>

#include <lke/math/matrix.h>

struct aiScene;
struct aiMesh;
struct aiMaterial;

namespace lke
{
    class AssimpModelLoader final : public ModelLoader
    {
    public:
        std::unique_ptr<Model> LoadModel(const std::string& modelPath) const override;

    private:
        friend ModelLoader& ModelLoader::GetInstance();
        
        static const Matrix44f& GetAssimpCorrectionMatrix();
        static std::tuple<std::string, bool> GetAlbedoTexturePathFromMaterial(const aiMaterial& mat);

        static void ImportAllTextures(const aiScene& scene, Model& model, const std::string& rootDir);
        static void ImportAllMeshes(const aiScene& scene, Model& model);
        static void ImportMesh(const aiMesh& mesh, const aiMaterial& mat, Model& model);

        AssimpModelLoader() = default;
    };
}