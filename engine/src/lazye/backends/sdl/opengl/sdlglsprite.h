#pragma once

#include <lazye/graphics/sprite.h>

#include <lazye/backends/opengl/openglsprite.h>

namespace lazye
{
    class SDLGLSprite final : public Sprite
    {
    public:
        SDLGLSprite(const std::string& path);

        void SetPosition(const Vector2f& position) override;
        void SetRotation(Radians rotation) override;

        inline void Draw() const { m_GLSprite.Draw(); }

    private:
        OpenGLSprite m_GLSprite;
    };
}