#pragma once
#include <lazye/lazye.h>

#include <lazye/math/matrix.h>
#include <lazye/math/vectors.h>

#include <memory>

namespace lazye
{
	class Model;
	class Sprite;
	class Camera;

	class lazyedll RenderingContext
	{
	public:
		RenderingContext();
		virtual ~RenderingContext();

		virtual void Clear() = 0;
		virtual void SetClearColor(const Vector3f& color) = 0;

        void SetCamera(std::unique_ptr<Camera> camera);
        void UpdateCamera();

		std::tuple<const Matrix44f&, const Matrix44f&> GetViewProjectionMatrices() const;

	protected:
		std::unique_ptr<Camera> m_Camera { nullptr };
	};
}