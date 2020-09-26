#pragma once
#include <lazye/lazye.h>

#include <memory>

namespace lazye
{
    enum class TextureType;

    class Texture;

    class lazyedll TextureLoader
    {
    public:
        ~TextureLoader() = default;

        static TextureLoader& GetInstance();

        virtual std::unique_ptr<Texture> LoadTexture(const TextureType type, const std::string& path) const = 0;

    protected:
        TextureLoader() = default;
    };
}