#pragma once
#include <lazye/lazye.h>

#include <memory>

namespace lazye
{
	class Sprite;

	class lazyedll RenderingContext
	{
	public:
		virtual void Clear() = 0;

		virtual void Render(const Sprite& sprite) = 0;
	};
}