#pragma once
#include <lazye/lazye.h>

#include <lazye/graphics/graphicsfactory.h>

namespace lazye
{
    class SDLGraphicsFactory : public GraphicsFactory
    {
    public:
        std::unique_ptr<Window> CreateWindow() const override;
        std::unique_ptr<Sprite> CreateSprite(const std::string& spritePath) const override;

    private:
        friend GraphicsFactory& GraphicsFactory::GetInstance();
        SDLGraphicsFactory() = default;
    };
}