#pragma once

#include <memory>
#include <string>

#include <lazye/graphics/renderingcontext.h>
#include <lazye/macros.h>

namespace sf
{
    class RenderWindow;
	class Event;
}

namespace lazye
{
	/**
	 * Sample Window class 
	 */
	class lazyedll Window
	{
		friend RenderingContext;

	public:
		enum class Mode
		{
			Windowed,
			Fullscreen
		};

		Window(const std::string& title, std::uint16_t width = 800, std::uint32_t height = 600, Mode mode = Mode::Windowed);
		~Window();

		/**
		 * Starts an infinite rendering loop which shows the window
		 */
		void RenderLoop();

	private:
		std::unique_ptr<sf::RenderWindow> m_Impl;

		void PollEvents();
		void HandleSFMLEvent(const sf::Event& event);
	};
}