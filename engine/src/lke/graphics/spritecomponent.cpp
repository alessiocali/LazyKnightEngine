#include <lke/graphics/spritecomponent.h>

#include <lke/core/entity.h>

#include <lke/graphics/graphicsfactory.h>
#include <lke/graphics/sprite.h>

namespace lke
{
	SpriteComponent::SpriteComponent(const std::string& spritePath)
    {
		m_Sprite = std::make_unique<Sprite>(spritePath);
    }

	SpriteComponent::~SpriteComponent() = default;

	void SpriteComponent::Render(RenderingContext& context)
	{
		if (m_Sprite != nullptr)
		{
			const auto [view, projection] = context.GetViewProjectionMatrices();
			m_Sprite->Draw(GetOwner()->GetTransform().GetMatrix(), view, projection);
		}
	}
}