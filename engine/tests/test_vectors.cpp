#include <catch2/catch.hpp>
#include <lazye/math/math.h>
#include <lazye/math/vectors.h>

constexpr const char* VectorsTag = "[vectors]";

SCENARIO("Vectors are correctly constructed and initialized", VectorsTag)
{
	using namespace lazye;

	GIVEN("Null initialized vectors")
	{
		Vector2f aVector2 { Vector2f::GetZero() };
		Vector3f aVector3 { Vector3f::GetZero() };
		Vector4f aVector4 { Vector4f::GetZero() };

		THEN("They are approximately null")
		{
			REQUIRE(EpsilonNull(aVector2));
			REQUIRE(EpsilonNull(aVector3));
			REQUIRE(EpsilonNull(aVector4));
		}
	}

	GIVEN("Vectors of all supported dimensions")
	{
		Vector2f aVector2(1.f, 2.f);
		Vector3f aVector3(1.f, 2.f, 3.f);
		Vector4f aVector4(1.f, 2.f, 3.f, 4.f);

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

		AND_THEN("Comparison with identical vectors succeeds")
		{
			REQUIRE(aVector2 == Vector2f({ 1.f, 2.f }));
			REQUIRE(aVector3 == Vector3f({ 1.f, 2.f, 3.f }));
			REQUIRE(aVector4 == Vector4f({ 1.f, 2.f, 3.f, 4.f }));
		}
	}

	GIVEN("Vector Axises")
	{
		Vector2f bidimI = Vector2f::GetAxisI();
		Vector2f bidimJ = Vector2f::GetAxisJ();

		Vector3f tridimI = Vector3f::GetAxisI();
		Vector3f tridimJ = Vector3f::GetAxisJ();
		Vector3f tridimK = Vector3f::GetAxisK();

		Vector4f quadimI = Vector4f::GetAxisI();
		Vector4f quadimJ = Vector4f::GetAxisJ();
		Vector4f quadimK = Vector4f::GetAxisK();
		Vector4f quadimL = Vector4f::GetAxisL();

		THEN("They are all normalized")
		{
			REQUIRE(IsNormalized(bidimI));
			REQUIRE(IsNormalized(bidimJ));

			REQUIRE(IsNormalized(tridimI));
			REQUIRE(IsNormalized(tridimJ));
			REQUIRE(IsNormalized(tridimK));
			
			REQUIRE(IsNormalized(quadimI));
			REQUIRE(IsNormalized(quadimJ));
			REQUIRE(IsNormalized(quadimK));
			REQUIRE(IsNormalized(quadimL));
		}

		AND_THEN("Their values are correct")
		{
			REQUIRE(EpsilonEqual(bidimI[0], 1.f));
			REQUIRE(EpsilonEqual(bidimJ[1], 1.f));

			REQUIRE(EpsilonEqual(tridimI[0], 1.f));
			REQUIRE(EpsilonEqual(tridimJ[1], 1.f));
			REQUIRE(EpsilonEqual(tridimK[2], 1.f));

			REQUIRE(EpsilonEqual(quadimI[0], 1.f));
			REQUIRE(EpsilonEqual(quadimJ[1], 1.f));
			REQUIRE(EpsilonEqual(quadimK[2], 1.f));
			REQUIRE(EpsilonEqual(quadimL[3], 1.f));
		}
	}
}

SCENARIO("Mathematical operation on vectors behave as expected", VectorsTag)
{
	using namespace lazye;

	GIVEN("Couples of vectors of all supported sizes")
	{
		Vector2f aVector2(1.f, -2.f);
		Vector2f bVector2(-3.f, 4.f);

		Vector3f aVector3(5.f, 6.f, 7.f);
		Vector3f bVector3(8.f, 9.f, 10.f);
		
		Vector4f aVector4(-11.f, -12.f, -13.f, -14.f);
		Vector4f bVector4(-15.f, -16.f, -17.f, -18.f);

		WHEN("their dot product is computed")
		{
			const float biDot = Dot(aVector2, bVector2);
			const float triDot = Dot(aVector3, bVector3);
			const float quadDot = Dot(aVector4, bVector4);

			THEN("the result is correct.")
			{
				REQUIRE(EpsilonEqual(biDot, -11.f));
				REQUIRE(EpsilonEqual(triDot, 164.f));
				REQUIRE(EpsilonEqual(quadDot, 830.f));
			}
		}

		WHEN("we dot a vector by itself and compute the squared length")
		{
			const float biSelf = Dot(aVector2, aVector2);
			const float triSelf = Dot(aVector3, aVector3);
			const float quadSelf = Dot(aVector4, aVector4);

			THEN("the result is comparable with the length squared.")
			{
				REQUIRE(EpsilonEqual(biSelf, GetLengthSquared(aVector2)));
				REQUIRE(EpsilonEqual(triSelf, GetLengthSquared(aVector3)));
				REQUIRE(EpsilonEqual(quadSelf, GetLengthSquared(aVector4)));
			}
		}

		WHEN("we compute the lenght of a vector")
		{
			const float biLength = GetLength(aVector2);
			const float triLength = GetLength(aVector3);
			const float quadLength = GetLength(aVector4);

			THEN("the result is comparable with the squared root of the length squared")
			{
				REQUIRE(EpsilonEqual(biLength, std::sqrt(GetLengthSquared(aVector2))));
				REQUIRE(EpsilonEqual(triLength, std::sqrt(GetLengthSquared(aVector3))));
				REQUIRE(EpsilonEqual(quadLength, std::sqrt(GetLengthSquared(aVector4))));
			}
		}
	}

	GIVEN("Tri-dimensional axises")
	{
		constexpr Vector3f axisI = Vector3f::GetAxisI();
		constexpr Vector3f axisJ = Vector3f::GetAxisJ();
		constexpr Vector3f axisK = Vector3f::GetAxisK();

		WHEN("We compute their cross product")
		{
			constexpr Vector3f IxJ = Cross(axisI, axisJ);
			constexpr Vector3f JxK = Cross(axisJ, axisK);
			constexpr Vector3f KxI = Cross(axisK, axisI);

			THEN("Each result corresponds to an axis in a right-handed system")
			{
				REQUIRE(EpsilonEqual(IxJ, Vector3f::GetAxisK()));
				REQUIRE(EpsilonEqual(JxK, Vector3f::GetAxisI()));
				REQUIRE(EpsilonEqual(KxI, Vector3f::GetAxisJ()));
			}
		}
	}
}

SCENARIO("Vector operators work as expected", VectorsTag)
{
	using namespace lazye;

	GIVEN("A set of supported vectors")
	{
		Vector2f aVector2(1, 2);
		Vector3f aVector3(-3, -4, -5);
		Vector4f aVector4(6, -7, 8, -9);

		THEN("each vector is identical to itself")
		{
			REQUIRE(aVector2 == aVector2);
			REQUIRE(aVector3 == aVector3);
			REQUIRE(aVector4 == aVector4);
		}

		AND_THEN("scaling can be performed by both sides")
		{
			REQUIRE(EpsilonEqual(aVector2, 1 * aVector2 * 1));
			REQUIRE(EpsilonEqual(aVector3, 1 * aVector3 * 1));
			REQUIRE(EpsilonEqual(aVector4, 1 * aVector4 * 1));
		}

		WHEN("we negate them")
		{
			Vector2f nVector2 = -aVector2;
			Vector3f nVector3 = -aVector3;
			Vector4f nVector4 = -aVector4;

			THEN("each member is the opposite of the original")
			{
				REQUIRE(aVector2[0] == -nVector2[0]);
				REQUIRE(aVector2[1] == -nVector2[1]);

				REQUIRE(aVector3[0] == -nVector3[0]);
				REQUIRE(aVector3[1] == -nVector3[1]);
				REQUIRE(aVector3[2] == -nVector3[2]);

				REQUIRE(aVector4[0] == -nVector4[0]);
				REQUIRE(aVector4[1] == -nVector4[1]);
				REQUIRE(aVector4[2] == -nVector4[2]);
				REQUIRE(aVector4[3] == -nVector4[3]);
			}
		}

		WHEN("we multiply them by a constant")
		{
			Vector2f mVector2 = aVector2 * 2;
			Vector3f mVector3 = aVector3 * 3;
			Vector4f mVector4 = aVector4 * 4;

			THEN("the resulting vectors are correctly scaled")
			{
				REQUIRE(mVector2[0] == aVector2[0] * 2);
				REQUIRE(mVector2[1] == aVector2[1] * 2);

				REQUIRE(mVector3[0] == aVector3[0] * 3);
				REQUIRE(mVector3[1] == aVector3[1] * 3);
				REQUIRE(mVector3[2] == aVector3[2] * 3);

				REQUIRE(mVector4[0] == aVector4[0] * 4);
				REQUIRE(mVector4[1] == aVector4[1] * 4);
				REQUIRE(mVector4[2] == aVector4[2] * 4);
				REQUIRE(mVector4[3] == aVector4[3] * 4);
			}
			AND_THEN("the results are comparable with dividing by the inverse")
			{
				REQUIRE(EpsilonEqual( mVector2, aVector2 / (1 / 2.f) ));
				REQUIRE(EpsilonEqual( mVector3, aVector3 / (1 / 3.f) ));
				REQUIRE(EpsilonEqual( mVector4, aVector4 / (1 / 4.f) ));
			}
			AND_THEN("division is idempotent")
			{
				REQUIRE(EpsilonEqual(aVector2, mVector2 / 2));
				REQUIRE(EpsilonEqual(aVector3, mVector3 / 3));
				REQUIRE(EpsilonEqual(aVector4, mVector4 / 4));
			}
		}

		WHEN("we divide them by a constant")
		{
			Vector2f mVector2 = aVector2 / 2;
			Vector3f mVector3 = aVector3 / 3;
			Vector4f mVector4 = aVector4 / 4;

			THEN("the resulting vectors are correctly scaled")
			{
				REQUIRE(EpsilonEqual(mVector2[0], aVector2[0] / 2));
				REQUIRE(EpsilonEqual(mVector2[1], aVector2[1] / 2));

				REQUIRE(EpsilonEqual(mVector3[0], aVector3[0] / 3));
				REQUIRE(EpsilonEqual(mVector3[1], aVector3[1] / 3));
				REQUIRE(EpsilonEqual(mVector3[2], aVector3[2] / 3));

				REQUIRE(EpsilonEqual(mVector4[0], aVector4[0] / 4));
				REQUIRE(EpsilonEqual(mVector4[1], aVector4[1] / 4));
				REQUIRE(EpsilonEqual(mVector4[2], aVector4[2] / 4));
				REQUIRE(EpsilonEqual(mVector4[3], aVector4[3] / 4));
			}
			AND_THEN("the results are comparable with multiplying by the inverse")
			{
				REQUIRE(EpsilonEqual(mVector2, aVector2 * (1 / 2.f)));
				REQUIRE(EpsilonEqual(mVector3, aVector3 * (1 / 3.f)));
				REQUIRE(EpsilonEqual(mVector4, aVector4 * (1 / 4.f)));
			}
			AND_THEN("multiplication is idempotent")
			{
				REQUIRE(EpsilonEqual(aVector2, mVector2 * 2));
				REQUIRE(EpsilonEqual(aVector3, mVector3 * 3));
				REQUIRE(EpsilonEqual(aVector4, mVector4 * 4));
			}
		}

		WHEN("we normalize them")
		{
			Vector2f nVector2 = GetNormalized(aVector2);
			Vector3f nVector3 = GetNormalized(aVector3);
			Vector4f nVector4 = GetNormalized(aVector4);

			THEN("their length is approximatively unitary")
			{
				REQUIRE(EpsilonEqual(GetLength(nVector2), 1.f));
				REQUIRE(EpsilonEqual(GetLength(nVector3), 1.f));
				REQUIRE(EpsilonEqual(GetLength(nVector4), 1.f));
			}
			AND_THEN("multiplying them by the original's length restores the original vector")
			{
				REQUIRE(EpsilonEqual(nVector2 * GetLength(aVector2), aVector2));
				REQUIRE(EpsilonEqual(nVector3 * GetLength(aVector3), aVector3));
				REQUIRE(EpsilonEqual(nVector4 * GetLength(aVector4), aVector4));
			}
		}

		AND_GIVEN("other vectors of the same dimension")
		{
			Vector2f bVector2(-10, -11);
			Vector3f bVector3(12, 13, 14);
			Vector4f bVector4(15, -16, 17, -18);

			WHEN("we add them to one another")
			{
				Vector2f sVector2 = aVector2 + bVector2;
				Vector3f sVector3 = aVector3 + bVector3;
				Vector4f sVector4 = aVector4 + bVector4;

				THEN("the result's components are the sum of the originals")
				{
					REQUIRE(sVector2[0] == aVector2[0] + bVector2[0]);
					REQUIRE(sVector2[1] == aVector2[1] + bVector2[1]);

					REQUIRE(sVector3[0] == aVector3[0] + bVector3[0]);
					REQUIRE(sVector3[1] == aVector3[1] + bVector3[1]);
					REQUIRE(sVector3[2] == aVector3[2] + bVector3[2]);

					REQUIRE(sVector4[0] == aVector4[0] + bVector4[0]);
					REQUIRE(sVector4[1] == aVector4[1] + bVector4[1]);
					REQUIRE(sVector4[2] == aVector4[2] + bVector4[2]);
					REQUIRE(sVector4[3] == aVector4[3] + bVector4[3]);
				}

				AND_THEN("the sum is commutative")
				{
					REQUIRE(EpsilonEqual(aVector2 + bVector2, bVector2 + aVector2));
					REQUIRE(EpsilonEqual(aVector3 + bVector3, bVector3 + aVector3));
					REQUIRE(EpsilonEqual(aVector4 + bVector4, bVector4 + aVector4));
				}
			}

			WHEN("we subtract them to one another")
			{
				Vector2f sVector2 = aVector2 - bVector2;
				Vector3f sVector3 = aVector3 - bVector3;
				Vector4f sVector4 = aVector4 - bVector4;

				THEN("the result's components are the subtraction of the originals")
				{
					REQUIRE(sVector2[0] == aVector2[0] - bVector2[0]);
					REQUIRE(sVector2[1] == aVector2[1] - bVector2[1]);

					REQUIRE(sVector3[0] == aVector3[0] - bVector3[0]);
					REQUIRE(sVector3[1] == aVector3[1] - bVector3[1]);
					REQUIRE(sVector3[2] == aVector3[2] - bVector3[2]);

					REQUIRE(sVector4[0] == aVector4[0] - bVector4[0]);
					REQUIRE(sVector4[1] == aVector4[1] - bVector4[1]);
					REQUIRE(sVector4[2] == aVector4[2] - bVector4[2]);
					REQUIRE(sVector4[3] == aVector4[3] - bVector4[3]);
				}

				AND_THEN("the subtraction is anti-commutative")
				{
					REQUIRE(EpsilonEqual( aVector2 - bVector2, -(bVector2 - aVector2) ));
					REQUIRE(EpsilonEqual( aVector3 - bVector3, -(bVector3 - aVector3) ));
					REQUIRE(EpsilonEqual( aVector4 - bVector4, -(bVector4 - aVector4) ));
				}
			}

			WHEN("we subtract and add the same vector")
			{
				THEN("the result doesn't change")
				{
					REQUIRE(EpsilonEqual(aVector2, aVector2 - bVector2 + bVector2));
					REQUIRE(EpsilonEqual(aVector3, aVector3 - bVector3 + bVector3));
					REQUIRE(EpsilonEqual(aVector4, aVector4 - bVector4 + bVector4));
				}
			}
		}
	}
}