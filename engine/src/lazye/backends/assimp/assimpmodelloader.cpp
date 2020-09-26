#include <lazye/backends/assimp/assimpmodelloader.h>

#include <lazye/math/math.h>
#include <lazye/math/quaternions.h>

#include <lazye/graphics/graphicsfactory.h>
#include <lazye/graphics/mesh.h>
#include <lazye/graphics/model.h>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

namespace lazye
{
    std::unique_ptr<Model> AssimpModelLoader::LoadModel(const std::string& modelPath) const
    {
        Assimp::Importer importer;

        constexpr unsigned int ASSIMP_IMPORT_FLAGS =
            aiProcess_JoinIdenticalVertices
            | aiProcess_Triangulate
            | aiProcess_SplitLargeMeshes
            | aiProcess_PreTransformVertices
            | aiProcess_ImproveCacheLocality
            | aiProcess_RemoveRedundantMaterials
            | aiProcess_SortByPType
            | aiProcess_GenUVCoords
            | aiProcess_TransformUVCoords
            | aiProcess_OptimizeMeshes;

        const aiScene* importedScene = importer.ReadFile(modelPath, ASSIMP_IMPORT_FLAGS);
        if (importedScene == nullptr)
        {
            Assert(false, "Failed to load model");
            return nullptr;
        }

        std::unique_ptr<Model> model = std::make_unique<Model>();
        ImportAllMeshes(*importedScene, *model);
        return model;
    }

    /*static*/ const Matrix44f& AssimpModelLoader::GetAssimpCorrectionMatrix()
    {
        static bool s_Init = false;
        static Matrix44f s_CameraCorrectionMatrix;

        if (!s_Init)
        {
            SetToRotationMatrix(s_CameraCorrectionMatrix, Quaternion::FromAngleAxis({ DegToRad(90.f), Vector3f::GetAxisI() }));
            s_Init = true;
        }

        return s_CameraCorrectionMatrix;
    }

    /*static*/ void AssimpModelLoader::ImportAllMeshes(const aiScene& scene, Model& model)
    {
        for (std::size_t i = 0; i < scene.mNumMeshes; i++)
        {
            ImportMesh(*(scene.mMeshes[i]), model);
        }
    }

    /*static*/ void AssimpModelLoader::ImportMesh(const aiMesh& mesh, Model& model)
    {
        std::unique_ptr<Mesh> importedMesh = GraphicsFactory::GetInstance().CreateMesh(mesh.mNumVertices);
        std::vector<Vector3f> vertices;
        std::vector<unsigned int> indices;

        vertices.reserve(mesh.mNumVertices);
        indices.reserve(mesh.mNumFaces * 3);

        for (std::size_t i = 0; i < mesh.mNumVertices; i++)
        {
            const aiVector3D& vx = mesh.mVertices[i];
            // Assimp uses the OpenGL reference system, so we're better correcting that.
            Vector4f correctVx = GetAssimpCorrectionMatrix() * Vector4f { vx[0], vx[1], vx[2], 1.f };
            vertices.emplace_back(Vector3f { correctVx[0], correctVx[1], correctVx[2] });
        }

        for (std::size_t i = 0; i < mesh.mNumFaces; i++)
        {
            const aiFace& face = mesh.mFaces[i];
            if (face.mNumIndices != 3)
            {
                // Ignore non-triangular faces (model should have been already triangulated)
                continue;
            }

            auto emplaceIndices = [&indices, &face](auto... faceIdx) { (..., indices.emplace_back(face.mIndices[faceIdx])); };
            emplaceIndices(0, 1, 2);
        }

        importedMesh->AddVertices(vertices);
        importedMesh->SetIndices(indices);

        model.AddMesh(std::move(importedMesh));
    }
}