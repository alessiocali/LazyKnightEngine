#pragma once
#include <lazye/assets/assetloader.h>

#include <lazye/math/matrix.h>

struct aiScene;
struct aiMesh;

namespace lazye
{
    class AssimpAssetLoader final : public AssetLoader
    {
    public:
        std::unique_ptr<Model> LoadModel(const std::string& modelPath) override;

    private:
        friend AssetLoader& AssetLoader::GetInstance();
        
        static const Matrix44f& GetAssimpCorrectionMatrix();
        static void ImportAllMeshes(const aiScene& scene, Model& model);
        static void ImportMesh(const aiMesh& mesh, Model& model);

        AssimpAssetLoader() = default;
    };
}