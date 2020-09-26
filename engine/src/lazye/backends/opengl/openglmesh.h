#pragma once
#include <lazye/graphics/mesh.h>

#include <lazye/backends/opengl/openglvertexarrayobject.h>

#include <lazye/math/matrix.h>

namespace lazye
{
    class OpenGLProgram;

    class OpenGLMesh final : public Mesh
    {
    public:
        OpenGLMesh(std::size_t numVertices);

        void AddVertices(const std::vector<Vector3f>& vertices) override;
        void SetIndices(const std::vector<unsigned int> indices) override;

        void Draw(const Matrix44f& transform = Matrix44f::GetIdentity(), const Matrix44f& view = Matrix44f::GetIdentity(), const Matrix44f& projection = Matrix44f::GetIdentity());

    private:
        static const OpenGLProgram& GetMeshProgram();

        OpenGLVertexArrayObject m_VAO;
    };
}