#include <lazye/graphics/renderingcomponent.h>

namespace lazye
{
	void RenderingComponent::Update(float dt)
	{
		Render(dt, *m_Context);
	}
}