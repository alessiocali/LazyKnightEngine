#pragma once

#include <lazye/graphics/sprite.h>

namespace lazye
{
    class OpenGLSprite;

    class SDLGLSprite final : public Sprite
    {
    public:
        SDLGLSprite(const std::string& path);
        ~SDLGLSprite();

        void SetPosition(const Vector2f& position) override;
        void SetRotation(Radians rotation) override;

        void Draw() const;

    private:
        std::unique_ptr<OpenGLSprite> m_GLSprite;
    };
}