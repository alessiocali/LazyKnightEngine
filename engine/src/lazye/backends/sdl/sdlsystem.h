#pragma once

#include <SDL_stdinc.h>

namespace lazye
{
    class SDLSubSystemHandle final
    {
    public:
        friend class SDLSystem;

        ~SDLSubSystemHandle();

        SDLSubSystemHandle(const SDLSubSystemHandle& other) = delete;
        SDLSubSystemHandle& operator=(const SDLSubSystemHandle& other) = delete;

        SDLSubSystemHandle(SDLSubSystemHandle&& other);
        SDLSubSystemHandle& operator=(SDLSubSystemHandle&& other);

    private:
        static constexpr Uint32 INVALID_SUBSYSTEM = 0;

        Uint32 m_SubSystemFlag;

        SDLSubSystemHandle(Uint32 subSystemFlag);
        void Invalidate();
        bool IsValid() const;
    };

    class SDLSystem final
    {
    public:
        ~SDLSystem();

        static SDLSystem& GetInstance();

        SDLSubSystemHandle MakeHandleForSubsystem(Uint32 subsystem) const;

    private:
        SDLSystem();
    };

    template<Uint32 SubsystemType>
    class ISDLSubSystemUser
    {
    public:
        virtual ~ISDLSubSystemUser() = default;

        ISDLSubSystemUser()
            : m_Handle(SDLSystem::GetInstance().MakeHandleForSubsystem(SubsystemType))
        { }

    private:
        SDLSubSystemHandle m_Handle;
    };
}