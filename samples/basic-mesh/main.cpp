#include <lke/core/world.h>
#include <lke/core/entity.h>
#include <lke/graphics/graphicsfactory.h>
#include <lke/graphics/window.h>
#include <lke/graphics/camera.h>
#include <lke/graphics/modelcomponent.h>

#include <iostream>
#include <memory>

#include <cassert>

using namespace std;
using namespace lke;

class SpinnerComponent : public Component
{
public:
    SpinnerComponent(Radians rotationSpeed)
        : m_RotationSpeed(rotationSpeed)
    { }

    void Update(float dt) override
    {
        m_CurrentAngle += m_RotationSpeed * dt;
        if (m_CurrentAngle < DegToRad(-360.f)) { m_CurrentAngle += DegToRad(360.f); }
        if (m_CurrentAngle > DegToRad(360.f)) { m_CurrentAngle -= DegToRad(360.f); }
        GetOwner()->SetRotation(Quaternion::FromAngleAxis({ m_CurrentAngle, Vector3f::GetAxisK() }));
    }

private:
    Radians m_RotationSpeed;
    Radians m_CurrentAngle { 0.f };
};

int main()
{
    auto window = GraphicsFactory::GetInstance().CreateWindow();
    window->SetTitle("Mesh Scene");
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

        sampleEntity->AddComponent<ModelComponent>("Resources/Knight/scene.gltf");
        sampleEntity->AddComponent<SpinnerComponent>(DegToRad(10.f));

        sampleEntity->SetScaling({ 0.05f, 0.05f, 0.05f });
        sampleEntity->SetPosition({ 0.f, 20.f, -5.f });
    }

    world.Play();
    return 0;
}