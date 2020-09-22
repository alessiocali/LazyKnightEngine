#include <lazye/core/world.h>
#include <lazye/graphics/graphicsfactory.h>
#include <lazye/graphics/window.h>

using namespace lazye;

int main()
{
    World& world = World::GetInstance();
    
    auto window = GraphicsFactory::GetInstance().CreateWindow();
    window->Resize(Window::Size{ 1280, 720 });
    window->SetTitle("Hello LazyE!");
    window->SetMode(Window::Mode::Windowed);

    world.SetWindow(std::move(window));
    world.Play();

	return 0;
}