#include <catch2/catch.hpp>
#include <lke/math/math.h>
#include <lke/math/matrix.h>

constexpr const char* MatrixTag = "[matrix]";

SCENARIO("Matrices are correctly constructed and initialized", MatrixTag)
{
    using namespace lke;

    GIVEN("A null matrix")
    {
        const Matrix44f null = Matrix44f::GetZero();

        THEN("Their its values are all 0s")
        {
            Matrix44f testMatrix(
            {
                0.f, 0.f, 0.f, 0.f,
                0.f, 0.f, 0.f, 0.f,
                0.f, 0.f, 0.f, 0.f,
                0.f, 0.f, 0.f, 0.f
            });

            REQUIRE(EpsilonEqual(null, testMatrix));
        }
    }

    GIVEN("An identity matrix")
    {
        const Matrix44f identity = Matrix44f::GetIdentity();

        THEN("All its values are 0s except the diagonal")
        {
            Matrix44f testMatrix(
            {
                1.f, 0.f, 0.f, 0.f,
                0.f, 1.f, 0.f, 0.f,
                0.f, 0.f, 1.f, 0.f,
                0.f, 0.f, 0.f, 1.f,
            });

            REQUIRE(EpsilonEqual(identity, testMatrix));
        }
    }

    GIVEN("A generic 2x2 matrix")
    {
        const Matrix22f matrix({ 1.f, 2.f, 3.f, 4.f });

        THEN("Its values are correctly initialized")
        {
            REQUIRE(matrix(0, 0) == 1.f);
            REQUIRE(matrix(0, 1) == 2.f);
            REQUIRE(matrix(1, 0) == 3.f);
            REQUIRE(matrix(1, 1) == 4.f);
        }

        AND_THEN("Comparison with an identical matrix succeeds")
        {
            REQUIRE(matrix == Matrix22f({ 1.f, 2.f, 3.f, 4.f }));
        }

        AND_THEN("The negated matrix has all opposite components")
        {
            Matrix22f negate = -matrix;
            
            REQUIRE(negate(0, 0) == -matrix(0, 0));
            REQUIRE(negate(0, 1) == -matrix(0, 1));
            REQUIRE(negate(1, 0) == -matrix(1, 0));
            REQUIRE(negate(1, 1) == -matrix(1, 1));

            REQUIRE(EpsilonEqual(negate + matrix, Matrix22f::GetZero()));
        }

        AND_THEN("Sum of matrices work as intended")
        {
            Matrix22f testMatrix({ 5.f, 6.f, 7.f, 8.f });
            Matrix22f expectedSum({ 6.f, 8.f, 10.f, 12.f });
            Matrix22f expectedDiff({ 4.f, 4.f, 4.f, 4.f });

            REQUIRE(EpsilonEqual(testMatrix + matrix, expectedSum));
            REQUIRE(EpsilonEqual(testMatrix - matrix, expectedDiff));
            REQUIRE(EpsilonEqual(matrix - testMatrix, -(testMatrix - matrix)));
        }
        
        AND_THEN("Its inner buffer is accessible and valid")
        {
            const float* buffer = matrix.GetDataPtr();

            REQUIRE(buffer[0] == 1.f);
            REQUIRE(buffer[1] == 2.f);
            REQUIRE(buffer[2] == 3.f);
            REQUIRE(buffer[3] == 4.f);
        }

        AND_THEN("Its transpose is correctly computed")
        {
            const Matrix22f transpose = GetTranspose(matrix);
            const Matrix22f testMatrix(
            {
                1.f, 3.f,
                2.f, 4.f
            });

            REQUIRE(EpsilonEqual(transpose, testMatrix));
        }

        AND_THEN("Multiplication by another matrix works correctly")
        {
            const Matrix22f mulMatrix(
            {
                5.f, 6.f,
                7.f, 8.f
            });

            const Matrix22f testMatrix1(
            {
                19.f, 22.f,
                43.f, 50.f
            });

            const Matrix22f testMatrix2(
            {
                23.f, 34.f,
                31.f, 46.f
            });

            REQUIRE(EpsilonEqual(matrix * mulMatrix, testMatrix1));
            REQUIRE(EpsilonEqual(mulMatrix * matrix, testMatrix2));
        }

        AND_THEN("Multiplication by a vector works correctly")
        {
            const Vector2f testVector { 5.f, 6.f };
            const Vector2f expectedVector { 17.f, 39.f };
            
            REQUIRE(EpsilonEqual(matrix * testVector, expectedVector));
        }

        AND_THEN("Multiplication by a scalar works correctly")
        {
            const float mul = 10.f;
            const Matrix22f testMatrix(
            {
                10.f, 20.f,
                30.f, 40.f
            });

            REQUIRE(EpsilonEqual(mul * matrix, testMatrix));
            REQUIRE(EpsilonEqual(matrix * mul, testMatrix));
            REQUIRE(EpsilonEqual(matrix * mul, mul * matrix));
        }

        AND_THEN("Its inverse is correctly computed")
        {
            const Matrix22f inverse = GetInverse(matrix);
            const Matrix22f testMatrix(
            {
                4.f / (-2.f), -2.f / (-2.f),
                -3.f / (-2.f), 1.f / (-2.f)
            });

            REQUIRE(EpsilonEqual(inverse, testMatrix));
            REQUIRE(EpsilonEqual(inverse * matrix, Matrix22f::GetIdentity()));
        }
    }

    GIVEN("An invertible 3x3 matrix")
    {
        const Matrix33f matrix(
        {
             0.5f, -0.5f, 3.f,
            -0.5f,  1.f,  6.f,
             0.f ,  0.f,  1.f
        });

        THEN("Its inverse is correctly computed")
        {
            const Matrix33f inverse = GetInverse(matrix);

            REQUIRE(EpsilonEqual(matrix * inverse, Matrix33f::GetIdentity()));
            REQUIRE(EpsilonEqual(inverse * matrix, Matrix33f::GetIdentity()));
        }
    }

    GIVEN("An invertible 4x4 matrix")
    {
        const Matrix44f matrix(
        {
            2.f, 0.f, 0.f, 10.f,
            0.f, 1.f, 0.f, 5.f,
            0.f, 0.f, 3.f, 3.f,
            0.f, 0.f, 0.f, 1.f
        });

        THEN("Its inverse is correctly computed")
        {
            const Matrix44f inverse = GetInverse(matrix);

            REQUIRE(EpsilonEqual(matrix * inverse, Matrix44f::GetIdentity()));
            REQUIRE(EpsilonEqual(inverse * matrix, Matrix44f::GetIdentity()));
        }
    }
};