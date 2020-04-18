#pragma once
#include <lazye/lazye.h>

#include <memory>
#include <string>

namespace lazye
{
    class Window;
    class Sprite;

    class lazyedll GraphicsFactory
    {
    public:
        static GraphicsFactory& GetInstance();

        virtual std::unique_ptr<Window> CreateWindow() const = 0;
        virtual std::unique_ptr<Sprite> CreateSprite(const std::string& spritePath) const = 0;

    protected:
        GraphicsFactory() = default;
    };
}