#include <lazye/backends/sdl/sdlsprite.h>

#include <lazye/math/transform.h>

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

    void SDLSprite::SetTransform(const Transform& transform)
    {
        m_Position = Vector2f(transform.GetPosition()[0], transform.GetPosition()[1]);
    }
}