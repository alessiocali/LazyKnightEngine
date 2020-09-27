#pragma once
#include <lazye/lazye.h>

#include <lazye/core/component.h>
#include <lazye/graphics/renderingcontext.h>

#include <memory>

namespace lazye
{
	class Entity;

	class lazyedll RenderingComponent : public Component
	{
	public:
		void Update(float dt) override;
		
	private:
		virtual void UpdateOwnerTransform() = 0;
		virtual void Render(Seconds dt, RenderingContext& context) = 0;
	};
}