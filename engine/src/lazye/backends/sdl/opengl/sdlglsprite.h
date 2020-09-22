#pragma once

#include <lazye/math/transform.h>

#include <lazye/graphics/sprite.h>

namespace lazye
{
    class OpenGLSprite;

    class SDLGLSprite final : public Sprite
    {
    public:
        SDLGLSprite(const std::string& path);
        ~SDLGLSprite();

        // Yes I'm aware this is a sort of unnecessary copy...
        // But I'm kinda limited by the interface, I should probably
        // change it
        inline void SetTransform(const Transform& transform) override { m_Matrix = transform.GetMatrix(); };
        
        void Draw(const Matrix44f& view, const Matrix44f& projection) const;

    private:
        std::unique_ptr<OpenGLSprite> m_GLSprite;

        Matrix44f m_Matrix;
    };
}