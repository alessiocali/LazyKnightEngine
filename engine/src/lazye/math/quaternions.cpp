#include <lazye/math/quaternions.h>

#include <lazye/math/math.h>

namespace lazye
{
    bool IsNormalized(const Quaternion& quaternion)
    {
        const float vectorLengthSquared = GetLengthSquared(quaternion.m_Vector);
        const float scalarSquared = SquareOf(quaternion.m_Scalar);
        return EpsilonEqual(vectorLengthSquared + scalarSquared, 1.f);
    }

    bool EpsilonEqual(const Quaternion& q1, const Quaternion& q2)
    {
        return EpsilonEqual(q1.m_Vector, q2.m_Vector) && EpsilonEqual(q1.m_Scalar, q2.m_Scalar);
    }

    Quaternion Quaternion::FromAngleAxis(const AngleAxis& angleAxis)
    {
        Assert(IsNormalized(angleAxis.m_Axis));
        Vector3f newQuaternionVector = Sin(angleAxis.m_Angle / 2.f) * angleAxis.m_Axis;
        float newQuaternionScalar = Cos(angleAxis.m_Angle / 2.f);
        return Quaternion(newQuaternionVector, newQuaternionScalar);
    }

    Quaternion Quaternion::operator*(const Quaternion& other) const
    {
        const Vector3f productVector =
                m_Scalar * other.m_Vector 
            +   other.m_Scalar * m_Vector
            +   Cross(m_Vector, other.m_Vector);

        const float productScalar =
                m_Scalar * other.m_Scalar 
            -   Dot(m_Vector, other.m_Vector);

        return Quaternion(productVector, productScalar);
    }

    Vector3f Quaternion::operator*(const Vector3f& vector) const
    {
        const Quaternion vectorAsQuaternion(vector, 0);
        const Quaternion rotatedResult = (*this * vectorAsQuaternion) * GetInverse();
        return rotatedResult.m_Vector;
    }

    Quaternion Quaternion::GetInverse() const
    {
        Assert(IsNormalized(*this));
        return Quaternion(-m_Vector, m_Scalar);
    }

    EulerAngles Quaternion::ToEulerAngles() const
    {
        EulerAngles result;

        const float x = X();
        const float y = Y();
        const float z = Z();
        const float w = W();
        
        result.m_Pitch  = std::atan2(2 * (w * x + y * z), 1 - 2 * (x * x + y * y));
        result.m_Roll   = std::asin(2 * (w * y - z * x));
        result.m_Yaw    = std::atan2(2 * (w * z + x * y), 1 - 2 * (y * y + z * z));

        return result;
    }
}