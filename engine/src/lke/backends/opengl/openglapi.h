#pragma once

#include <glad/glad.h>

namespace lke
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