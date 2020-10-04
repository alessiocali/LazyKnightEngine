#pragma once
#include <lke/lke.h>

namespace lke
{
	class Entity;

	/**
	 * @brief A part of an Entity that can be updated
	 */
	class lkedll Component
	{
	public:
		virtual ~Component() = default;

		inline void SetOwner(Entity* owner) { m_Owner = owner; }
		inline Entity* GetOwner() const { return m_Owner; }

		virtual void Update(float dt) = 0;

	private:
		Entity* m_Owner;
	};
}