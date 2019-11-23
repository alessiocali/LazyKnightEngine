#include <lazye/graphics/window.h>

using namespace lazye;

int main()
{
    Window window("Hello Window", 1920, 1080);
    window.RenderLoop();
	return 0;
}