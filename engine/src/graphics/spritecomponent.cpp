#include <lazye/graphics/spritecomponent.h>

#include <lazye/logger.h>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace lazye
{
	SpriteComponent::SpriteComponent(std::string spritePath, std::shared_ptr<RenderingContext> context)
	: RenderingComponent(context)
	{
		LoadSprite(spritePath);
	}

	SpriteComponent::~SpriteComponent() = default;

	void SpriteComponent::Render(float, RenderingContext& context)
	{
		context.Render(*this);
	}

	void SpriteComponent::LoadSprite(std::string spritePath)
	{
		m_Impl = std::make_unique<sf::Sprite>();
		sf::Texture spriteTexture;
		
		if (spriteTexture.loadFromFile(spritePath))
		{
			Log(LogLevel::Error, "Cannot load sprite:");
			Log(LogLevel::Error, spritePath);
			return;
		}

		m_Impl->setTexture(spriteTexture);
	}
}