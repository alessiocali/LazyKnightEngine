#pragma once

#include <vector>
#include <memory>

namespace lazye
{
	class Component;

	/**
	 * Something that has a presence in the world.
	 */
	class lazyedll Entity final
	{
		Entity(const Entity& other) = delete;
		Entity& operator=(const Entity& other) = delete;

		Entity(Entity&& other) = default;
		Entity& operator=(Entity&& other) = default;

		void Update(float dt);

		template<class ComponentType, class... Args>
		void AddComponent(Args&&... args)
		{
			m_Components.push_back(
				std::make_unique<ComponentType>(std::forward(args))
			);
		}

	private:
		using ComponentPtr = std::unique_ptr<Component>;

		std::vector<ComponentPtr> m_Components;
	};
}