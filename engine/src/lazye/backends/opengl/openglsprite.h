#pragma once

#include <memory.h>

#include <lazye/math/math.h>

namespace lazye
{
    class OpenGLVertexArrayObject;
    class OpenGLProgram;
    class OpenGLTexture;
    struct ColorSpace;

    class OpenGLSprite final
    {
    public:
        OpenGLSprite(std::byte* rawData, const ColorSpace& sourceSpace, unsigned int width, unsigned int height);
        ~OpenGLSprite();

        void Draw(const Matrix44f& transform = Matrix44f::GetIdentity(), const Matrix44f& view = Matrix44f::GetIdentity(), const Matrix44f& projection = Matrix44f::GetIdentity()) const;

    private:
        static OpenGLVertexArrayObject& GetSpriteBaseVAO();
        static const OpenGLProgram& GetShaderProgram();
        static bool ms_BaseInit;

        static void InitializeBase();

        std::unique_ptr<OpenGLTexture> m_Texture;
    };
}