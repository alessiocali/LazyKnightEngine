#pragma once

#include <vector>
#include <memory>

#include <lazye/core/component.h>

namespace lazye
{
	/**
	 * @brief Something that has a presence in the world.
	 */
	class lazyedll Entity final
	{
    public:
		Entity() = default;

		Entity(const Entity& other) = delete;
		Entity& operator=(const Entity& other) = delete;

		const Vector3f& GetPosition() const { return m_GlobalPosition; }

		void Update(float dt);

		template<class ComponentType, class... Args>
		void AddComponent(Args&&... args)
		{
			m_Components.emplace_back(
				std::make_unique<ComponentType>(std::forward<Args>(args)...)
			);
		}

		template<class ComponentType>
		ComponentType* GetComponentOfType() const
		{
			auto componentIt = std::find_if(m_Components.cbegin(), m_Components.cend(),
			[](const std::unique_ptr<Component> component)
			{
				return dynamic_cast<ComponentType*>(component.get()) != nullptr;
			});

			return componentIt != m_Components.cend() ?
				static_cast<ComponentType*>(componentIt->get()) : nullptr;
		}

	private:
		std::vector<std::unique_ptr<Component>> m_Components;
		Vector3f m_GlobalPosition;
	};
}