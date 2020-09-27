#pragma once
#include <lke/lke.h>

#include <memory>

namespace lke
{
    enum class TextureType;

    class Texture;

    class lkedll TextureLoader
    {
    public:
        ~TextureLoader() = default;

        static TextureLoader& GetInstance();

        virtual std::unique_ptr<Texture> LoadTexture(const TextureType type, const std::string& path) const = 0;

    protected:
        TextureLoader() = default;
    };
}