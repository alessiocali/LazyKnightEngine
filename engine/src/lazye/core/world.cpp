#include <lazye/core/world.h>

#include <chrono>
#include <thread>

#include <lazye/core/entity.h>

#include <lazye/graphics/window.h>
#include <lazye/graphics/renderingcontext.h>
#include <lazye/graphics/graphicsfactory.h>

namespace lazye
{
    static constexpr std::uint16_t FRAMES_PER_SECOND = 60;
    static constexpr auto TIME_PER_FRAME = std::chrono::duration<float>(1 / static_cast<float>(FRAMES_PER_SECOND));

    World& World::GetInstance()
    {
        static World world;
        return world;
    }

    World::~World() = default;

    std::weak_ptr<Entity> World::CreateEntity()
    {
        std::shared_ptr<Entity>& newEntity = m_Entities.emplace_back(std::make_shared<Entity>());
        newEntity->SetWorld(this);
        return newEntity;
    }

    void World::Play()
    {
        while (IsAlive())
        {
            Update(0.f);
            std::this_thread::sleep_for(TIME_PER_FRAME);
        }
    }

    bool World::IsAlive() const
    {
        return m_Window->IsOpen();
    }

    void World::Update(float dt)
    {
        m_Window->GetRenderingContext().Clear();

        for (auto& entity : m_Entities)
        {
            entity->Update(dt);
        }

        m_Window->Display();
    }

    void World::SetWindow(std::unique_ptr<Window>& window)
    {
        if (m_Window != nullptr && m_Window->IsOpen())
        {
            m_Window->Close();
        }

        m_Window = std::move(window); 
    }

    RenderingContext& World::GetRenderingContext()
    {
        return m_Window->GetRenderingContext();
    }
}