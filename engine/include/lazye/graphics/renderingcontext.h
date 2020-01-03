#pragma once
#include <lazye/lazye.h>

#include <lazye/graphics/irenderable.h>

#include <memory>

namespace lazye
{
	class SpriteComponent;
	class Window;

	class lazyedll RenderingContext
	{
	public:
		RenderingContext(std::weak_ptr<Window> window) : m_Window(window)
		{ }

		void Render(SpriteComponent& spriteComponent);

	private:
		std::weak_ptr<Window> m_Window;
	};
}