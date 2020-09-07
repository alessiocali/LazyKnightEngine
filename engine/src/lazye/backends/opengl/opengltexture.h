#pragma once

#include <cstddef>

#include <lazye/backends/opengl/openglincludes.h>

namespace lazye
{
    struct TextureType
    {
        const GLenum m_Target;
        const GLenum m_Unit;
        const unsigned int m_UnitIdx;

        static const TextureType Albedo;

    private:
        TextureType(GLenum target, GLenum unit)
            : m_Target(target), m_Unit(unit), m_UnitIdx(unit - GL_TEXTURE0)
        { }
    };

    struct ColorSpace
    {
        const GLenum m_Format;

        static const ColorSpace RGB;
        static const ColorSpace RGBA;

    private:
        ColorSpace(GLenum format)
            : m_Format(format)
        { }
    };

    class OpenGLTexture final
    {
    public:
        struct Info
        {
            const TextureType&  m_Type;
            const ColorSpace&   m_TargetSpace;
            const ColorSpace&   m_SourceSpace;
            unsigned int        m_Width;
            unsigned int        m_Height;
            std::byte*          m_Data;
        };

        OpenGLTexture(Info info);
        ~OpenGLTexture();

        inline const TextureType& GetTextureType() const { return m_Type; }

        void Bind();

    private:
        const TextureType& m_Type;
        GLuint m_TextureID;
    };
}