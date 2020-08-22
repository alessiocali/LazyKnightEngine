#include <lazye/backends/sdl/sdlsprite.h>

#include <SDL_image.h>

namespace lazye
{
    void SDLSprite::Load(SDL_Renderer* renderer)
    {
        m_Texture = SDLHelper::SDL_TexturePtr(IMG_LoadTexture(renderer, m_SourceFilePath.c_str()));
    }

    SDL_Texture* SDLSprite::GetTexture() const
    {
        return m_Texture.get();
    }

    const Vector2f& SDLSprite::GetPosition() const
    {
        return m_Position;
    }

    Radians SDLSprite::GetRotation() const
    {
        return m_Rotation;
    }

    void SDLSprite::SetPosition(const Vector2f& position)
    {
        m_Position = position;
    }

    void SDLSprite::SetRotation(Radians rotation)
    {
        m_Rotation = rotation;
    }
}