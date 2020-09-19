#include <lazye/core/entity.h>

#include <lazye/core/component.h>

namespace lazye
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