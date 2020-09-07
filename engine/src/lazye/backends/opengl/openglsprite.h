#pragma once

#include <memory.h>

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

        void Draw() const;

    private:
        static OpenGLVertexArrayObject& GetSpriteBaseVAO();
        static const OpenGLProgram& GetShaderProgram();
        static bool ms_BaseInit;

        static void InitializeBase();

        std::unique_ptr<OpenGLTexture> m_Texture;
    };
}