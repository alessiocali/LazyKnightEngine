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
    }

    world.Play();
    return 0;
}