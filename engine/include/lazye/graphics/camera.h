#pragma once
#include <lazye/lazye.h>

#include <lazye/math/vectors.h>
#include <lazye/math/quaternions.h>
#include <lazye/math/matrix.h>

namespace lazye
{
    class lazyedll Camera
    {
    public:
        enum class Type
        {
            Orthogonal,
            Perspective
        };

        /**
         *  Parameters defining a symmetric Frustum.
         *
         *  @param m_FoV:   Full Horizontal Field of View (in Radians). 
         *                  Must be positive and less than 180 Degrees.
         *  @param m_Ratio: Ratio between the view's width and height.
         *  @param m_Near:  Near plane position. Must be positive.
         *  @param m_Far:   Far plane position. Must be greater than m_Near.
         */
        struct FrustumParameters
        {
            Radians m_FoV;
            float m_Ratio;
            float m_Near;
            float m_Far;
        };

        Camera(const FrustumParameters& params, const Type type);

        void UpdateViewMatrix();

        inline void SetLookAt(const Vector3f& lookAt) { SetRotation(Quaternion::FromLookAt(lookAt)); }

        void SetRotation(const Quaternion& rotation);
        void SetPosition(const Vector3f& position);

        inline auto GetViewProjectionMatrices() const { return std::tuple<const Matrix44f&, const Matrix44f&> { m_ViewMatrix, m_ProjectionMatrix }; }

        inline const Matrix44f& GetProjectionMatrix() const { return m_ProjectionMatrix; }
        inline const Matrix44f& GetViewMatrix() const { return m_ViewMatrix; }

    private:

        static void SetToOrthogonalProjectionMatrix(Matrix44f& matrix, const FrustumParameters& params);
        static void SetToPerspectiveProjectionMatrix(Matrix44f& matrix, const FrustumParameters& params);

        void Invalidate();

        bool m_Dirty { true };
        Vector3f m_Position { Vector3f::GetZero() };
        Quaternion m_Rotation { Quaternion::GetIdentity() };

        Matrix44f m_ProjectionMatrix { Matrix44f::GetIdentity() };
        Matrix44f m_ViewMatrix { Matrix44f::GetIdentity() };
    };
}