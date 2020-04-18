#pragma once
#include <lazye/lazye.h>

#include <lazye/math/vectors.h>

namespace lazye
{
    class lazyedll Sprite
    {
    public:
        virtual ~Sprite() = default;

        virtual void SetPosition(const Vector2f& position) = 0;
        virtual void SetRotation(Radians rotation) = 0;
    };
}