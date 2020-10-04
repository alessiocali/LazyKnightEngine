#include <lke/core/world.h>
#include <lke/graphics/graphicsfactory.h>
#include <lke/graphics/window.h>

using namespace lke;

int main()
{
    World& world = World::GetInstance();
    
    auto window = GraphicsFactory::GetInstance().CreateWindow();
    window->SetTitle("Hello Lazy Knight!");
    window->SetMode(Window::Mode::Windowed);

    world.SetWindow(std::move(window));
    world.Play();

	return 0;
}