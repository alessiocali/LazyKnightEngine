#include <lazye/backends/sdl/opengl/sdlglgraphicsfactory.h>

#include <lazye/backends/sdl/opengl/sdlglwindow.h>
#include <lazye/backends/sdl/opengl/sdlglsprite.h>

namespace lazye
{
    std::unique_ptr<Window> SDLGLGraphicsFactory::CreateWindow() const
    {
        return std::make_unique<SDLGLWindow>();
    }

    std::unique_ptr<Sprite> SDLGLGraphicsFactory::CreateSprite(const std::string& spritePath) const
    {
        return std::make_unique<SDLGLSprite>(spritePath);
    }
}