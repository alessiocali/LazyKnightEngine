#include <lke/graphics/sprite.h>

#include <memory>

#include <lke/assets/textureloader.h>
#include <lke/graphics/graphicsfactory.h>
#include <lke/graphics/mesh.h>
#include <lke/graphics/texture.h>

namespace lke
{
    /*static*/ Mesh& Sprite::GetBaseMesh()
    {
        static std::unique_ptr<Mesh> s_BaseMesh { GraphicsFactory::GetInstance().CreateMesh(4) };
        static bool s_Init { false };

        if (!s_Init)
        {
            s_BaseMesh->AddVertices
            ({
                { -0.5f, 0.f,  0.5f },
                { -0.5f, 0.f, -0.5f },
                {  0.5f, 0.f, -0.5f },
                {  0.5f, 0.f,  0.5f }
            });

            s_BaseMesh->AddTextureMapping
            ({
                { 0.f, 1.f },
                { 0.f, 0.f },
                { 1.f, 0.f },
                { 1.f, 1.f },
            });

            s_BaseMesh->SetIndices({ 0, 1, 2, 0, 3, 2 });

            s_Init = true;
        }

        return *s_BaseMesh;
    }

    Sprite::Sprite(const std::string& spritePath)
    {
        m_Texture = TextureLoader::GetInstance().LoadTexture(TextureType::Albedo, spritePath);
    }

    Sprite::~Sprite() = default;

    void Sprite::Draw(const Matrix44f& transform, const Matrix44f& view, const Matrix44f& projection)
    {
        Mesh& baseMesh = GetBaseMesh();
        baseMesh.AssociateTextures({ m_Texture });
        baseMesh.Draw(transform, view, projection);
    }

}