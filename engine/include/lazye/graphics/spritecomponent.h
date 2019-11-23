#pragma once

#include <lazye/graphics/renderingcomponent.h>

#include <string>
#include <memory>

namespace sf
{
	class Sprite;
}

namespace lazye
{
	class SpriteComponent : public RenderingComponent
	{
		friend void RenderingContext::Render(SpriteComponent&);

	public:
		SpriteComponent(std::string spritePath, std::shared_ptr<RenderingContext> context);
		virtual ~SpriteComponent() override;

	private:
		void Render(float dt, RenderingContext& context) override;
		void LoadSprite(std::string spritePath);

		std::unique_ptr<sf::Sprite> m_Impl;
	};
}