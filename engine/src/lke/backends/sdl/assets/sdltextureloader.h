#pragma once
#include <lke/assets/textureloader.h>

namespace lke
{
    class SDLTextureLoader : public TextureLoader
    {
    public:
        std::unique_ptr<Texture> LoadTexture(const TextureType type, const std::string& path) const override;

    private:
        friend TextureLoader& TextureLoader::GetInstance();

        SDLTextureLoader() = default;
    };
}