#pragma once
#include <lazye/graphics/window.h>
#include <lazye/graphics/renderingcontext.h>

#include <SFML/Graphics/RenderWindow.hpp>

namespace lazye
{
    /**
     * A Window and RenderingContext based on the SFML RenderWindow class
     */
    class SFMLRenderingWindow : public Window, public RenderingContext
    {
    public:
        SFMLRenderingWindow();
        virtual ~SFMLRenderingWindow();

        virtual bool IsOpen() const override;

        virtual void SetTitle(const std::string& title) override;
        virtual void Resize(Size size) override;
        virtual void SetMode(Mode mode) override;
        virtual void Display() override;
        virtual void Close() override;

        virtual RenderingContext& GetRenderingContext() override { return *this; };

        virtual void Clear() override;
        virtual void Render(const Sprite& sprite) override;

    private:
        static sf::Uint32 GetSFMLStyleFromMode(Mode mode);

        void ReCreateRenderWindow();
        void ExecuteDrawCalls();
        void ProcessEvents();

        Size m_Size;
        std::string m_Title;
        Mode m_Mode;

        sf::RenderWindow m_RenderWindow;
    };
}