#include <catch2/catch.hpp>

#include <lke/math/quaternions.h>
#include <lke/math/matrix.h>
#include <lke/math/math.h>

constexpr const char* QuaternionsTag = "[quaternions]";

SCENARIO("Quaternions are correctly constructed and initialized", QuaternionsTag)
{
    using namespace lke;

    GIVEN("An angle and the K axis")
    {
        constexpr Radians angle = DegToRad(45.f);
        constexpr Vector3f axis = Vector3f::GetAxisK();

        WHEN("We instantiate a Quaternion from them")
        {
            Quaternion quat = Quaternion::FromAngleAxis({ angle, axis });
            REQUIRE(IsNormalized(quat));

            THEN("The inverse vector is correctly calculated")
            {
                REQUIRE(EpsilonEqual(quat * quat.GetInverse(), Quaternion::GetIdentity()));
                REQUIRE(EpsilonEqual(quat.GetInverse() * quat, Quaternion::GetIdentity()));
            }

            AND_THEN("Multiplying a vector by this quaternion and its inverse is idempotent")
            {
                constexpr Vector3f testVector = { 1.f, 2.f, 3.f };
                REQUIRE(EpsilonEqual(testVector, quat.GetInverse() * (quat * testVector)));
                REQUIRE(EpsilonEqual(testVector, quat * (quat.GetInverse() * testVector)));
            }

            AND_THEN("Compositing quaternions yields the expected result")
            {
                Quaternion _45Deg = Quaternion::FromAngleAxis({ DegToRad(45.f), Vector3f::GetAxisK() });
                Quaternion _180Deg = Quaternion::FromAngleAxis({ DegToRad(180.f), Vector3f::GetAxisK() });
                Quaternion _225Deg = Quaternion::FromAngleAxis({ DegToRad(225.f), Vector3f::GetAxisK() });

                REQUIRE(EpsilonEqual(_45Deg * _180Deg, _225Deg));
                REQUIRE(EpsilonEqual(_180Deg * _45Deg, _225Deg));

                constexpr Vector3f testVector = { 1.f, 2.f, 3.f };
                REQUIRE(EpsilonEqual(_180Deg * _45Deg * testVector, _225Deg * testVector));
            }

            AND_THEN("Rotating vectors at various degrees yield correct results")
            {
                Vector3f _0Deg = { 1.f, 0.f, 0.f };
                Vector3f _45Deg = { 1.f / Sqrt(2.f), 1.f / Sqrt(2.f), 0.f };
                Vector3f _90Deg = { 0.f, 1.f, 0.f };
                Vector3f _135Deg = { -1.f / Sqrt(2.f), 1.f / Sqrt(2.f), 0.f };
                Vector3f _180Deg = { -1.f, 0.f, 0.f };
                Vector3f _225Deg = { -1.f / Sqrt(2.f), -1.f / Sqrt(2.f), 0.f };
                Vector3f _270Deg = { 0.f, -1.f, 0.f };
                Vector3f _315Deg = { 1.f / Sqrt(2.f), -1.f / Sqrt(2.f), 0.f };

                REQUIRE(EpsilonEqual(quat * _0Deg, _45Deg));
                REQUIRE(EpsilonEqual(quat * _45Deg, _90Deg));
                REQUIRE(EpsilonEqual(quat * _90Deg, _135Deg));
                REQUIRE(EpsilonEqual(quat * _135Deg, _180Deg));
                REQUIRE(EpsilonEqual(quat * _180Deg, _225Deg));
                REQUIRE(EpsilonEqual(quat * _225Deg, _270Deg));
                REQUIRE(EpsilonEqual(quat * _270Deg, _315Deg));
                REQUIRE(EpsilonEqual(quat * _315Deg, _0Deg));
            }
        }
    }

    GIVEN("Some directions")
    {
        Vector3f test1 = GetNormalized(Vector3f { 1.f, 1.f, 1.f });
        Vector3f test2 = GetNormalized(Vector3f { 1.f, 0.f, 1.f });
        Vector3f test3 = GetNormalized(Vector3f { 0.f, 1.f, 1.f });
        Vector3f test4 = GetNormalized(Vector3f { 1.f, 1.f, 0.f });

        WHEN("We construct LookAt Quaternions from them")
        {
            Quaternion lookAt1 = Quaternion::FromLookAt(test1);
            Quaternion lookAt2 = Quaternion::FromLookAt(test2);
            Quaternion lookAt3 = Quaternion::FromLookAt(test3);
            Quaternion lookAt4 = Quaternion::FromLookAt(test4);

            THEN("Rotation the Y axis with them yields the original LookAt vector")
            {
                // ...Save some floating point errors
                REQUIRE(EpsilonEqual(lookAt1 * Vector3f::GetAxisJ(), test1, 0.00001f));
                REQUIRE(EpsilonEqual(lookAt2 * Vector3f::GetAxisJ(), test2, 0.00001f));
                REQUIRE(EpsilonEqual(lookAt3 * Vector3f::GetAxisJ(), test3, 0.00001f));
                REQUIRE(EpsilonEqual(lookAt4 * Vector3f::GetAxisJ(), test4, 0.00001f));
            }
        }
    }
};

SCENARIO("Quaternion decomposition", QuaternionsTag)
{
    using namespace lke;

    GIVEN("The identity quaternion")
    {
        Quaternion identity { Quaternion::GetIdentity() };

        THEN("It decomposes into the Identity matrix")
        {
            Matrix44f resultMatrix;
            SetToRotationMatrix(resultMatrix, identity);

            REQUIRE(EpsilonEqual(resultMatrix, Matrix44f::GetIdentity()));
        }

        AND_THEN("It decomposes into null angles")
        {
            EulerAngles eulers = identity.ToEulerAngles();

            REQUIRE(EpsilonNull(eulers.m_Pitch));
            REQUIRE(EpsilonNull(eulers.m_Roll));
            REQUIRE(EpsilonNull(eulers.m_Yaw));
        }
    }

    GIVEN("90-degree Rotations against the different axises")
    {
        Quaternion aroundX{ Quaternion::FromAngleAxis({ DegToRad(90.f), Vector3f::GetAxisI() }) };
        Quaternion aroundY{ Quaternion::FromAngleAxis({ DegToRad(90.f), Vector3f::GetAxisJ() }) };
        Quaternion aroundZ{ Quaternion::FromAngleAxis({ DegToRad(90.f), Vector3f::GetAxisK() }) };
    
        THEN("The corresponding matrices are as expected")
        {
            Matrix44f matAroundX(
            {
                1.f, 0.f, 0.f, 0.f,
                0.f, 0.f, -1.f, 0.f,
                0.f, 1.f, 0.f, 0.f,
                0.f, 0.f, 0.f, 1.f
            });
            
            Matrix44f matAroundY(
            {
                0.f, 0.f, 1.f, 0.f,
                0.f, 1.f, 0.f, 0.f,
                -1.f, 0.f, 0.f, 0.f,
                0.f, 0.f, 0.f, 1.f
            });
            
            Matrix44f matAroundZ(
            {
                0.f, -1.f, 0.f, 0.f,
                1.f, 0.f, 0.f, 0.f,
                0.f, 0.f, 1.f, 0.f,
                0.f, 0.f, 0.f, 1.f
            });

            Matrix44f resultX, resultY, resultZ;

            SetToRotationMatrix(resultX, aroundX);
            SetToRotationMatrix(resultY, aroundY);
            SetToRotationMatrix(resultZ, aroundZ);

            REQUIRE(EpsilonEqual(resultX, matAroundX));
            REQUIRE(EpsilonEqual(resultY, matAroundY));
            REQUIRE(EpsilonEqual(resultZ, matAroundZ));
        }

        AND_THEN("They decompose correctly into Euler angles")
        {
            EulerAngles eulerX = aroundX.ToEulerAngles();
            EulerAngles eulerY = aroundY.ToEulerAngles();
            EulerAngles eulerZ = aroundZ.ToEulerAngles();

            REQUIRE(EpsilonEqual(eulerX.m_Pitch, DegToRad(90)));
            REQUIRE(EpsilonNull(eulerX.m_Roll));
            REQUIRE(EpsilonNull(eulerY.m_Yaw));

            // Asin is slightly inaccurate, so let's account for a larger epsilon
            REQUIRE(EpsilonEqual(eulerY.m_Roll, DegToRad(90), 0.001f));
            REQUIRE(EpsilonNull(eulerY.m_Yaw));
            REQUIRE(EpsilonNull(eulerY.m_Pitch));

            REQUIRE(EpsilonEqual(eulerZ.m_Yaw, DegToRad(90)));
            REQUIRE(EpsilonNull(eulerZ.m_Roll));
            REQUIRE(EpsilonNull(eulerZ.m_Pitch));
        }
    }
}