#include <lke/backends/sdl/opengl/sdlglgraphicsfactory.h>

#include <lke/backends/sdl/opengl/sdlglwindow.h>
#include <lke/backends/opengl/openglmesh.h>
#include <lke/backends/opengl/opengltexture.h>

namespace lke
{
    const Matrix44f& SDLGLGraphicsFactory::GetCameraCorrectionMatrix() const
    {
        static bool s_Init = false;
        static Matrix44f s_CameraCorrectionMatrix;

        if (!s_Init)
        {
            SetToRotationMatrix(s_CameraCorrectionMatrix, Quaternion::FromAngleAxis({ DegToRad(90.f), Vector3f::GetAxisI() }));
            s_Init = true;
        }

        return s_CameraCorrectionMatrix;
    }

    std::unique_ptr<Window> SDLGLGraphicsFactory::CreateWindow() const
    {
        return std::make_unique<SDLGLWindow>();
    }

    std::unique_ptr<Mesh> SDLGLGraphicsFactory::CreateMesh(std::size_t vertexCount) const
    {
        return std::make_unique<OpenGLMesh>(vertexCount);
    }

    std::unique_ptr<Texture> SDLGLGraphicsFactory::CreateTexture() const
    {
        return std::make_unique<OpenGLTexture>();
    }
}