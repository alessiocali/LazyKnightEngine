#include <lke/graphics/camera.h>

#include <lke/graphics/graphicsfactory.h>
#include <lke/math/transform.h>

namespace lke
{
    Camera::Camera(const FrustumParameters& params, const Type type)
        : m_ViewMatrix(Matrix44f::GetIdentity())
    {
        switch (type)
        {
        case Type::Orthogonal:
            SetToOrthogonalProjectionMatrix(m_ProjectionMatrix, params);
            break;
        case Type::Perspective:
            SetToPerspectiveProjectionMatrix(m_ProjectionMatrix, params);
            break;
        default:
            Assert(false, "Unknown Camera Type");
            break;
        }
    }

    void Camera::UpdateViewMatrix()
    {
        if (!m_Dirty)
        {
            return;
        }

        Matrix44f rotationMatrix;
        SetToRotationMatrix(rotationMatrix, m_Rotation);

        Matrix44f translationMatrix;
        SetToTranslationMatrix(translationMatrix, m_Position);

        m_ViewMatrix = GetInverse(translationMatrix * rotationMatrix * GraphicsFactory::GetInstance().GetCameraCorrectionMatrix());
        m_Dirty = false;
    }

    void Camera::SetPosition(const Vector3f& position)
    {
        m_Position = position;
        Invalidate();
    }

    void Camera::SetRotation(const Quaternion& rotation)
    {
        m_Rotation = rotation;
        Invalidate();
    }

    /*static*/ void Camera::SetToOrthogonalProjectionMatrix(Matrix44f& matrix, const FrustumParameters& params)
    {
        Assert(params.m_Near > 0);
        Assert(params.m_Far > params.m_Near);
        Assert(params.m_FoV > 0.f && params.m_FoV < PI);
        Assert(params.m_Ratio > 0.f);

        const float halfWidth = params.m_Near * std::tan(params.m_FoV * 0.5f);
        const float halfHeight = halfWidth / params.m_Ratio;

        matrix(0, 0) = 1.f / halfWidth;
        matrix(0, 1) = 0.f;
        matrix(0, 2) = 0.f;
        matrix(0, 3) = 0.f;

        matrix(1, 0) = 0.f;
        matrix(1, 1) = 1.f / halfHeight;
        matrix(1, 2) = 0.f;
        matrix(1, 3) = 0.f;

        matrix(2, 0) = 0.f;
        matrix(2, 1) = 0.f;
        matrix(2, 2) = -2.f / (params.m_Far - params.m_Near);
        matrix(2, 3) = -(params.m_Far + params.m_Near) / (params.m_Far - params.m_Near);

        matrix(3, 0) = 0.f;
        matrix(3, 1) = 0.f;
        matrix(3, 2) = 0.f;
        matrix(3, 3) = 1.f;
    }

    /*static*/ void Camera::SetToPerspectiveProjectionMatrix(Matrix44f& matrix, const FrustumParameters& params)
    {
        Assert(params.m_Near > 0);
        Assert(params.m_Far > params.m_Near);
        Assert(params.m_FoV > 0.f && params.m_FoV < PI);
        Assert(params.m_Ratio > 0.f);

        const float widthParam = 1.f / std::tan(params.m_FoV * 0.5f);
        const float heightParam = widthParam * params.m_Ratio;

        matrix(0, 0) = widthParam;
        matrix(0, 1) = 0.f;
        matrix(0, 2) = 0.f;
        matrix(0, 3) = 0.f;

        matrix(1, 0) = 0.f;
        matrix(1, 1) = heightParam;
        matrix(1, 2) = 0.f;
        matrix(1, 3) = 0.f;

        matrix(2, 0) = 0.f;
        matrix(2, 1) = 0.f;
        matrix(2, 2) = -(params.m_Far + params.m_Near) / (params.m_Far - params.m_Near);
        matrix(2, 3) = -2.f * params.m_Far * params.m_Near / (params.m_Far - params.m_Near);

        matrix(3, 0) = 0.f;
        matrix(3, 1) = 0.f;
        matrix(3, 2) = -1.f;
        matrix(3, 3) = 0.f;
    }

    void Camera::Invalidate()
    {
        m_Dirty = true;
    }
}