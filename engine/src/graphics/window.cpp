#include <lazye/graphics/window.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/WindowStyle.hpp>

namespace lazye
{
	sf::Uint32 GetSFMLStyleFromMode(Window::Mode mode)
	{
		if (mode == Window::Mode::Fullscreen)
		{
			return sf::Style::Fullscreen;
		}
		else
		{
			return sf::Style::Default;
		}
	}

    Window::Window(const std::string& title, std::uint16_t width, std::uint32_t height, Mode mode)
    {
        m_Impl = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height, 32), title, GetSFMLStyleFromMode(mode));
    }

	Window::~Window() = default;

    void Window::RenderLoop()
    {
        while (m_Impl->isOpen())
        {
			PollEvents();
			m_Impl->display();
        }
    }

	void Window::PollEvents()
	{
		sf::Event windowEvent;
		while (m_Impl->pollEvent(windowEvent))
		{
			HandleSFMLEvent(windowEvent);
		}
	}

	void Window::HandleSFMLEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::Closed)
		{
			m_Impl->close();
		}
	}
}