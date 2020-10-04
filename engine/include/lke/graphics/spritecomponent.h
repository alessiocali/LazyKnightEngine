#pragma once
#include <lke/lke.h>

#include <lke/graphics/spritecomponent.h>
#include <lke/graphics/renderingcomponent.h>

#include <string>
#include <memory>

namespace lke
{
	class lkedll SpriteComponent : public RenderingComponent
	{
	public:
		SpriteComponent(const std::string& spritePath);
		~SpriteComponent();

	private:
		std::unique_ptr<Sprite> m_Sprite;

		void Render(RenderingContext& context) override;
	};
}