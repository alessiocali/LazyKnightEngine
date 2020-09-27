#pragma once
#include <lke/graphics/texture.h>

#include <lke/backends/opengl/openglincludes.h>

namespace lke
{
    class OpenGLTexture final : public Texture
    {
    public:
        virtual ~OpenGLTexture();

        virtual void Init(const InitInfo& info) override;

        const std::string& GetDefaultShaderAttributeName() const;
        const std::string& GetDefaultShaderEnableAttributeName() const;
        const unsigned int GetUnitIdx() const;

        void Bind() const;

    private:
        GLuint m_TextureID;
        TextureType m_Type { TextureType::Invalid };
    };
}