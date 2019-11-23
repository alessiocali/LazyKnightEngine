#include <catch2/catch.hpp>
#include <lazye/math.h>

constexpr const char* VectorsTag = "[vectors]";

SCENARIO("Vectors are correctly constructed and initialized", VectorsTag)
{
	GIVEN("Vectors of all supported dimensions")
	{
		lazye::Vector2f aVector2(1.f, 2.f);
		lazye::Vector3f aVector3(1.f, 2.f, 3.f);
		lazye::Vector4f aVector4(1.f, 2.f, 3.f, 4.f);

		REQUIRE(aVector2.Dimension() == 2);
		REQUIRE(aVector3.Dimension() == 3);
		REQUIRE(aVector4.Dimension() == 4);

		REQUIRE(aVector2[0] == 1.f);
		REQUIRE(aVector2[1] == 2.f);

		REQUIRE(aVector3[0] == 1.f);
		REQUIRE(aVector3[1] == 2.f);
		REQUIRE(aVector3[2] == 3.f);

		REQUIRE(aVector4[0] == 1.f);
		REQUIRE(aVector4[1] == 2.f);
		REQUIRE(aVector4[2] == 3.f);
		REQUIRE(aVector4[3] == 4.f);

		WHEN("the vector content are changed")
		{
			aVector2[0] = 2.f;
			aVector2[1] = 3.f;

			aVector3[0] = 4.f;
			aVector3[1] = 5.f;
			aVector3[2] = 6.f;

			aVector4[0] = 7.f;
			aVector4[1] = 8.f;
			aVector4[2] = 9.f;
			aVector4[3] = 10.f;

			THEN("their content is updated accordingly.")
			{
				REQUIRE(aVector2[0] == 2.f);
				REQUIRE(aVector2[1] == 3.f);

				REQUIRE(aVector3[0] == 4.f);
				REQUIRE(aVector3[1] == 5.f);
				REQUIRE(aVector3[2] == 6.f);

				REQUIRE(aVector4[0] == 7.f);
				REQUIRE(aVector4[1] == 8.f);
				REQUIRE(aVector4[2] == 9.f);
				REQUIRE(aVector4[3] == 10.f);
			}
		}
	}
}

SCENARIO("Mathematical operation on vectors behave as expected", VectorsTag)
{
	using lazye::EpsilonEqual;

	GIVEN("Couples of vectors of all supported sizes")
	{
		lazye::Vector2f aVector2(1.f, -2.f);
		lazye::Vector2f bVector2(-3.f, 4.f);

		lazye::Vector3f aVector3(5.f, 6.f, 7.f);
		lazye::Vector3f bVector3(8.f, 9.f, 10.f);
		
		lazye::Vector4f aVector4(-11.f, -12.f, -13.f, -14.f);
		lazye::Vector4f bVector4(-15.f, -16.f, -17.f, -18.f);

		WHEN("their dot product is computed")
		{
			const float biDot = lazye::Dot(aVector2, bVector2);
			const float triDot = lazye::Dot(aVector3, bVector3);
			const float quadDot = lazye::Dot(aVector4, bVector4);

			THEN("the result is correct.")
			{
				REQUIRE(EpsilonEqual(biDot, -11.f));
				REQUIRE(EpsilonEqual(triDot, 164.f));
				REQUIRE(EpsilonEqual(quadDot, 830.f));
			}
		}

		WHEN("we dot a vector by itself and compute the squared length")
		{
			const float biSelf = lazye::Dot(aVector2, aVector2);
			const float triSelf = lazye::Dot(aVector3, aVector3);
			const float quadSelf = lazye::Dot(aVector4, aVector4);

			THEN("the result is comparable with the length squared.")
			{
				REQUIRE(EpsilonEqual(biSelf, lazye::GetLengthSquared(aVector2)));
				REQUIRE(EpsilonEqual(triSelf, lazye::GetLengthSquared(aVector3)));
				REQUIRE(EpsilonEqual(quadSelf, lazye::GetLengthSquared(aVector4)));
			}
		}

		WHEN("we compute the lenght of a vector")
		{
			const float biLength = lazye::GetLength(aVector2);
			const float triLength = lazye::GetLength(aVector3);
			const float quadLength = lazye::GetLength(aVector4);

			THEN("the result is comparable with the squared root of the length squared")
			{
				REQUIRE(EpsilonEqual(biLength, std::sqrt(lazye::GetLengthSquared(aVector2))));
				REQUIRE(EpsilonEqual(triLength, std::sqrt(lazye::GetLengthSquared(aVector3))));
				REQUIRE(EpsilonEqual(quadLength, std::sqrt(lazye::GetLengthSquared(aVector4))));
			}
		}
	}
}