#pragma once
#include <lazye/graphics/mesh.h>

#include <lazye/backends/opengl/openglprogram.h>
#include <lazye/backends/opengl/openglvertexarrayobject.h>

#include <lazye/math/matrix.h>

namespace lazye
{
    class OpenGLMesh final : public Mesh
    {
    public:
        OpenGLMesh(std::size_t numVertices);

        void AddVertices(const std::vector<Vector3f>& vertices) override;
        void AddTextureMapping(const std::vector<Vector2f>& mapping) override;
        void SetIndices(const std::vector<unsigned int>& indices) override;
        void AssociateTextures(const std::vector<std::weak_ptr<Texture>>& textures) override;
        void Draw(const Matrix44f& transform, const Matrix44f& view, const Matrix44f& projection) override;

    private:
        static const OpenGLProgram& GetMeshProgram();

        void BindAssociatedTextures(const OpenGLProgram::Instance& programInstance);

        OpenGLVertexArrayObject m_VAO;
        std::vector<std::weak_ptr<Texture>> m_AssociatedTextures;
    };
}