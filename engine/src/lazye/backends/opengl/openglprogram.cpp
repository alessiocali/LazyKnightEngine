#include <lazye/backends/opengl/openglprogram.h>

namespace lazye
{
    OpenGLProgram::OpenGLProgram(const OpenGLVertexShader::Instance& vertexShader, const OpenGLFragmentShader::Instance& fragmentShader)
    {
        m_ProgramID = glCreateProgram();
        Assert(m_ProgramID);

        glAttachShader(m_ProgramID, vertexShader.GetShaderID());
        glAttachShader(m_ProgramID, fragmentShader.GetShaderID());
        glLinkProgram(m_ProgramID);

        GLint success;
        glGetShaderiv(m_ProgramID, GL_LINK_STATUS, &success);
        Assert(success);
    }

    OpenGLProgram::OpenGLProgram(OpenGLProgram&& other)
        : m_ProgramID(std::exchange(other.m_ProgramID, 0))
    { }

    OpenGLProgram& OpenGLProgram::operator=(OpenGLProgram&& other)
    {
        if (this != &other)
        {
            std::swap(m_ProgramID, other.m_ProgramID);
        }

        return *this;
    }

    OpenGLProgram::~OpenGLProgram()
    {
        if (m_ProgramID != 0)
        {
            glDeleteProgram(m_ProgramID);
        }
    }

    void OpenGLProgram::Activate() const
    {
        glUseProgram(m_ProgramID);
    }
}