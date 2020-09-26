#include <lazye/graphics/spritecomponent.h>

#include <lazye/core/entity.h>

#include <lazye/graphics/graphicsfactory.h>
#include <lazye/graphics/sprite.h>

namespace lazye
{
	SpriteComponent::SpriteComponent(const std::string& spritePath)
    {
		m_Sprite = std::make_unique<Sprite>(spritePath);
    }

	SpriteComponent::~SpriteComponent() = default;

	void SpriteComponent::Render(float, RenderingContext& context)
	{
		context.Render(*m_Sprite);
	}

	void SpriteComponent::UpdateOwnerTransform()
	{
		m_Sprite->SetTransform(GetOwner()->GetTransform());
	}
}