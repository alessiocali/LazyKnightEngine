#pragma once

#include <lke/backends/opengl/openglshader.h>

namespace lke
{
    class OpenGLVertexShader : public OpenGLShader
    {
    private:
        virtual GLenum GetShaderType() const override { return GL_VERTEX_SHADER; }
    };
}