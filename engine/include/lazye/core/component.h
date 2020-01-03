#pragma once
#include <lazye/lazye.h>

namespace lazye
{
	/**
	 * A part of an Entity that can be updated
	 */
	class lazyedll Component
	{
	public:
		virtual ~Component() = default;

		virtual void Update(float dt) = 0;
	};
}