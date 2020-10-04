#include <lke/backends/opengl/openglprogram.h>

namespace lke
{
    bool OpenGLProgram::Instance::ms_ProgramUsageFlag { false };

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

    OpenGLProgram::Instance OpenGLProgram::Instantiate() const
    {
        return Instance(this);
    }

    OpenGLProgram::Instance::Instance(const OpenGLProgram* owner)
        : m_OwnerProgramID(owner->m_ProgramID)
    {
        Assert(!ms_ProgramUsageFlag);
        Assert(owner->m_ProgramID != 0);
        glUseProgram(owner->m_ProgramID);
        ms_ProgramUsageFlag = true;
    }

    OpenGLProgram::Instance::~Instance()
    {
        Assert(ms_ProgramUsageFlag);
        glUseProgram(0);
        ms_ProgramUsageFlag = false;
    }

    GLint OpenGLProgram::Instance::GetUniformLocationFromName(const std::string& name) const
    {
        return glGetUniformLocation(m_OwnerProgramID, name.c_str());
    }
}