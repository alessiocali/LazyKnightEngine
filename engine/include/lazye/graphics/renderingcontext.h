#pragma once
#include <lazye/lazye.h>

#include <lazye/math/vectors.h>

#include <memory>

namespace lazye
{
	class Sprite;
	class Camera;

	class lazyedll RenderingContext
	{
	public:
		RenderingContext();
		virtual ~RenderingContext();

		virtual void Clear() = 0;

		virtual void Render(const Sprite& sprite) = 0;
		virtual void SetClearColor(const Vector3f& color) = 0;

		void SetCamera(std::unique_ptr<Camera> camera);

	protected:
		std::unique_ptr<Camera> m_Camera { nullptr };
	};
}