#pragma once

#include <glad/glad.h>

namespace lazye
{
    class OpenGLAPI final
    {
    public:
        static OpenGLAPI& GetInstance();

        void Init(GLADloadproc loaderProcess);

    private:
        OpenGLAPI() = default;
    };
}