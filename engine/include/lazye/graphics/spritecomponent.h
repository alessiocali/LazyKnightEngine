#pragma once
#include <lazye/lazye.h>

#include <lazye/graphics/spritecomponent.h>
#include <lazye/graphics/renderingcomponent.h>

#include <string>
#include <memory>

namespace lazye
{
	class lazyedll SpriteComponent : public RenderingComponent
	{
	public:
		SpriteComponent(const std::string& spritePath);
		~SpriteComponent();

	private:
		std::unique_ptr<Sprite> m_Sprite;

		void Render(float dt, RenderingContext& context) override;
		void UpdateOwnerTransform() override;

		void LoadSprite(const std::string& spritePath);
	};
}