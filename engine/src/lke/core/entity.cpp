#include <lke/core/entity.h>

#include <lke/core/component.h>

namespace lke
{
	void Entity::Update(float dt)
	{
		m_Transform.UpdateMatrix();

		for (auto& component : m_Components)
		{
			component->Update(dt);
		}
	}
}