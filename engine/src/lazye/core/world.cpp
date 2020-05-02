#include <lazye/core/world.h>

#include <lazye/core/entity.h>

#include <lazye/graphics/window.h>
#include <lazye/graphics/renderingcontext.h>
#include <lazye/graphics/graphicsfactory.h>

namespace lazye
{
    World& World::GetInstance()
    {
        static World world;
        return world;
    }

    World::World()
        : m_Window(GraphicsFactory::GetInstance().CreateWindow())
    { }

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
        m_Window->Close();
        m_Window = std::move(window); 
    }

    RenderingContext& World::GetRenderingContext()
    {
        return m_Window->GetRenderingContext();
    }
}