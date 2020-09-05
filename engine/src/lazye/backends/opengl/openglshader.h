#pragma once

#include <glad/glad.h>

namespace lazye
{
    class OpenGLShader
    {
    public:
        class Instance;

        virtual ~OpenGLShader() = default;

        Instance Instantiate() const { return Instance(this); }

        class Instance
        {
        public:
            ~Instance();

            Instance(Instance& other) = delete;
            Instance operator=(Instance& other) = delete;

            inline GLuint GetShaderID() const { return m_ShaderID; }

        private:
            friend class OpenGLShader;

            Instance(const OpenGLShader* owner);

            GLuint m_ShaderID = 0;
        };

    private:
        friend class Instance;

        virtual const char* const* GetSource() const = 0;
        virtual GLenum GetShaderType() const = 0;
    };
}