#include <lazye/core/world.h>
#include <lazye/core/entity.h>
#include <lazye/graphics/graphicsfactory.h>
#include <lazye/graphics/window.h>
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

        GetOwner()->SetPosition(Vector3f{ Sin(m_TranslationFrequency * m_InternalClock), Cos(m_TranslationFrequency * m_InternalClock), 0.f });
        GetOwner()->SetRotation(
            Quaternion::FromAngleAxis({ m_HorizontalRotationFrequency * dt, Vector3f::GetAxisK() }) * 
            GetOwner()->GetRotation() * 
            Quaternion::FromAngleAxis({ m_VerticalRotationFrequency * dt, Vector3f::GetAxisJ() })
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
    }

    world.Play();
    return 0;
}