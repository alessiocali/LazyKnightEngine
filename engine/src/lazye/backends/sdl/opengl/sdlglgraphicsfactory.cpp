#include <lazye/backends/sdl/opengl/sdlglgraphicsfactory.h>

#include <lazye/backends/sdl/opengl/sdlglwindow.h>
#include <lazye/backends/sdl/opengl/sdlglsprite.h>
#include <lazye/backends/opengl/openglmesh.h>

namespace lazye
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

    std::unique_ptr<Sprite> SDLGLGraphicsFactory::CreateSprite(const std::string& spritePath) const
    {
        return std::make_unique<SDLGLSprite>(spritePath);
    }

    std::unique_ptr<Mesh> SDLGLGraphicsFactory::CreateMesh(std::size_t vertexCount) const
    {
        return std::make_unique<OpenGLMesh>(vertexCount);
    }

}