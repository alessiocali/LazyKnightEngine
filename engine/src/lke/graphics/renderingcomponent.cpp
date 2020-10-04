#include <lke/graphics/renderingcomponent.h>

#include <lke/core/world.h>
#include <lke/core/entity.h>

namespace lke
{
	void RenderingComponent::Update(float dt)
	{
		Render(GetOwner()->GetWorld()->GetRenderingContext());
	}
}