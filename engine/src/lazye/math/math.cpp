#include <lazye/math/math.h>

#include <lazye/math/quaternions.h>

namespace lazye
{
    float Sin(Radians angle)
    {
        return std::sin(angle);
    }

    float Cos(Radians angle)
    {
        return std::cos(angle);
    }

    void QuaternionToRotationMatrix(Matrix44f& targetMatrix, const Quaternion& quaternion)
    {
        const float x = quaternion.X();
        const float y = quaternion.Y();
        const float z = quaternion.Z();
        const float w = quaternion.W();

        targetMatrix(0, 0) = 1 - 2 * y * y - 2 * z * z;
        targetMatrix(0, 1) = 2 * x * y - 2 * z * w;
        targetMatrix(0, 2) = 2 * x * z + 2 * y * w;
        
        targetMatrix(1, 0) = 2 * x * y + 2 * z * w;
        targetMatrix(1, 1) = 1 - 2 * x * x - 2 * z * z;
        targetMatrix(1, 2) = 2 * y * z - 2 * x * w;
        
        targetMatrix(2, 0) = 2 * z * x - 2 * y * w;
        targetMatrix(2, 1) = 2 * y * z + 2 * x * w;
        targetMatrix(2, 2) = 1 - 2 * x * x - 2 * y * y;

        targetMatrix(0, 3) = targetMatrix(1, 3) = targetMatrix(2, 3) = 0.f;
        targetMatrix(3, 0) = targetMatrix(3, 1) = targetMatrix(3, 2) = 0.f;
        targetMatrix(3, 3) = 1.f;
    }
}