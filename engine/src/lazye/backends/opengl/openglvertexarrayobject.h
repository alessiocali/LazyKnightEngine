#pragma once

#include <lazye/lazye.h>

#include <vector>
#include <type_traits>

#include <lazye/backends/opengl/openglincludes.h>
#include <lazye/backends/opengl/openglbufferobject.h>
#include <lazye/backends/opengl/openglvertexattribute.h>

namespace lazye
{
    class OpenGLProgram;

    /**
     *  Wrapper around an OpenGL VertexArrayObject. It contains methods for adding and
     *  initializing {@link OpenGLVertexAttribute}s backed by one 
     *  {@link OpenGLVertexBufferObject} each.
     *
     *  It can also contain one instance of an {@link OpenGLElementBufferObject}; adding
     *  more than one destroys implicitly the previous instance.
     *
     *  Attributes / VBO couples and EBOs are initialized by means of initializer functions 
     *  (see, respectively, {@link #CreateAttributeOfType} and {@link #CreateElementBuffer}.
     *
     *  VAOs need to be bound before being used, see the {@link Bind} method.
     */
    class OpenGLVertexArrayObject final
    {
    public:
        class Binder;

        OpenGLVertexArrayObject(GLsizei vertexCount);
        ~OpenGLVertexArrayObject();

        OpenGLVertexArrayObject(const OpenGLVertexArrayObject& other) = delete;
        OpenGLVertexArrayObject& operator=(const OpenGLVertexArrayObject& other) = delete;

        /**
         *  Creates a new OpenGLVertex attribute and backs it with a dedicated Vertex
         *  Buffer Object.
         *
         *  @param <AttributeType>: the type of the unit element of the Attribute
         *                          (supported are GL_FLOAT, GL_INT and GL_UNSIGNED_INT)
         *
         *  @param size:            the size of the attribute.
         *
         *  @param initializer:     a functor in the form GLfloat(size_t e, size_t s)
         *                          which return the attribute data for each element 'e'
         *                          for each value of 's' between 0 and size.
         */
        template<GLenum AttributeType, typename Initializer>
        std::size_t CreateAttributeOfType(GLuint attributeSize, Initializer initializer)
        {
            Assert(!m_Bound, "Modifying a bound VAO is illegal");

            using GLType = gl_type_of_t<AttributeType>;

            const GLsizei strideSize = attributeSize * sizeof(GLType);

            OpenGLVertexBufferObject& newBuffer = m_VertexBufferObjects.emplace_back(m_VertexCount * strideSize);
            newBuffer.Initialize<GLType>(m_VertexCount, attributeSize, initializer);

            Assert(m_VertexBufferObjects.size() > 0);
            GLint bufferIdx = static_cast<GLint>(m_VertexBufferObjects.size() - 1);

            m_Attributes.emplace_back(bufferIdx, attributeSize, AttributeType, static_cast<GLboolean>(GL_FALSE), strideSize, nullptr);
            Assert(m_VertexBufferObjects.size() == m_Attributes.size());

            m_Dirty = true;

            return bufferIdx;
        }

        /**
         *  Adds an ElementBufferObject to this VertexArrayObject.
         *
         *  @param elementCount:    how many elements are in the ElementBuffer.
         *
         *  @param initializer:     a functor of type GLint(size_t i) which returns
         *                          the value of element 'i'
         */
        template<typename Initializer>
        void CreateElementBuffer(GLsizei elementCount, Initializer initializer)
        {
            using GLType = gl_type_of_t<GL_UNSIGNED_INT>;

            Assert(!m_Bound, "Modifying a bound VAO is illegal");

            m_ElementBufferObject = std::make_unique<OpenGLElementBufferObject>(elementCount * sizeof(GLuint));
            Assert(m_ElementBufferObject != nullptr);
            m_ElementBufferObject->Initialize<GLType>(elementCount, 1,
            [&initializer](std::size_t e, std::size_t s)
            {
                return initializer(e);
            });

            m_ElementCount = elementCount;

            m_Dirty = true;
        }

        /**
         *  Binds this VAO, and returns a Binder which manages the duration of the binding.
         *
         *  Binding a VAO multiple times is illegal.
         *
         *  The return value must not be ignored, otherwise the call is pointless
         */
        [[nodiscard]]
        Binder Bind();

        /**
         *  Automatically draws this VAO using its EBO. Fails if no EBO is set.
         */
        void Draw();

        class Binder
        {
        public:
            ~Binder();

        private:
            friend class OpenGLVertexArrayObject;

            Binder(OpenGLVertexArrayObject* owner);

            OpenGLVertexArrayObject* m_Owner;
        };

    private:
        friend class Binder;

        void DeleteCurrentArray();
        void CreateNewArray();
        void Regenerate();

        [[nodiscard]]
        Binder Bind_Internal();

        const GLsizei m_VertexCount = 0;
        GLsizei m_ElementCount = 0;

        GLuint m_ArrayID = 0;
        bool m_Bound = false;
        bool m_Dirty = true;
        std::vector<OpenGLVertexBufferObject> m_VertexBufferObjects;
        std::vector<OpenGLVertexAttribute> m_Attributes;
        std::unique_ptr<OpenGLElementBufferObject> m_ElementBufferObject;
    };
}