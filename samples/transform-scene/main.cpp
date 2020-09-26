#include <lazye/core/world.h>
#include <lazye/core/entity.h>
#include <lazye/graphics/graphicsfactory.h>
#include <lazye/graphics/window.h>
#include <lazye/graphics/camera.h>
#include <lazye/graphics/spritecomponent.h>

#include <iostream>
#include <memory>

#include <cassert>

using namespace std;
using namespace lazye;

/**
 *  Entity goes weeeeee
 */
class SpinComponent : public Component
{
public:
    SpinComponent(Radians trFreq, Radians horRotFreq, Radians verRotFreq, Radians sclFreq)
        :   m_TranslationFrequency(trFreq), 
            m_HorizontalRotationFrequency(horRotFreq),
            m_VerticalRotationFrequency(verRotFreq),
            m_ScalingFrequency(sclFreq)
    { }

    void Update(float dt) override
    {
        m_InternalClock += dt;

        const Vector3f& currentPos = GetOwner()->GetPosition();
        GetOwner()->SetPosition(Vector3f{ Sin(m_TranslationFrequency * m_InternalClock), currentPos[1], Cos(m_TranslationFrequency * m_InternalClock) });
        GetOwner()->SetRotation(
            Quaternion::FromAngleAxis({ m_HorizontalRotationFrequency * dt, Vector3f::GetAxisJ() }) * 
            GetOwner()->GetRotation() * 
            Quaternion::FromAngleAxis({ m_VerticalRotationFrequency * dt, Vector3f::GetAxisK() })
        );
        GetOwner()->SetScaling(Vector3f{ 1.5f + Sin(m_ScalingFrequency * m_InternalClock), 1.5f + Sin(m_ScalingFrequency * m_InternalClock), 1.f });
    }
private:
    Seconds m_InternalClock{ 0.f };

    Radians m_TranslationFrequency;
    Radians m_HorizontalRotationFrequency;
    Radians m_VerticalRotationFrequency;
    Radians m_ScalingFrequency;
};

int main()
{
    auto window = GraphicsFactory::GetInstance().CreateWindow();
    window->SetTitle("Transform Scene");
    window->SetMode(Window::Mode::Windowed);
    window->Resize({ 1280, 720 });
    window->GetRenderingContext().SetCamera(std::make_unique<Camera>(Camera::FrustumParameters({ DegToRad(75.f), 16.f / 9.f, 0.1f, 100.f }), Camera::Type::Perspective));

    World& world = World::GetInstance();
    world.SetWindow(std::move(window));
    
    {
        shared_ptr<Entity> sampleEntity = world.CreateEntity().lock();
        if (!sampleEntity)
        {
            cerr << "Could not initialize Entity" << endl;
            return 1;
        }

        sampleEntity->AddComponent<SpriteComponent>("Resources/Knight.png");
        sampleEntity->AddComponent<SpinComponent>(DegToRad(30.f), DegToRad(20.f), DegToRad(20.f), DegToRad(20.f));
        sampleEntity->SetPosition({ 0.f, 2.f, 0.f });
    }

    world.Play();
    return 0;
}