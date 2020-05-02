#include <lazye/graphics/spritecomponent.h>

#include <lazye/core/entity.h>

#include <lazye/graphics/graphicsfactory.h>
#include <lazye/graphics/sprite.h>

namespace lazye
{
	SpriteComponent::SpriteComponent(const std::string& spritePath)
	{
		LoadSprite(spritePath);
	}

	SpriteComponent::~SpriteComponent() = default;

	void SpriteComponent::Render(float, RenderingContext& context)
	{
		context.Render(*m_Sprite);
	}

	void SpriteComponent::UpdateOwnerTransform()
	{
		const Vector3f& ownerPosition = GetOwner()->GetPosition();
		Vector2f spritePosition(ownerPosition[0], ownerPosition[1]);
		m_Sprite->SetPosition(spritePosition);
	}

	void SpriteComponent::LoadSprite(const std::string& spritePath)
	{
		m_Sprite = GraphicsFactory::GetInstance().CreateSprite(spritePath);
	}
}