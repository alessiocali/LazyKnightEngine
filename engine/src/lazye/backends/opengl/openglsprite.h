#pragma once

namespace lazye
{
    class OpenGLVertexArrayObject;
    class OpenGLProgram;

    class OpenGLSprite final
    {
    public:
        OpenGLSprite();

        void Draw() const;

    private:
        static OpenGLVertexArrayObject& GetSpriteBaseVAO();
        static const OpenGLProgram& GetShaderProgram();
        static bool ms_BaseInit;

        static void InitializeBase();
    };
}