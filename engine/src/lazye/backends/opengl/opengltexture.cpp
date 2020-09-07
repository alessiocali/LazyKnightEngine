#include <lazye/backends/opengl/opengltexture.h>

namespace lazye
{
    const TextureType TextureType::Albedo   { GL_TEXTURE_2D, GL_TEXTURE0 };

    const ColorSpace ColorSpace::RGB    { GL_RGB };
    const ColorSpace ColorSpace::RGBA   { GL_RGBA };

    OpenGLTexture::OpenGLTexture(OpenGLTexture::Info info)
        : m_Type(info.m_Type)
    {
        Assert(info.m_Data != nullptr);

        glGenTextures(1, &m_TextureID);
        Assert(m_TextureID != 0);

        Bind();
        glTexParameteri(m_Type.m_Target, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(m_Type.m_Target, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(m_Type.m_Target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(m_Type.m_Target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        static constexpr int MIPMAP_LEVEL = 0;
        static constexpr int DEPRECATED = 0;
        static constexpr GLenum DATA_TYPE = GL_UNSIGNED_BYTE;
        glTexImage2D(
            m_Type.m_Target,
            MIPMAP_LEVEL,
            info.m_TargetSpace.m_Format,
            info.m_Width,
            info.m_Height,
            DEPRECATED,
            info.m_TargetSpace.m_Format,
            DATA_TYPE,
            info.m_Data
        );
        glGenerateMipmap(m_Type.m_Target);
    }

    OpenGLTexture::~OpenGLTexture()
    {
        glDeleteTextures(1, &m_TextureID);
        m_TextureID = 0;
    }

    void OpenGLTexture::Bind()
    {
        glActiveTexture(m_Type.m_Unit);
        glBindTexture(m_Type.m_Target, m_TextureID);
    }
}