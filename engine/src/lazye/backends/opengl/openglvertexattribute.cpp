#include <lazye/backends/opengl/openglvertexattribute.h>

namespace lazye
{
    OpenGLVertexAttribute::OpenGLVertexAttribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* offset)
        : m_Index(index), m_Size(size), m_Type(type), m_Normalized(normalized), m_Stride(stride), m_Offset(offset)
    { }

    OpenGLVertexAttribute::Instance::Instance(const OpenGLVertexAttribute* owner)
        : m_OwnerIndex(owner->m_Index)
    {
        glVertexAttribPointer(
            owner->m_Index, 
            owner->m_Size, 
            owner->m_Type, 
            owner->m_Normalized, 
            owner->m_Stride,
            owner->m_Offset
        );
        
        glEnableVertexAttribArray(owner->m_Index);

        m_Valid = true;
    }

    OpenGLVertexAttribute::Instance::~Instance()
    {
        if (m_Valid)
        {
            glDisableVertexAttribArray(m_OwnerIndex);
            m_Valid = false;
        }
    }

    OpenGLVertexAttribute::Instance::Instance(OpenGLVertexAttribute::Instance&& other)
        : m_OwnerIndex(other.m_OwnerIndex), m_Valid(other.m_Valid)
    {
        other.m_Valid = false;
    }

    OpenGLVertexAttribute::Instance& OpenGLVertexAttribute::Instance::operator=(OpenGLVertexAttribute::Instance&& other)
    {
        if (this != &other)
        {
            std::swap(m_OwnerIndex, other.m_OwnerIndex);
            std::swap(m_Valid, other.m_Valid);
        }

        return *this;
    }
}