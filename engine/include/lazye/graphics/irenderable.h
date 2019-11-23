#pragma once

namespace lazye
{
	class RenderingContext;

	/**
	 * Interface for objects that can be rendered via RenderingContext.
	 */
	class IRenderable
	{
	public:
		virtual void Render(float dt, RenderingContext& context) = 0;
	};
}