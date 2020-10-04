#pragma once
#include <lke/lke.h>

#include <lke/core/component.h>
#include <lke/graphics/renderingcontext.h>

#include <memory>

namespace lke
{
	class Entity;

	class lkedll RenderingComponent : public Component
	{
	public:
		void Update(float dt) override;
		
	private:
		virtual void Render(RenderingContext& context) = 0;
	};
}