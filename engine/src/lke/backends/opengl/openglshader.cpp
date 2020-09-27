#include <lke/backends/opengl/openglshader.h>

namespace lke
{
    OpenGLShader::Instance::Instance(const OpenGLShader* owner)
    {
        m_ShaderID = glCreateShader(owner->GetShaderType());
        Assert(m_ShaderID);

        glShaderSource(m_ShaderID, 1, owner->GetSource(), nullptr);
        glCompileShader(m_ShaderID);

        GLint success;
        glGetShaderiv(m_ShaderID, GL_COMPILE_STATUS, &success);
        Assert(success);
    }

    OpenGLShader::Instance::~Instance()
    {
        glDeleteShader(m_ShaderID);
    }
}