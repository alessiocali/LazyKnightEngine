#include <lazye/backends/sfml/sfmlgraphicsfactory.h>

#include <lazye/backends/sfml/sfmlrenderingwindow.h>
#include <lazye/backends/sfml/sfmlsprite.h>

namespace lazye
{
    std::unique_ptr<Window> SFMLGraphicsFactory::CreateWindow() const
    {
        return std::make_unique<SFMLRenderingWindow>();
    }

    std::unique_ptr<Sprite> SFMLGraphicsFactory::CreateSprite(const std::string& spritePath) const
    {
        return std::make_unique<SFMLSprite>(spritePath);
    }
}