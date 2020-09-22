#include <lazye/backends/opengl/openglsprite.h>

#include <lazye/backends/opengl/opengltexture.h>
#include <lazye/backends/opengl/openglprogram.h>
#include <lazye/backends/opengl/builtin_shaders/basevertexshader.h>
#include <lazye/backends/opengl/builtin_shaders/basefragmentshader.h>

#include <lazye/backends/opengl/openglvertexarrayobject.h>

namespace lazye
{
    bool OpenGLSprite::ms_BaseInit { false };

    OpenGLVertexArrayObject& OpenGLSprite::GetSpriteBaseVAO()
    {
        static OpenGLVertexArrayObject s_SpriteBaseVAO { 4 };
        return s_SpriteBaseVAO;
    }

    const OpenGLProgram& OpenGLSprite::GetShaderProgram()
    {
        static OpenGLProgram s_ShaderProgram{ BaseVertexShader().Instantiate(), BaseFragmentShader().Instantiate() };
        return s_ShaderProgram;
    }

    OpenGLSprite::OpenGLSprite(std::byte* rawData, const ColorSpace& sourceSpace, unsigned int width, unsigned int height)
    {
        const OpenGLTexture::Info textureInfo({ TextureType::Albedo, ColorSpace::RGBA, sourceSpace, width, height, rawData });
        m_Texture = std::make_unique<OpenGLTexture>(textureInfo);
        InitializeBase();
    }

    OpenGLSprite::~OpenGLSprite() = default;

    void OpenGLSprite::InitializeBase()
    {
        if (ms_BaseInit)
        {
            return;
        }

        const std::vector<float> vertices =
        {
            -0.5f, 0.5f, 0.f,
            -0.5f, -0.5f, 0.f,
            0.5f, -0.5f, 0.f,
            0.5f, 0.5f, 0.f
        };
        static constexpr std::size_t POS_ATTR_SIZE = 3;
        GetSpriteBaseVAO().CreateAttributeOfType<GL_FLOAT>(POS_ATTR_SIZE,
        [&vertices](std::size_t e, std::size_t s)
        {
            return vertices[POS_ATTR_SIZE * e + s];
        });

        const std::vector<float> texCoordinates =
        {
            0.f, 1.f,
            0.f, 0.f,
            1.f, 0.f,
            1.f, 1.f
        };
        static constexpr std::size_t TEX_ATTR_SIZE = 2;
        GetSpriteBaseVAO().CreateAttributeOfType<GL_FLOAT>(TEX_ATTR_SIZE,
        [&texCoordinates](std::size_t e, std::size_t s)
        {
            return texCoordinates[TEX_ATTR_SIZE * e + s];
        });

        const std::vector<std::uint8_t> elements =
        {
            0, 1, 2, 0, 3, 2
        };
        GetSpriteBaseVAO().CreateElementBuffer(static_cast<GLsizei>(elements.size()),
        [&elements](std::size_t i)
        {
            return elements[i];
        });

        ms_BaseInit = true;
    }

    void OpenGLSprite::Draw
    (
        const Matrix44f& transform /*= Matrix44f::GetZero()*/, 
        const Matrix44f& view /*= Matrix44f::GetIdentity()*/, 
        const Matrix44f& projection /*= Matrix44f::GetIdentity()*/
    ) const
    {
        m_Texture->Bind();

        OpenGLProgram::Instance programInstance = GetShaderProgram().Instantiate();
        programInstance.SetUniform("Transform", transform);
        programInstance.SetUniform("View", view);
        programInstance.SetUniform("Projection", projection);
        programInstance.SetUniform("Albedo", m_Texture->GetTextureType().m_UnitIdx);
        
        GetSpriteBaseVAO().Draw();
    }
}