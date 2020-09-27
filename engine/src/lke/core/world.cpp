#include <lke/core/world.h>

#include <chrono>
#include <thread>

#include <lke/core/entity.h>

#include <lke/graphics/window.h>
#include <lke/graphics/renderingcontext.h>
#include <lke/graphics/graphicsfactory.h>

namespace lke
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
            m_LastFrameIstant = std::chrono::steady_clock::now();

            Update(m_CurrentDt.count());
            std::this_thread::sleep_for(TIME_PER_FRAME);
            
            m_CurrentDt = std::chrono::steady_clock::now() - m_LastFrameIstant;
        }
    }

    bool World::IsAlive() const
    {
        return m_Window->IsOpen();
    }

    void World::Update(float dt)
    {
        m_Window->GetRenderingContext().Clear();
        m_Window->GetRenderingContext().UpdateCamera();

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