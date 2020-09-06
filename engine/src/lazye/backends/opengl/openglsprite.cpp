#include <lazye/backends/opengl/openglsprite.h>

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

    OpenGLSprite::OpenGLSprite()
    {
        InitializeBase();
    }

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

    void OpenGLSprite::Draw() const
    {
        // TODO: Actually draw a texture and not some uniform thingy
        OpenGLProgram::Instance programInstance = GetShaderProgram().Instantiate();
        programInstance.SetUniform("Tint", Vector4f{ 1.f, 0.5f, 0.f, 1.f });

        GetSpriteBaseVAO().Draw();
    }
}