#pragma once

#include <lke/backends/opengl/openglshader.h>

namespace lke
{
    class OpenGLFragmentShader : public OpenGLShader
    {
    private:
        virtual GLenum GetShaderType() const override { return GL_FRAGMENT_SHADER; }
    };
}