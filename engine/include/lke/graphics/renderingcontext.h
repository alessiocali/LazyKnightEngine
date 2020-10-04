#pragma once
#include <lke/lke.h>

#include <lke/math/matrix.h>
#include <lke/math/vectors.h>

#include <memory>

namespace lke
{
	class Model;
	class Sprite;
	class Camera;

	class lkedll RenderingContext
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