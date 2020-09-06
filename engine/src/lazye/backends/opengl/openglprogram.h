#pragma once

#include <lazye/backends/opengl/openglincludes.h>

#include <lazye/backends/opengl/opengluniformhelper.h>
#include <lazye/backends/opengl/openglvertexshader.h>
#include <lazye/backends/opengl/openglfragmentshader.h>

namespace lazye
{
    class OpenGLProgram final
    {
    public:
        class Instance;

        OpenGLProgram(const OpenGLVertexShader::Instance& vertexShader, const OpenGLFragmentShader::Instance& fragmentShader);
        ~OpenGLProgram();

        OpenGLProgram(const OpenGLProgram& other) = delete;
        OpenGLProgram& operator=(const OpenGLProgram& other) = delete;

        OpenGLProgram(OpenGLProgram&& other);
        OpenGLProgram& operator=(OpenGLProgram&& other);

        /**
         *  Instantiate the current Program, returning an {@link OpenGLProgram::Instance} handle
         *  which binds the program activation and can be used to manipulate it (e.g. by setting
         *  uniforms).
         *
         *  Only one program at a time can be Instantiated (otherwise each Instance would override
         *  the previous). Trying to instantiate multiple programs or the same program multiple
         *  times is illegal.
         */
        [[nodiscard]]
        Instance Instantiate() const;

        class Instance final
        {
        public:
            ~Instance();

            Instance(const Instance& other) = delete;
            Instance& operator=(Instance&& other) = delete;

            template<typename Type, typename... Types>
            void SetUniform(const std::string& name, Type&& value, Types&&... other)
            {
                OpenGLUniformHelper::SetUniform(GetUniformLocationFromName(name), value, std::forward<Types>(other)...);
            }

        private:
            friend class OpenGLProgram;
            
            static bool ms_ProgramUsageFlag;

            GLuint m_OwnerProgramID = 0;

            Instance(const OpenGLProgram* owner);
            GLint GetUniformLocationFromName(const std::string& name);
        };

    private:
        friend class Instance;

        GLuint m_ProgramID = 0;
    };
}