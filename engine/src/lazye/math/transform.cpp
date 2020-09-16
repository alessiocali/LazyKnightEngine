#include <lazye/math/transform.h>

#include <lazye/math/math.h>

namespace lazye
{
    void Transform::SetPosition(const Vector3f& position)
    {
        m_Position = position;
        Invalidate();
    }

    void Transform::SetRotation(const Quaternion& rotation)
    {
        m_Rotation = rotation;
        Invalidate();
    }

    void Transform::SetScaling(const Vector3f& scaling)
    {
        m_Scaling = scaling;
        Invalidate();
    }

    const Matrix44f& Transform::GetUpdatedMatrix()
    {
        if (m_Dirty)
        {
            RecomputeMatrix();
        }

        return m_Matrix;
    }

    void Transform::Invalidate()
    {
        m_Dirty = true;
    }

    void Transform::RecomputeMatrix()
    {
        QuaternionToRotationMatrix(m_Matrix, m_Rotation);

        m_Matrix(0, 0) *= m_Scaling[0];
        m_Matrix(1, 1) *= m_Scaling[1];
        m_Matrix(2, 2) *= m_Scaling[2];

        m_Matrix(0, 3) = m_Position[0];
        m_Matrix(1, 3) = m_Position[1];
        m_Matrix(2, 3) = m_Position[2];

        m_Dirty = false;
    }
}