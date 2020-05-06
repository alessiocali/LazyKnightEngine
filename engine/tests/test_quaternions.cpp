#include <catch2/catch.hpp>

#include <lazye/math/quaternions.h>

constexpr const char* QuaternionsTag = "[quaternions]";

SCENARIO("Quaternions are correctly constructed and initialized", QuaternionsTag)
{
    using namespace lazye;

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
}