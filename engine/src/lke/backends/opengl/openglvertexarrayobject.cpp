#include <lke/backends/opengl/openglvertexarrayobject.h>

#include <lke/backends/opengl/openglprogram.h>

namespace lke
{
    OpenGLVertexArrayObject::OpenGLVertexArrayObject(GLsizei vertexCount)
        :   m_VertexCount(vertexCount),
            m_Dirty(true)
    { }

    OpenGLVertexArrayObject::~OpenGLVertexArrayObject()
    {
        Assert(!m_Bound, "Destroying a bound VAO, this should not be possible!");
        DeleteCurrentArray();
    }

    OpenGLVertexArrayObject::Binder OpenGLVertexArrayObject::Bind()
    {
        if (m_Dirty)
        {
            Regenerate();
        }

        return Bind_Internal();
    }

    void OpenGLVertexArrayObject::Draw()
    {
        if (m_ElementBufferObject == nullptr)
        {
            return;
        }
        
        Binder vaoBinder = Bind();
        glDrawElements(GL_TRIANGLES, m_ElementCount, GL_UNSIGNED_INT, static_cast<void*>(0));
    }

    void OpenGLVertexArrayObject::DeleteCurrentArray()
    {
        if (m_ArrayID != 0)
        {
            glDeleteVertexArrays(1, &m_ArrayID);
            m_ArrayID = 0;
        }
    }

    void OpenGLVertexArrayObject::CreateNewArray()
    {
        Assert(m_ArrayID == 0);
        glGenVertexArrays(1, &m_ArrayID);
        Assert(m_ArrayID != 0);
    }

    void OpenGLVertexArrayObject::Regenerate()
    {
        DeleteCurrentArray();
        CreateNewArray();

        Assert(m_VertexBufferObjects.size() == m_Attributes.size());

        // Attributes and EBOs need to be disabled *after* the VAO is unbound
        std::vector<OpenGLVertexAttribute::Instance> attributeInstances;
        std::vector<OpenGLElementBufferObject::Binder> elementBinders;

        OpenGLVertexArrayObject::Binder arrayBinder = Bind_Internal();
        for (std::size_t i = 0; i < m_VertexBufferObjects.size(); i++)
        {
            OpenGLVertexBufferObject::Binder bufferBinder = m_VertexBufferObjects[i].Bind();
            attributeInstances.emplace_back(m_Attributes[i].Instantiate());
        }

        if (m_ElementBufferObject != nullptr)
        {
            elementBinders.emplace_back(m_ElementBufferObject->Bind());
        }

        Assert(elementBinders.size() == 1);

        m_Dirty = false;
    }

    OpenGLVertexArrayObject::Binder OpenGLVertexArrayObject::Bind_Internal()
    {
        return Binder(this);
    }

    OpenGLVertexArrayObject::Binder::Binder(OpenGLVertexArrayObject* owner)
        : m_Owner(owner)
    {
        Assert(!m_Owner->m_Bound);
        Assert(m_Owner->m_ArrayID != 0);

        glBindVertexArray(m_Owner->m_ArrayID);
        m_Owner->m_Bound = true;
    }

    OpenGLVertexArrayObject::Binder::~Binder()
    {
        Assert(m_Owner->m_Bound);
        glBindVertexArray(0);
        m_Owner->m_Bound = false;
    }
}