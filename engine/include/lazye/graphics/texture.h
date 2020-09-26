#pragma once

#include <cstddef>
#include <memory>

namespace lazye
{
    enum class TextureType
    {
        Invalid,
        Albedo
    };

    enum class ColorSpace
    {
        RGB,
        RGBA
    };

    class Texture
    {
    public:
        struct InitInfo
        {
            TextureType         Type;
            ColorSpace          TargetSpace;
            ColorSpace          SourceSpace;
            unsigned int        Width;
            unsigned int        Height;
            const std::byte*    Data;
        };

        virtual ~Texture() = default;

        virtual void Init(const InitInfo& info) = 0;
    };
}