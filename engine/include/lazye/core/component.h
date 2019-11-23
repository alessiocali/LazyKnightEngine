#pragma once

namespace lazye
{
	/**
	 * A part of an Entity that can be updated
	 */
	class Component
	{
	public:
		virtual ~Component() = default;

		virtual void Update(float dt) = 0;
	};
}