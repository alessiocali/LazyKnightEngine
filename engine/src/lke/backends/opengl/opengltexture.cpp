#include <lke/backends/opengl/opengltexture.h>

#include <unordered_map>

namespace lke
{
    struct OpenGLTextureInfo
    { 
        const std::string DefaultAttributeName;
        const std::string DefaultEnableAttributeName;
        const GLenum Target;
        const GLenum Unit;
        const unsigned int UnitIdx;

        OpenGLTextureInfo(const std::string& attributeName, const std::string& enableAttributeName, GLenum target, GLenum unit)
            : DefaultAttributeName(attributeName)
            , DefaultEnableAttributeName(enableAttributeName)
            , Target(target)
            , Unit(unit)
            , UnitIdx(unit - GL_TEXTURE0)
        { }
    };

    const std::unordered_map<TextureType, OpenGLTextureInfo> OpenGLTextureInfos =
    {
        { TextureType::Albedo, { "Albedo", "UseAlbedo", GL_TEXTURE_2D, GL_TEXTURE0 } }
    };

    const std::unordered_map<ColorSpace, GLint> OpenGLColorSpaces =
    {
        { ColorSpace::RGB, GL_RGB },
        { ColorSpace::RGBA, GL_RGBA }
    };

    OpenGLTexture::~OpenGLTexture()
    {
        glDeleteTextures(1, &m_TextureID);
        m_TextureID = 0;
    }

    void OpenGLTexture::Init(const InitInfo& info)
    {
        Assert(info.Data != nullptr);

        glGenTextures(1, &m_TextureID);
        Assert(m_TextureID != 0);

        const OpenGLTextureInfo& glTextureInfo = OpenGLTextureInfos.at(info.Type);

        m_Type = info.Type;

        Bind();

        glTexParameteri(glTextureInfo.Target, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(glTextureInfo.Target, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(glTextureInfo.Target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(glTextureInfo.Target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        static constexpr int MIPMAP_LEVEL = 0;
        static constexpr int DEPRECATED = 0;
        static constexpr GLenum DATA_TYPE = GL_UNSIGNED_BYTE;

        glTexImage2D(
            glTextureInfo.Target,
            MIPMAP_LEVEL,
            OpenGLColorSpaces.at(info.TargetSpace),
            info.Width,
            info.Height,
            DEPRECATED,
            OpenGLColorSpaces.at(info.SourceSpace),
            DATA_TYPE,
            info.Data
        );

        glGenerateMipmap(glTextureInfo.Target);
    }

    const std::string& OpenGLTexture::GetDefaultShaderAttributeName() const
    {
        return OpenGLTextureInfos.at(m_Type).DefaultAttributeName;
    }

    const std::string& OpenGLTexture::GetDefaultShaderEnableAttributeName() const
    {
        return OpenGLTextureInfos.at(m_Type).DefaultEnableAttributeName;
    }

    unsigned int OpenGLTexture::GetUnitIdx() const
    {
        return OpenGLTextureInfos.at(m_Type).UnitIdx;
    }

    void OpenGLTexture::Bind() const
    {
        const OpenGLTextureInfo& glTextureInfo = OpenGLTextureInfos.at(m_Type);

        glActiveTexture(glTextureInfo.Unit);
        glBindTexture(glTextureInfo.Target, m_TextureID);
    }
}