#include <lazye/backends/assimp/assimpmodelloader.h>

#include <filesystem>

#include <lazye/assets/textureloader.h>

#include <lazye/math/math.h>
#include <lazye/math/quaternions.h>

#include <lazye/graphics/graphicsfactory.h>
#include <lazye/graphics/mesh.h>
#include <lazye/graphics/model.h>
#include <lazye/graphics/texture.h>

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
        ImportAllTextures(*importedScene, *model, std::filesystem::path(modelPath).remove_filename().string());
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

    /*static*/ void AssimpModelLoader::ImportAllTextures(const aiScene& scene, Model& model, const std::string& rootDir)
    {
        for (std::size_t i = 0; i < scene.mNumMaterials; i++)
        {
            const aiMaterial& material = *(scene.mMaterials[i]);
            // Support only diffuse (Albedo) textures for now

            const auto [texturePath, success] = GetAlbedoTexturePathFromMaterial(material);
            if (!success || model.HasTexture(texturePath))
            {
                continue;
            }

            std::unique_ptr<Texture> loadedTexture = TextureLoader::GetInstance().LoadTexture(TextureType::Albedo, rootDir + texturePath);
            if (loadedTexture == nullptr)
            {
                continue;
            }

            model.AddTexture(texturePath, std::move(loadedTexture));
        }
    }

    /*static*/ std::tuple<std::string, bool> AssimpModelLoader::GetAlbedoTexturePathFromMaterial(const aiMaterial& material)
    {
        if (material.GetTextureCount(aiTextureType_DIFFUSE) == 0)
        {
            return { "" , false };
        }

        // Support only 1 texture for now
        aiString texturePath;
        aiReturn result = material.GetTexture(aiTextureType_DIFFUSE, 0, &texturePath);
        if (result != aiReturn_SUCCESS)
        {
            return { "" , false };
        }

        return { texturePath.C_Str(), true };
    }

    /*static*/ void AssimpModelLoader::ImportAllMeshes(const aiScene& scene, Model& model)
    {
        for (std::size_t i = 0; i < scene.mNumMeshes; i++)
        {
            const aiMesh& mesh = *(scene.mMeshes[i]);
            const aiMaterial& material = *(scene.mMaterials[mesh.mMaterialIndex]);
            ImportMesh(mesh, material, model);
        }
    }

    /*static*/ void AssimpModelLoader::ImportMesh(const aiMesh& mesh, const aiMaterial& material, Model& model)
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

        if (mesh.GetNumUVChannels() > 0)
        {
            std::vector<Vector2f> textureMap;
            textureMap.reserve(mesh.mNumVertices);

            // Again, only one channel supported for the moment
            aiVector3D* uvs = mesh.mTextureCoords[0];
            for (std::size_t i = 0; i < mesh.mNumVertices; i++)
            {
                const aiVector3D& uv = uvs[i];
                textureMap.emplace_back(Vector2f { uv[0], uv[1] });
            }

            importedMesh->AddTextureMapping(textureMap);
        }

        std::vector<std::string> associatedAlbedoTextures;
        if (const auto [albedoPath, success] = GetAlbedoTexturePathFromMaterial(material); success)
        {
            associatedAlbedoTextures.emplace_back(albedoPath);
        }
        
        model.AddMesh(std::move(importedMesh), associatedAlbedoTextures);
    }
}