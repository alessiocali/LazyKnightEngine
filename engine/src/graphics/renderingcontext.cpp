#include <lazye/graphics/renderingcontext.h>

#include <lazye/graphics/window.h>
#include <lazye/graphics/spritecomponent.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace lazye
{
	void RenderingContext::Render(SpriteComponent& spriteComponent)
	{
		if (auto window = m_Window.lock())
		{
			window->m_Impl->draw(*spriteComponent.m_Impl);
		}
	}
}