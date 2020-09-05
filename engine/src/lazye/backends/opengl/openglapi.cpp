#include <lazye/backends/opengl/openglapi.h>

namespace lazye
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