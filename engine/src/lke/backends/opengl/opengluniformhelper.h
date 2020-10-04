#pragma once

#include <lke/backends/opengl/openglincludes.h>
#include <lke/math/vectors.h>
#include <lke/math/matrix.h>

namespace lke::OpenGLUniformHelper
{
    inline void SetUniform(GLint location, float v0) { glUniform1f(location, v0); }
    inline void SetUniform(GLint location, float v0, float v1) { glUniform2f(location, v0, v1); }
    inline void SetUniform(GLint location, float v0, float v1, float v2) { glUniform3f(location, v0, v1, v2); }
    inline void SetUniform(GLint location, float v0, float v1, float v2, float v4) { glUniform4f(location, v0, v1, v2, v4); }
    inline void SetUniform(GLint location, const Vector2f& v) { glUniform2fv(location, 1, v.GetDataPtr()); }
    inline void SetUniform(GLint location, const Vector3f& v) { glUniform3fv(location, 1, v.GetDataPtr()); }
    inline void SetUniform(GLint location, const Vector4f& v) { glUniform4fv(location, 1, v.GetDataPtr()); }
    
    inline void SetUniform(GLint location, unsigned int v0) { glUniform1ui(location, v0); }
    inline void SetUniform(GLint location, unsigned int v0, unsigned int v1) { glUniform2ui(location, v0, v1); }
    inline void SetUniform(GLint location, unsigned int v0, unsigned int v1, unsigned int v2) { glUniform3ui(location, v0, v1, v2); }
    inline void SetUniform(GLint location, unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v4) { glUniform4ui(location, v0, v1, v2, v4); }
    inline void SetUniform(GLint location, const Vector2ui& v) { glUniform2uiv(location, 1, v.GetDataPtr()); }
    inline void SetUniform(GLint location, const Vector3ui& v) { glUniform3uiv(location, 1, v.GetDataPtr()); }
    inline void SetUniform(GLint location, const Vector4ui& v) { glUniform4uiv(location, 1, v.GetDataPtr()); }
    
    inline void SetUniform(GLint location, int v0) { glUniform1i(location, v0); }
    inline void SetUniform(GLint location, int v0, int v1) { glUniform2i(location, v0, v1); }
    inline void SetUniform(GLint location, int v0, int v1, int v2) { glUniform3i(location, v0, v1, v2); }
    inline void SetUniform(GLint location, int v0, int v1, int v2, int v4) { glUniform4i(location, v0, v1, v2, v4); }
    inline void SetUniform(GLint location, const Vector2i& v) { glUniform2iv(location, 1, v.GetDataPtr()); }
    inline void SetUniform(GLint location, const Vector3i& v) { glUniform3iv(location, 1, v.GetDataPtr()); }
    inline void SetUniform(GLint location, const Vector4i& v) { glUniform4iv(location, 1, v.GetDataPtr()); }

    // lke matrices are row-major, glUniformMatrix expects column major (translation in 13th to 15th), so...
    inline void SetUniform(GLint location, const Matrix44f& m) { glUniformMatrix4fv(location, 1, GL_TRUE, m.GetDataPtr()); }
}