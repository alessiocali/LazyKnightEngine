#pragma once

#include <lke/backends/opengl/openglincludes.h>
#include <lke/backends/opengl/opengltypetraits.h>

#include <type_traits>

namespace lke
{
    /**
     *  Wrapper around an OpenGL VBO. It contains the buffer data and manages 
     *  creation and deletion of the buffer object.
     */
    template<GLenum TargetType, std::enable_if_t<lke::is_opengl_buffer_v<TargetType>, bool> = false>
    class OpenGLBufferObject final
    {
    public:
        class Binder;

        OpenGLBufferObject(std::size_t bufferSize, GLenum usageType = GL_STATIC_DRAW)
            :   m_BufferSize(bufferSize),
                m_UsageType(usageType)
        {
            glGenBuffers(1, &m_BufferID);
            Assert(m_BufferID != 0);

            m_Buffer.AsBytes = new GLbyte[bufferSize];
            Assert(m_Buffer.AsBytes != nullptr, "Failed OpenGL buffer allocation");
        }

        ~OpenGLBufferObject()
        {
            Assert(!m_Bound, "Deleting a VBO which is Bound, this shouldn't be possible!");

            if (m_BufferID != 0)
            {
                glDeleteBuffers(1, &m_BufferID);
            }

            delete[] m_Buffer.AsBytes;
            m_Buffer.AsBytes = nullptr;
        }

        OpenGLBufferObject(const OpenGLBufferObject& other) = delete;
        OpenGLBufferObject& operator=(const OpenGLBufferObject& other) = delete;

        // Allow move construction for emplace-back
        OpenGLBufferObject(OpenGLBufferObject&& other)
            :   m_BufferSize(std::exchange(other.m_BufferSize, 0)), 
                m_UsageType(other.m_UsageType),
                m_BufferID(std::exchange(other.m_BufferID, 0))
        {
            Assert(!other.m_Bound, "Trying to move a Bound OpenGLBuffer");
            m_Buffer.AsBytes = std::exchange(other.m_Buffer.AsBytes, nullptr);
        }

        OpenGLBufferObject operator=(OpenGLBufferObject&& other) = delete;

        /**
         *  Binds the VBO, returning a Binder object which manages the duration of the binding.
         *
         *  Binding a VBO multiple times is illegal.
         *
         *  @return A Binder object for this VBO. The value must not be ignored or the call
         *          will be pointless.
         */
        [[nodiscard]]
        inline Binder Bind() { return Binder(this); }

        /**
         *  Initializes the data inside this buffer using an initializer function.
         *
         *  @param elementCount:    How many elements to initialize
         *  @param attributeSize:   How many sub-elements per single element to initialize
         *  @param initializer:     A function in the form GLfloat(size_t e, size_t s) which returns the value
         *                          of element 'e' sub-element 's'.
         */
        template<typename GLType, typename Initializer, std::enable_if_t<std::is_same_v<GLType, GLfloat>, bool> = false>
        void Initialize(std::size_t elementCount, std::size_t attributeSize, Initializer initializer)
        {
            Initialize_Internal(elementCount, attributeSize, m_Buffer.AsFloats, initializer);
        }

        /**
         *  Initializes the data inside this buffer using an initializer function.
         *
         *  @param elementCount:    How many elements to initialize
         *  @param attributeSize:   How many sub-elements per single element to initialize
         *  @param initializer:     A function in the form GLint(size_t e, size_t s) which returns the value
         *                          of element 'e' sub-element 's'.
         */
        template<typename GLType, typename Initializer, std::enable_if_t<std::is_same_v<GLType, GLint>, bool> = false>
        void Initialize(std::size_t elementCount, std::size_t attributeSize, Initializer initializer)
        {
            Initialize_Internal(elementCount, attributeSize, m_Buffer.AsInts, initializer);
        }

        /**
         *  Initializes the data inside this buffer using an initializer function.
         *
         *  @param elementCount:    How many elements to initialize
         *  @param attributeSize:   How many sub-elements per single element to initialize
         *  @param initializer:     A function in the form GLuint(size_t e, size_t s) which returns the value
         *                          of element 'e' sub-element 's'.
         */
        template<typename GLType, typename Initializer, std::enable_if_t<std::is_same_v<GLType, GLuint>, bool> = false>
        void Initialize(std::size_t elementCount, std::size_t attributeSize, Initializer initializer)
        {
            Initialize_Internal(elementCount, attributeSize, m_Buffer.AsUInts, initializer);
        }

        /**
         *  A RAII-like object which wraps calls to glBindBuffer related to its owning VBO.
         *
         *  There can only be one active Binder per VBO, any further creation is illegal.
         *
         *  Binder instances should not be stored outside of the parent's lifecycle (not that
         *  this should be possible anyway)
         */
        class Binder final
        {
        public:
            ~Binder()
            {
                if (m_Owner != nullptr)
                {
                    glBindBuffer(TargetType, 0);
                    m_Owner->m_Bound = false;
                }
            }

            Binder(const Binder& other) = delete;
            Binder& operator=(const Binder& other) = delete;
            Binder operator=(Binder&& other) = delete;

            Binder(Binder&& other)
            {
                m_Owner = std::exchange(other.m_Owner, nullptr);
            }
            
        private:
            friend class OpenGLBufferObject;

            Binder(OpenGLBufferObject* owner)
                : m_Owner(owner)
            {
                Assert(m_Owner->m_BufferID != 0);
                Assert(!m_Owner->m_Bound, "Already bound VBO!");

                glBindBuffer(TargetType, m_Owner->m_BufferID);
                glBufferData(TargetType, m_Owner->m_BufferSize, m_Owner->m_Buffer.AsBytes, m_Owner->m_UsageType);

                m_Owner->m_Bound = true;
            }

            OpenGLBufferObject* m_Owner = nullptr;
        };

    private:
        friend class Binder;

        using GLPointerHelper = union
        {
            GLbyte* AsBytes;
            GLuint* AsUInts;
            GLint* AsInts;
            GLfloat* AsFloats;
        };

        std::size_t m_BufferSize = 0;
        GLPointerHelper m_Buffer;

        GLenum m_UsageType = GL_STATIC_DRAW;
        GLuint m_BufferID = 0;
        bool m_Bound = false;

        template<typename RawType, typename Initializer>
        void Initialize_Internal(std::size_t elementCount, std::size_t attributeSize, RawType* dataPtr, Initializer initializer)
        {
            Assert(elementCount * attributeSize * sizeof(RawType) <= m_BufferSize);
            Assert(reinterpret_cast<GLbyte*>(dataPtr) == m_Buffer.AsBytes, "Trying to initialize an invalid buffer!");
            
            std::size_t bufferIdx = 0;
            for (std::size_t elementIdx = 0; elementIdx < elementCount; elementIdx++)
            {
                for (std::size_t subIdx = 0; subIdx < attributeSize; subIdx++)
                {
                    dataPtr[bufferIdx++] = initializer(elementIdx, subIdx);
                }
            }
        }
    };

    using OpenGLVertexBufferObject = OpenGLBufferObject<GL_ARRAY_BUFFER>;
    using OpenGLElementBufferObject = OpenGLBufferObject<GL_ELEMENT_ARRAY_BUFFER>;
}