#include <lazye/graphics/sprite.h>

#include <memory>

#include <lazye/assets/textureloader.h>
#include <lazye/graphics/graphicsfactory.h>
#include <lazye/graphics/mesh.h>
#include <lazye/graphics/texture.h>

namespace lazye
{
    /*static*/ Mesh& Sprite::GetBaseMesh()
    {
        static std::unique_ptr<Mesh> s_BaseMesh = GraphicsFactory::GetInstance().CreateMesh(4);
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

    void Sprite::Draw(const Matrix44f& view, const Matrix44f& projection)
    {
        Mesh& baseMesh = GetBaseMesh();
        baseMesh.AssociateTextures({ m_Texture });
        baseMesh.Draw(m_Transform.GetMatrix(), view, projection);
    }

}