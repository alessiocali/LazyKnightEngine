#include <lke/math/transform.h>

#include <lke/math/math.h>

namespace lke
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

    void Transform::UpdateMatrix()
    {
        if (m_Dirty)
        {
            RecomputeMatrix();
        }
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
        Matrix44f scale, rotation, translation;

        SetToScalingMatrix(scale, m_Scaling);
        SetToRotationMatrix(rotation, m_Rotation);
        SetToTranslationMatrix(translation, m_Position);

        m_Matrix = translation * rotation * scale;

        m_Dirty = false;
    }
}