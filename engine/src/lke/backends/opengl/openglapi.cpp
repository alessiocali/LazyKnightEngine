#include <lke/backends/opengl/openglapi.h>

namespace lke
{
    OpenGLAPI& OpenGLAPI::GetInstance()
    {
        static OpenGLAPI s_Instance;
        return s_Instance;
    }

    void OpenGLAPI::Init(GLADloadproc loaderProcess)
    {
        Assert(gladLoadGLLoader(loaderProcess));
    }
}