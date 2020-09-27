#pragma once

#include <lke/backends/opengl/openglincludes.h>

namespace lke
{
    /**
     *  A wrapper around OpenGLVertexAttribute data. To enable the Attribute call Instantiate.
     */
    class OpenGLVertexAttribute final
    {
    public:
        class Instance;

        OpenGLVertexAttribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* offset);

        /**
         *  Creates an Instance of this attribute and binds it to the currently active ARRAY_BUFFER object.
         *
         *  @return A RAII instance of this Attribute.
         */
        [[nodiscard]]
        inline Instance Instantiate() const { return Instance(this); }

        /**
         *  A RAII object which wraps calls around glVertexAttribPointer and glEnable/DisableAttribArray
         */
        class Instance
        {
        public:
            ~Instance();

            Instance(const Instance& other) = delete;
            Instance& operator=(const Instance& other) = delete;

            Instance(Instance&& other);
            Instance& operator=(Instance&& other);

        private:
            friend class OpenGLVertexAttribute;

            Instance(const OpenGLVertexAttribute* owner);

            GLuint  m_OwnerIndex = 0;
            bool    m_Valid = false;
        };

    private:
        friend class Instance;

        const GLuint        m_Index;
        const GLint         m_Size;
        const GLenum        m_Type;
        const GLboolean     m_Normalized;
        const GLsizei       m_Stride;
        const GLvoid* const m_Offset;
    };
}