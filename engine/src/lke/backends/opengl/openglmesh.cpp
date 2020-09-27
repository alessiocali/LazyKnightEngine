#include <lke/backends/opengl/openglmesh.h>

#include <lke/backends/opengl/builtin_shaders/basefragmentshader.h>
#include <lke/backends/opengl/builtin_shaders/basevertexshader.h>
#include <lke/backends/opengl/openglprogram.h>
#include <lke/backends/opengl/opengltexture.h>

namespace lke
{
    OpenGLMesh::OpenGLMesh(std::size_t numVertices)
        : m_VAO(static_cast<GLsizei>(numVertices))
    { }

    void OpenGLMesh::AddVertices(const std::vector<Vector3f>& vertices)
    {
        constexpr GLuint POS_ATTR_SIZE = 3;
        m_VAO.CreateAttributeOfType<GL_FLOAT>(POS_ATTR_SIZE, [&vertices](std::size_t e, std::size_t s)
        {
            return vertices[e][s];
        });
    }

    void OpenGLMesh::AddTextureMapping(const std::vector<Vector2f>& mapping)
    {
        constexpr GLuint POS_ATTR_SIZE = 2;
        m_VAO.CreateAttributeOfType<GL_FLOAT>(POS_ATTR_SIZE, [&mapping](std::size_t e, std::size_t s)
        {
            return mapping[e][s];
        });
    }

    void OpenGLMesh::SetIndices(const std::vector<unsigned int>& indices)
    {
        m_VAO.CreateElementBuffer(static_cast<GLsizei>(indices.size()), [&indices](std::size_t i) { return indices[i]; });
    }

    void OpenGLMesh::AssociateTextures(const std::vector<std::weak_ptr<Texture>>& textures)
    {
        m_AssociatedTextures.clear();
        m_AssociatedTextures.reserve(textures.size());
        m_AssociatedTextures.insert(m_AssociatedTextures.end(), textures.begin(), textures.end());
    }

    void OpenGLMesh::Draw(const Matrix44f& transform, const Matrix44f& view, const Matrix44f& projection)
    {
        const OpenGLProgram::Instance programInstance = GetMeshProgram().Instantiate();

        BindAssociatedTextures(programInstance);

        // A nice eyesore Magenta
        programInstance.SetUniform("FallbackColor", Vector4f { 1.f, 0.f, 1.f, 1.f });

        programInstance.SetUniform("Transform", transform);
        programInstance.SetUniform("View", view);
        programInstance.SetUniform("Projection", projection);

        m_VAO.Draw();
    }

    void OpenGLMesh::BindAssociatedTextures(const OpenGLProgram::Instance& programInstance)
    {
        for (const auto& texture : m_AssociatedTextures)
        {
            if (std::shared_ptr lockedTexture(texture); lockedTexture)
            {
                const OpenGLTexture& glTexture = static_cast<const OpenGLTexture&>(*lockedTexture);
                
                glTexture.Bind();
                programInstance.SetUniform(glTexture.GetDefaultShaderAttributeName(), glTexture.GetUnitIdx());
                programInstance.SetUniform(glTexture.GetDefaultShaderEnableAttributeName(), true);
            }
        }
    }

    /*static*/ const OpenGLProgram& OpenGLMesh::GetMeshProgram()
    {
        static const OpenGLProgram s_MeshProgram { BaseVertexShader().Instantiate(), BaseFragmentShader().Instantiate() };
        return s_MeshProgram;
    }
}

