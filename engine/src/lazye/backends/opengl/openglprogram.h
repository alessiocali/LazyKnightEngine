#pragma once

#include <lazye/backends/opengl/openglincludes.h>

#include <lazye/backends/opengl/openglvertexshader.h>
#include <lazye/backends/opengl/openglfragmentshader.h>

namespace lazye
{
    class OpenGLProgram final
    {
    public:
        OpenGLProgram(const OpenGLVertexShader::Instance& vertexShader, const OpenGLFragmentShader::Instance& fragmentShader);
        ~OpenGLProgram();

        OpenGLProgram(const OpenGLProgram& other) = delete;
        OpenGLProgram& operator=(const OpenGLProgram& other) = delete;

        OpenGLProgram(OpenGLProgram&& other);
        OpenGLProgram& operator=(OpenGLProgram&& other);

        void Activate() const;

    private:
        GLuint m_ProgramID = 0;
    };
}