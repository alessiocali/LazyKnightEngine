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

int main()
{
    auto window = GraphicsFactory::GetInstance().CreateWindow();
    window->SetTitle("Base Scene");
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
        sampleEntity->SetPosition({ 0.f, 2.f, 0.f });
    }

    world.Play();
    return 0;
}