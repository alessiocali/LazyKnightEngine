#pragma once

#include <lazye/graphics/sprite.h>

#include <lazye/backends/sdl/sdlhelper.h>

namespace lazye
{
    class SDLSprite : public Sprite
    {
    public:
        SDLSprite(const std::string& spritePath)
            : m_SourceFilePath(spritePath)
        { };

        bool IsLoaded() const { return m_Texture != nullptr; }
        void Load(SDL_Renderer* renderer);

        SDL_Texture* GetTexture() const;

        const Vector2f& GetPosition() const;

        void SetTransform(const Transform& transform) override;
        
    private:
        SDLHelper::SDL_TexturePtr m_Texture;
        std::string m_SourceFilePath;

        Vector2f m_Position = { 0.f, 0.f };
    };
}