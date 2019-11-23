#pragma once

#include <lazye/core/component.h>
#include <lazye/graphics/irenderable.h>
#include <lazye/graphics/renderingcontext.h>

#include <memory>

namespace lazye
{
	class RenderingComponent : public Component, public IRenderable
	{
	public:
		RenderingComponent(std::shared_ptr<RenderingContext> context) : m_Context(context)
		{ }

		void Update(float dt) override;

	private:
		std::shared_ptr<RenderingContext> m_Context;
	};
}