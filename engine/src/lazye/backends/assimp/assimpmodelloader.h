#pragma once
#include <lazye/assets/modelloader.h>

#include <lazye/math/matrix.h>

struct aiScene;
struct aiMesh;

namespace lazye
{
    class AssimpModelLoader final : public ModelLoader
    {
    public:
        std::unique_ptr<Model> LoadModel(const std::string& modelPath) const override;

    private:
        friend ModelLoader& ModelLoader::GetInstance();
        
        static const Matrix44f& GetAssimpCorrectionMatrix();
        static void ImportAllMeshes(const aiScene& scene, Model& model);
        static void ImportMesh(const aiMesh& mesh, Model& model);

        AssimpModelLoader() = default;
    };
}