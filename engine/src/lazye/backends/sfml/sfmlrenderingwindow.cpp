#include <lazye/backends/sfml/sfmlrenderingwindow.h>

#include <lazye/backends/sfml/sfmlsprite.h>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace lazye
{
    SFMLRenderingWindow::SFMLRenderingWindow()
        : m_Size(DEFAULT_WINDOW_SIZE), m_Title(DEFAULT_WINDOW_TITLE), m_Mode(DEFAULT_WINDOW_MODE)
    {
        ReCreateRenderWindow();
    }

    SFMLRenderingWindow::~SFMLRenderingWindow()
    {
        if (IsOpen())
        {
            Close();
        }
    }

    bool SFMLRenderingWindow::IsOpen() const
    {
        return m_RenderWindow.isOpen();
    }

    void SFMLRenderingWindow::SetTitle(const std::string& title)
    {
        m_Title = title;
        m_RenderWindow.setTitle(title);
    }

    void SFMLRenderingWindow::Resize(Size size)
    {
        m_Size = size;
        m_RenderWindow.setSize(sf::Vector2u(size.width, size.height));
    }

    void SFMLRenderingWindow::SetMode(Mode mode)
    {
        m_Mode = mode;
        ReCreateRenderWindow();
    }

    void SFMLRenderingWindow::Display()
    {
        ProcessEvents();
        m_RenderWindow.display();
    }

    void SFMLRenderingWindow::Close()
    {
        m_RenderWindow.close();
    }

    void SFMLRenderingWindow::Clear()
    {
        m_RenderWindow.clear();
    }

    void SFMLRenderingWindow::Render(const Sprite& sprite)
    {
        Assert(dynamic_cast<const SFMLSprite*>(&sprite));
        const SFMLSprite& sfmlSprite = static_cast<const SFMLSprite&>(sprite);

        m_RenderWindow.draw(sfmlSprite.GetSFMLSprite());
    }

    void SFMLRenderingWindow::ReCreateRenderWindow()
    {
        m_RenderWindow.create(sf::VideoMode(m_Size.width, m_Size.height), m_Title, GetSFMLStyleFromMode(m_Mode));
    }

    void SFMLRenderingWindow::ProcessEvents()
    {
        sf::Event event;
        while (m_RenderWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                Close();
                return;
            }
        }
    }

    void SFMLRenderingWindow::ExecuteDrawCalls()
    {

    }

    sf::Uint32 SFMLRenderingWindow::GetSFMLStyleFromMode(Mode mode)
    {
        switch (mode)
        {
        default:
        case Mode::Windowed:
            return sf::Style::Default;
        case Mode::Fullscreen:
            return sf::Style::Fullscreen;
        }
    }
}