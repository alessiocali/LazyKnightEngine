#pragma once
#include <lazye/assets/textureloader.h>

namespace lazye
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