#include <lazye/backends/sdl/sdlgraphicsfactory.h>

#include <lazye/graphics/sprite.h>

#include <lazye/backends/sdl/sdlwindow.h>
#include <lazye/backends/sdl/sdlsprite.h>

namespace lazye
{
    std::unique_ptr<Window> SDLGraphicsFactory::CreateWindow() const
    {
        return std::make_unique<SDLWindow>();
    }

    std::unique_ptr<Sprite> SDLGraphicsFactory::CreateSprite(const std::string& spritePath) const
    {
        return std::make_unique<SDLSprite>(spritePath);
    }
}