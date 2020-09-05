#pragma once

#include <lazye/backends/opengl/openglshader.h>

namespace lazye
{
    class OpenGLVertexShader : public OpenGLShader
    {
    private:
        virtual GLenum GetShaderType() const override { return GL_VERTEX_SHADER; }
    };
}