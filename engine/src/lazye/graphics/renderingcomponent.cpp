#include <lazye/graphics/renderingcomponent.h>

#include <lazye/core/world.h>
#include <lazye/core/entity.h>

namespace lazye
{
	void RenderingComponent::Update(float dt)
	{
		UpdateOwnerTransform();
		Render(dt, World::GetInstance().GetRenderingContext());
	}
}