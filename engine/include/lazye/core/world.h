#pragma once
#include <lazye/lazye.h>

#include <vector>
#include <memory>

namespace lazye
{
    class Window;
    class Entity;
    class RenderingContext;

    /**
     * @brief A set of Entities that run at the same time
     */
    class lazyedll World
    {
    public:
        static World& GetInstance();

        ~World();

        World(const World& world) = delete;
        World& operator=(const World& world) = delete;

        void SetWindow(std::unique_ptr<Window>& window);
        RenderingContext& GetRenderingContext();

        std::weak_ptr<Entity> CreateEntity();

        void Play();
        bool IsAlive() const;
        void Update(float dt);

    private:
        World() = default;

        std::unique_ptr<Window> m_Window = nullptr;
        std::vector<std::shared_ptr<Entity>> m_Entities;
    };
}