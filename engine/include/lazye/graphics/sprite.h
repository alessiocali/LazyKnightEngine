#pragma once
#include <lazye/lazye.h>

#include <lazye/math/vectors.h>

namespace lazye
{
    class Transform;

    class lazyedll Sprite
    {
    public:
        virtual ~Sprite() = default;

        virtual void SetTransform(const Transform& transform) = 0;
    };
}