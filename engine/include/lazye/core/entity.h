#pragma once

#include <vector>
#include <memory>

#include <lazye/core/component.h>
#include <lazye/math/transform.h>

namespace lazye
{
	class World;

	/**
	 * @brief Something that has a presence in the world.
	 */
	class lazyedll Entity final
	{
    public:
		Entity() = default;

		Entity(const Entity& other) = delete;
		Entity& operator=(const Entity& other) = delete;

		inline void SetWorld(World* world) { m_World = world; }
		inline World* GetWorld() const { return m_World; }

		inline const Vector3f& GetPosition() const { return GetTransform().GetPosition(); }
		inline const Vector3f& GetScaling() const { return GetTransform().GetScaling(); }
		inline const Quaternion& GetRotation() const { return GetTransform().GetRotation(); }
		inline const Transform& GetTransform() const { return m_Transform; }

		inline void SetPosition(const Vector3f& position) { m_Transform.SetPosition(position); }
		inline void SetScaling(const Vector3f& scaling) { m_Transform.SetScaling(scaling); }
		inline void SetRotation(const Quaternion& rotation) { m_Transform.SetRotation(rotation); }
		inline void SetTransform(const Transform& transform) { m_Transform = transform; }

		void Update(float dt);

		template<class ComponentType, class... Args>
		void AddComponent(Args&&... args)
		{
			std::unique_ptr<Component>& newComponent = m_Components.emplace_back(
				std::make_unique<ComponentType>(std::forward<Args>(args)...)
			);

			newComponent->SetOwner(this);
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
		World* m_World;
		std::vector<std::unique_ptr<Component>> m_Components;
		Transform m_Transform;
	};
}