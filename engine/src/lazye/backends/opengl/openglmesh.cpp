#include <lazye/backends/opengl/openglmesh.h>

#include <lazye/backends/opengl/builtin_shaders/meshfragmentshader.h>
#include <lazye/backends/opengl/builtin_shaders/meshvertexshader.h>
#include <lazye/backends/opengl/openglprogram.h>

namespace lazye
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

    void OpenGLMesh::SetIndices(const std::vector<unsigned int> indices)
    {
        m_VAO.CreateElementBuffer(static_cast<GLsizei>(indices.size()), [&indices](std::size_t i) { return indices[i]; });
    }

    void OpenGLMesh::Draw(
        const Matrix44f& transform /*= Matrix44f::GetIdentity()*/, 
        const Matrix44f& view /*= Matrix44f::GetIdentity()*/, 
        const Matrix44f& projection /*= Matrix44f::GetIdentity()*/
    )
    {
        OpenGLProgram::Instance programInstance = GetMeshProgram().Instantiate();

        programInstance.SetUniform("Transform", transform);
        programInstance.SetUniform("View", view);
        programInstance.SetUniform("Projection", projection);
        programInstance.SetUniform("Color", Vector4f { 0.4f, 0.4f, 0.4f, 1.0f });

        m_VAO.Draw();
    }

    /*static*/ const OpenGLProgram& OpenGLMesh::GetMeshProgram()
    {
        static const OpenGLProgram s_MeshProgram { MeshVertexShader().Instantiate(), MeshFragmentShader().Instantiate() };
        return s_MeshProgram;
    }
}

