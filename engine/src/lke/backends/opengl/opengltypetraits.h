#pragma once

#include <lke/backends/opengl/openglincludes.h>

namespace lke
{
    template<GLenum AttributeType>
    struct gl_type_of { };

    template<>
    struct gl_type_of<GL_FLOAT>
    {
        using type = GLfloat;
    };

    template<>
    struct gl_type_of<GL_INT>
    {
        using type = GLint;
    };

    template<>
    struct gl_type_of<GL_UNSIGNED_INT>
    {
        using type = GLuint;
    };

    template<GLenum AttributeType>
    using gl_type_of_t = typename gl_type_of<AttributeType>::type;

    template<typename GLType>
    struct gl_enum_of { };

    template<>
    struct gl_enum_of<GLint>
    {
        static constexpr GLenum value = GL_INT;
    };

    template<>
    struct gl_enum_of<GLuint>
    {
        static constexpr GLenum value = GL_UNSIGNED_INT;
    };

    template<typename GLType>
    inline constexpr GLenum gl_enum_of_v = typename gl_enum_of<GLType>::value;

    /**
     *  Defined as true for every GLenum target which is valid for glBindBuffer, false otherwise
     */
    template<GLenum Target>
    inline constexpr bool is_opengl_buffer_v = 
           (Target == GL_ARRAY_BUFFER)
        || (Target == GL_ATOMIC_COUNTER_BUFFER)
        || (Target == GL_COPY_READ_BUFFER)
        || (Target == GL_COPY_WRITE_BUFFER)
        || (Target == GL_DISPATCH_INDIRECT_BUFFER)
        || (Target == GL_DRAW_INDIRECT_BUFFER)
        || (Target == GL_ELEMENT_ARRAY_BUFFER)
        || (Target == GL_PIXEL_PACK_BUFFER)
        || (Target == GL_PIXEL_UNPACK_BUFFER)
        || (Target == GL_QUERY_BUFFER)
        || (Target == GL_SHADER_STORAGE_BUFFER)
        || (Target == GL_TEXTURE_BUFFER)
        || (Target == GL_TRANSFORM_FEEDBACK_BUFFER)
        || (Target == GL_UNIFORM_BUFFER);

    /**
     *  Defined as true for every usage which is valid for glBufferData, false otherwise.
     */
    template<GLenum Usage>
    inline constexpr bool is_opengl_usage_v =
           (Usage == GL_STREAM_DRAW)
        || (Usage == GL_STREAM_READ)
        || (Usage == GL_STREAM_COPY)
        || (Usage == GL_STATIC_DRAW)
        || (Usage == GL_STATIC_READ)
        || (Usage == GL_STATIC_COPY)
        || (Usage == GL_DYNAMIC_DRAW)
        || (Usage == GL_DYNAMIC_COPY);
}