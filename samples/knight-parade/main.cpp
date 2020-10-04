#include <lke/core/world.h>
#include <lke/core/entity.h>
#include <lke/graphics/graphicsfactory.h>
#include <lke/graphics/window.h>
#include <lke/graphics/camera.h>
#include <lke/graphics/spritecomponent.h>

#include <iostream>
#include <memory>

#include <cassert>

using namespace std;
using namespace lke;

class MarchComponent : public Component
{
public:
    MarchComponent(float marchSpeed, Seconds flipTime, Radians hrzFrequency, float startingX)
        : m_MarchSpeed(marchSpeed), m_FlipTime(flipTime), m_HorizontalFrequency(hrzFrequency), m_StartingX(startingX)
    {
        static float TimeOffset = 0.f;
        m_InternalClock += TimeOffset;
        TimeOffset += 1.f;
    }

    void Update(float dt) override
    {
        m_InternalClock += dt;

        if (m_InternalClock - m_LastTimeFlipped > m_FlipTime && !m_Flipping)
        {
            StartFlipping();
        }
        else if (m_Flipping)
        {
            UpdateFlipping(dt);
        }

        UpdateMarching(dt);
        UpdateHorizontal();
    }
private:
    Seconds m_InternalClock{ 0.f };
    Seconds m_LastTimeFlipped{ 0.f };
    bool m_Flipping{ false };

    const float m_MarchSpeed{ 0.f };
    const float m_FlipTime{ 0.f };
    const float m_HorizontalFrequency{ 0.f };

    Radians m_FlipCounter{ 0.f };
    float m_StartingX;

    void StartFlipping()
    {
        m_Flipping = true;
        GetOwner()->SetRotation(Quaternion::GetIdentity());
        m_FlipCounter = 0.f;
    }

    void UpdateFlipping(Radians dt)
    {
        constexpr Radians FLIP_FREQ = DegToRad(720.f);
        m_FlipCounter += dt * FLIP_FREQ;
        
        if (m_FlipCounter > DegToRad(360.f))
        {
            m_Flipping = false;
            m_FlipCounter = 0.f;
            m_LastTimeFlipped = m_InternalClock;
        }

        GetOwner()->SetRotation(Quaternion::FromAngleAxis({ m_FlipCounter, Vector3f::GetAxisK() }));
    }

    void UpdateMarching(Seconds dt)
    {
        constexpr float Y_LIMIT = 20.f;

        const Vector3f& pos = GetOwner()->GetPosition();
        if (pos[1] > Y_LIMIT)
        {
            GetOwner()->SetPosition(Vector3f{ pos[0], 0.f, pos[2] });
        }

        GetOwner()->SetPosition(GetOwner()->GetPosition() + m_MarchSpeed * dt * Vector3f::GetAxisJ());
    }

    void UpdateHorizontal()
    {
        const Vector3f pos = GetOwner()->GetPosition();
        GetOwner()->SetPosition(Vector3f{ m_StartingX + 0.5f * Sin(m_InternalClock * m_HorizontalFrequency), pos[1], 0.f });
    }
};

int main()
{
    auto window = GraphicsFactory::GetInstance().CreateWindow();
    window->SetTitle("Knight Parade");
    window->SetMode(Window::Mode::Windowed);
    window->SetPosition({ 20, 30 });

    World& world = World::GetInstance();
    
    auto createKnight = [&world](const Vector3f& startingPos)
    {
        shared_ptr<Entity> sampleEntity = world.CreateEntity().lock();
        if (!sampleEntity)
        {
            cerr << "Could not initialize Entity" << endl;
            return;
        }

        sampleEntity->SetPosition(startingPos);
        sampleEntity->AddComponent<SpriteComponent>("Resources/Knight.png");
        sampleEntity->AddComponent<MarchComponent>(1.f, 5.f, DegToRad(180.f), startingPos[0]);
    };

    createKnight({ -0.75f, 3.f, 0.f });
    createKnight({ -0.25f, 0.f, 0.f });
    createKnight({ +0.25f, -3.f, 0.f });
    createKnight({ +0.75f, -6.f, 0.f });

    Window::Size targetSize = { 1280, 720 };
    const float ratio = float(targetSize.width) / float(targetSize.height);

    auto camera = std::make_unique<Camera>(Camera::FrustumParameters{ DegToRad(75.f), ratio, 0.1f, 100.f }, Camera::Type::Perspective);
    camera->SetPosition({ 0.f, -0.5f, 3.f });
    camera->SetLookAt({ 0.f, 0.5, -0.25f });
    window->GetRenderingContext().SetCamera(std::move(camera));
    window->Resize(targetSize);
    world.SetWindow(std::move(window));

    world.Play();
    return 0;
}