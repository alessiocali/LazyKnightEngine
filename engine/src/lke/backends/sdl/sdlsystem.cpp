#include <lke/backends/sdl/sdlsystem.h>

#include <lke/backends/sdl/sdlheader.h>

#include <SDL_image.h>

namespace lke
{
    SDLSubSystemHandle SDLSystem::MakeHandleForSubsystem(Uint32 subsystem) const
    {
        return SDLSubSystemHandle(subsystem);
    }

    SDLSubSystemHandle::SDLSubSystemHandle(Uint32 subsystemFlag)
        : m_SubSystemFlag(subsystemFlag)
    {
        SDL_InitSubSystem(m_SubSystemFlag);
    }

    SDLSubSystemHandle::~SDLSubSystemHandle()
    {
        if (IsValid())
        {
            SDL_QuitSubSystem(m_SubSystemFlag);
        }
    }

    SDLSubSystemHandle::SDLSubSystemHandle(SDLSubSystemHandle&& other)
    {
        m_SubSystemFlag = other.m_SubSystemFlag;
        other.Invalidate();
    }

    SDLSubSystemHandle& SDLSubSystemHandle::operator=(SDLSubSystemHandle&& other)
    {
        if (this == &other)
        {
            return *this;
        }

        m_SubSystemFlag = other.m_SubSystemFlag;
        other.Invalidate();

        return *this;
    }

    void SDLSubSystemHandle::Invalidate()
    {
        m_SubSystemFlag = INVALID_SUBSYSTEM;
    }

    bool SDLSubSystemHandle::IsValid() const
    {
        return m_SubSystemFlag != INVALID_SUBSYSTEM;
    }


    SDLSystem::SDLSystem()
    {
        static constexpr Uint32 IMG_FORMATS_TO_LOAD = IMG_INIT_JPG | IMG_INIT_PNG;

        SDL_SetMainReady();
        SDL_Init(0);
        IMG_Init(IMG_FORMATS_TO_LOAD);
    }

    SDLSystem::~SDLSystem()
    {
        IMG_Quit();
        SDL_Quit();
    }

    SDLSystem& SDLSystem::GetInstance()
    {
        static SDLSystem s_Instance;
        return s_Instance;
    }
}