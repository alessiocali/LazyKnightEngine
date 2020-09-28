#include <lke/backends/sdl/assets/sdltextureloader.h>

#include <SDL2/SDL_image.h>

#include <lke/backends/sdl/sdlhelper.h>
#include <lke/graphics/graphicsfactory.h>
#include <lke/graphics/texture.h>

namespace lke
{
    ColorSpace GetColorSpaceFromSDLFormat(Uint32 format)
    {
        return SDL_ISPIXELFORMAT_ALPHA(format) ? ColorSpace::RGBA : ColorSpace::RGB;
    }

    /**
     *  Unfortunately SDL's IMG_Load won't allow us to flip the data on load,
     *  so we've got to do it manually.
     */
    void FlipSurfaceVertically(SDLHelper::SDL_SurfacePtr& source)
    {
        // Many thanks to this sample
        // http://lazyfoo.net/SDL_tutorials/lesson31/index.php

        Uint32 colorKey = 0;
        const bool hasColorKey = SDL_GetColorKey(source.get(), &colorKey) > 0;
        const Uint32 surfaceAlphaMask = hasColorKey ? 0 : source->format->Amask;
        SDLHelper::SDL_SurfacePtr flipped(
            SDL_CreateRGBSurface(
                SDL_SWSURFACE,
                source->w,
                source->h,
                source->format->BitsPerPixel,
                source->format->Rmask,
                source->format->Gmask,
                source->format->Bmask,
                surfaceAlphaMask
            )
        );

        {
            SDLHelper::SDL_SurfaceLocker locker(source.get());

            auto copyRow = [](SDL_Surface* source, SDL_Surface* target, std::size_t srcRow, std::size_t tgtRow)
            {
                const std::size_t srcH = static_cast<std::size_t>(source->h);
                const std::size_t srcW = static_cast<std::size_t>(source->w);
                const std::size_t tgtH = static_cast<std::size_t>(target->h);
                const std::size_t tgtW = static_cast<std::size_t>(target->w);

                Assert((srcRow < srcH) && (tgtRow < tgtH));
                Assert(srcW == tgtW);
                Uint32* sourceRowPtr = static_cast<Uint32*>(source->pixels) + (srcRow * srcW);
                Uint32* targetRowPtr = static_cast<Uint32*>(target->pixels) + (tgtRow * tgtW);

                std::memcpy(targetRowPtr, sourceRowPtr, srcW * sizeof(Uint32));
            };

            std::size_t srcCol = 0;
            std::size_t tgtCol = flipped->h - 1;
            const std::size_t srcH = static_cast<std::size_t>(source->h);
            while ((srcCol < srcH) && (tgtCol > 0))
            {
                copyRow(source.get(), flipped.get(), srcCol, tgtCol);
                srcCol++;
                tgtCol--;
            }
        }

        if (hasColorKey)
        {
            SDL_SetColorKey(flipped.get(), SDL_TRUE, colorKey);
        }

        source = std::move(flipped);
    }

    std::unique_ptr<Texture> SDLTextureLoader::LoadTexture(const TextureType type, const std::string& path) const
    {
        SDLHelper::SDL_SurfacePtr sdlSurface(IMG_Load(path.c_str()));
        if (sdlSurface == nullptr)
        {
            return nullptr;
        }

        FlipSurfaceVertically(sdlSurface);
        std::unique_ptr<Texture> loadedTexture = GraphicsFactory::GetInstance().CreateTexture();
        
        Texture::InitInfo initInfo;
        initInfo.Type = type;
        initInfo.SourceSpace = GetColorSpaceFromSDLFormat(sdlSurface->format->format);
        initInfo.TargetSpace = initInfo.SourceSpace; // No particular reason for distinguishing the two (yet)
        initInfo.Width = sdlSurface->w;
        initInfo.Height = sdlSurface->h;
        initInfo.Data = static_cast<const std::byte*>(sdlSurface->pixels);

        loadedTexture->Init(initInfo);
        return loadedTexture;
    }
}