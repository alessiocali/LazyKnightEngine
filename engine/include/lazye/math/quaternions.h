#pragma once 

#include <lazye/lazye.h>
#include <lazye/math/math.h>
#include <lazye/math/vectors.h>

namespace lazye
{
    class Quaternion;

    struct AngleAxis
    {
        Radians m_Angle;
        Vector3f m_Axis;
    };

    bool IsNormalized(const Quaternion& quaternion);
    bool EpsilonEqual(const Quaternion& q1, const Quaternion& q2);

    class lazyedll Quaternion
    {
    public:
        friend bool IsNormalized(const Quaternion& quaternion);
        friend bool EpsilonEqual(const Quaternion& q1, const Quaternion& q2);

        Quaternion()
            : m_Vector(0, 0, 0), m_Scalar(0)
        { }

        Quaternion(float x, float y, float z, float w)
            : m_Vector(x, y, z), m_Scalar(w)
        { }

        explicit Quaternion(Vector3f vector, float scalar)
            : m_Vector(vector), m_Scalar(scalar)
        { }

        static Quaternion GetIdentity() { return Quaternion(0, 0, 0, 1.f); }
        static Quaternion FromAngleAxis(const AngleAxis& angleAxis);
        
        /**
         *  @brief Grassman product multiplication. 
         *  See Game Engine Architecture, 3rd Edition, page 396
         */
        Quaternion operator*(const Quaternion& other) const;

        /**
         *  @brief Rotates the input 3D Vector by this Quaternion
         */
        Vector3f operator*(const Vector3f& vector) const;

        /**
         *  @brief Returns the Quaternion representing the inverse rotation
         *  of this Quaternion, i.e. its conjugate. The Quaternion __must__
         *  be unitary.
         */
        Quaternion GetInverse() const;

    private:
        Vector3f m_Vector;
        float m_Scalar;
    };
}