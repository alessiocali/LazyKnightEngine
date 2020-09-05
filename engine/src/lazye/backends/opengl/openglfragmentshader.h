#pragma once

#include <lazye/backends/opengl/openglshader.h>

namespace lazye
{
    class OpenGLFragmentShader : public OpenGLShader
    {
    private:
        virtual GLenum GetShaderType() const override { return GL_FRAGMENT_SHADER; }
    };
}