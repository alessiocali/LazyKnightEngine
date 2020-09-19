#pragma once

#include <lazye/math/vectors.h>
#include <lazye/math/matrix.h>
#include <lazye/math/quaternions.h>

namespace lazye
{
    lazyedll class Transform
    {
    public:
        inline const Vector3f& GetPosition() const { return m_Position; }
        inline const Vector3f& GetScaling() const { return m_Scaling; }
        inline const Quaternion& GetRotation() const { return m_Rotation; }

        void UpdateMatrix();

        const Matrix44f& GetMatrix() const { return m_Matrix; }
        const Matrix44f& GetUpdatedMatrix();

        void SetPosition(const Vector3f& position);
        void SetRotation(const Quaternion& rotation);
        void SetScaling(const Vector3f& scaling);

    private:
        Vector3f m_Position { Vector3f::GetZero() };
        Quaternion m_Rotation { Quaternion::GetIdentity() };
        Vector3f m_Scaling { 1.f, 1.f, 1.f };

        bool m_Dirty { false };
        Matrix44f m_Matrix { Matrix44f::GetIdentity() };

        void Invalidate();
        void RecomputeMatrix();
    };
}