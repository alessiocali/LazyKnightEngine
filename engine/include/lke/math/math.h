#pragma once
#include <lke/lke.h>

#include <algorithm>
#include <type_traits>

#include <lke/math/vectors.h>
#include <lke/math/matrix.h>

namespace lke
{
    class Quaternion;

	template<typename T, std::enable_if_t<std::is_arithmetic_v<T>, bool> = 0>
	constexpr T SquareOf(T val)
	{
		return val * val;
	}

	template<typename T, std::enable_if_t<std::is_arithmetic_v<T>, bool> = 0>
	T Sqrt(T val)
	{
		return std::sqrt(val);
	}

	// Implementation from this thread
	// https://stackoverflow.com/a/15012792
	template<typename T, std::enable_if_t<std::is_arithmetic_v<T>, bool> = 0>
	constexpr bool EpsilonEqual(const T& t1, const T& t2, T epsilon = std::numeric_limits<T>::epsilon())
	{
		auto scale = std::max({ T(1), std::abs(t1), std::abs(t2) });
		return std::abs(t1 - t2) <= epsilon * scale;
	}

	template<typename T>
	constexpr bool EpsilonNotEqual(const T& t1, const T& t2, T epsilon = std::numeric_limits<T>::epsilon())
	{
		return !EpsilonEqual(t1, t2, epsilon);
	}

	template<typename T>
	constexpr bool EpsilonNull(const T& t)
	{
		return EpsilonEqual(t, T());
	}

	lkedll float Sin(Radians angle);
	lkedll float Cos(Radians angle);

    template<std::size_t D, typename T>
    constexpr auto Dot(const Vector<D, T>& v1, const Vector<D, T>& v2)
    {
        auto dot = v1[0] * v2[0];
        for (std::size_t i = 1; i < D; i++)
        {
            dot += v1[i] * v2[i];
        }
        return dot;
    }

    template<typename T>
    constexpr Vector<3, T> Cross(const Vector<3, T>& v1, const Vector<3, T>& v2)
    {
        const T x = v1[1] * v2[2] - v1[2] * v2[1];
        const T y = v1[2] * v2[0] - v1[0] * v2[2];
        const T z = v1[0] * v2[1] - v2[0] * v1[1];
        return Vector<3, T>(x, y, z);
    }

    template<std::size_t D, typename T>
    constexpr auto GetLengthSquared(const Vector<D, T>& v)
    {
        return Dot(v, v);
    }

    template<std::size_t D, typename T>
    constexpr auto GetLength(const Vector<D, T>& v)
    {
        return std::sqrt(GetLengthSquared(v));
    }

    template<std::size_t D, typename T>
    constexpr Vector<D, T> GetNormalized(const Vector<D, T>& v)
    {
        return v / GetLength(v);
    }

    template<std::size_t D, typename T>
    constexpr bool IsNormalized(const Vector<D, T>& v)
    {
        return EpsilonEqual(GetLengthSquared(v), 1.f);
    }

    template<std::size_t D, typename T>
    constexpr bool EpsilonEqual(const Vector<D, T>& v1, const Vector<D, T>& v2, T epsilon = std::numeric_limits<T>::epsilon())
    {
        for (std::size_t i = 0; i < D; i++)
        {
            if (EpsilonNotEqual(v1[i], v2[i], epsilon))
            {
                return false;
            }
        }
        return true;
    }

    template<typename T, std::size_t M, std::size_t N>
    constexpr bool EpsilonEqual(const Matrix<T, M, N>& m1, const Matrix<T, M, N>& m2, T epsilon = std::numeric_limits<T>::epsilon())
    {
        for (std::size_t i = 0; i < M; i++)
        {
            for (std::size_t j = 0; j < N; j++)
            {
                if (EpsilonNotEqual(m1(i, j), m2(i, j), epsilon))
                {
                    return false;
                }
            }
        }
        return true;
    }

    template<typename Mul, std::size_t D, typename T>
    inline constexpr Vector<D, T> operator*(const Vector<D, T>& v, Mul m)
    {
        Vector<D, T> scaledVector;
        for (std::size_t i = 0; i < D; i++)
        {
            scaledVector[i] = v[i] * m;
        }
        return scaledVector;
    }

    template<typename Mul, std::size_t D, typename T>
    constexpr Vector<D, T> operator*(Mul m, const Vector<D, T>& v)
    {
        return v * m;
    }

    template<typename Div, std::size_t D, typename T>
    inline constexpr Vector<D, T> operator/(const Vector<D, T>& v, Div d)
    {
        return v * (T(1) / T(d));
    }

    template<std::size_t D, typename T>
    inline constexpr Vector<D, T> operator+(const Vector<D, T>& a, const Vector<D, T>& b)
    {
        Vector<D, T> addedVector;
        for (std::size_t i = 0; i < D; i++)
        {
            addedVector[i] = a[i] + b[i];
        }
        return addedVector;
    }

    template<std::size_t D, typename T>
    inline constexpr Vector<D, T> operator-(const Vector<D, T>& v)
    {
        Vector<D, T> negative;
        for (std::size_t i = 0; i < D; i++)
        {
            negative[i] = -v[i];
        }
        return negative;
    }

    template<std::size_t D, typename T>
    inline constexpr bool operator==(const Vector<D, T>& vec, const Vector<D, T>& other)
    {
        for (std::size_t i = 0; i < D; i++)
        {
            if (vec[i] != other[i])
            {
                return false;
            }
        }
        return true;
    }

    template<std::size_t D, typename T>
    inline constexpr Vector<D, T> operator-(const Vector<D, T>& vec, const Vector<D, T>& other)
    {
        Vector<D, T> diff;
        for (std::size_t i = 0; i < D; i++)
        {
            diff[i] = vec[i] - other[i];
        }
        return diff;
    }

    template<typename T, std::size_t M, std::size_t N>
    Matrix<T, M, N> operator-(const Matrix<T, M, N>& m)
    {
        Matrix<T, M, N> negate;
        for (std::size_t i = 0; i < M; i++)
        {
            for (std::size_t j = 0; j < N; j++)
            {
                negate(i, j) = -m(i, j);
            }
        }
        return negate;
    }

    template<typename T, std::size_t M, std::size_t N>
    Matrix<T, M, N> operator+(const Matrix<T, M, N>& m1, const Matrix<T, M, N>& m2)
    {
        Matrix<T, M, N> sum;
        for (std::size_t i = 0; i < M; i++)
        {
            for (std::size_t j = 0; j < N; j++)
            {
                sum(i, j) = m1(i, j) + m2(i, j);
            }
        }
        return sum;
    }

    template<typename T, std::size_t M, std::size_t N>
    Matrix<T, M, N> operator-(const Matrix<T, M, N>& m1, const Matrix<T, M, N>& m2)
    {
        Matrix<T, M, N> diff;
        for (std::size_t i = 0; i < M; i++)
        {
            for (std::size_t j = 0; j < N; j++)
            {
                diff(i, j) = m1(i, j) - m2(i, j);
            }
        }
        return diff;
    }

    template<typename T, std::size_t M, std::size_t N>
    bool operator==(const Matrix<T, M, N>& m1, const Matrix<T, M, N>& m2)
    {
        for (std::size_t i = 0; i < M; i++)
        {
            for (std::size_t j = 0; j < N; j++)
            {
                if (m1(i, j) != m2(i, j))
                {
                    return false;
                }
            }
        }
        return true;
    }

    template<typename T, std::size_t L, std::size_t M, std::size_t N>
    Matrix<T, L, N> operator*(const Matrix<T, L, M>& m1, const Matrix<T, M, N>& m2)
    {
        Matrix<T, L, N> result;
        for (std::size_t row = 0; row < L; row++)
        {
            for (std::size_t col = 0; col < N; col++)
            {
                T& element = result(row, col);
                element = T(0);
                for (std::size_t idx = 0; idx < M; idx++)
                {
                    element += m1(row, idx) * m2(idx, col);
                }
            }
        }
        return result;
    }

    template<typename T, std::size_t M, std::size_t N>
    Vector<N, T> operator*(const Matrix<T, M, N>& m, const Vector<N, T>& v)
    {
        Vector<N, T> result;
        for (std::size_t row = 0; row < M; row++)
        {
            T& element = result[row];
            element = T(0);

            for (std::size_t col = 0; col < N; col++)
            {
                element += m(row, col) * v[col];
            }
        }
        return result;
    }

    template<typename T, typename S, std::size_t M, std::size_t N>
    Matrix<T, M, N> operator*(const Matrix<T, M, N>& m, S s)
    {
        Matrix<T, M, N> result;
        const T ts = T(s);

        for (std::size_t i = 0; i < M; i++)
        {
            for (std::size_t j = 0; j < N; j++)
            {
                result(i, j) = m(i, j) * ts;
            }
        }

        return result;
    }

    template<typename T, typename S, std::size_t M, std::size_t N>
    Matrix<T, M, N> operator*(S s, const Matrix<T, M, N>& m)
    {
        return m * s;
    }

    template<typename T, typename S, std::size_t M, std::size_t N>
    Matrix<T, M, N> operator/(const Matrix<T, M, N>& m, S s)
    {
        return m * (T(1) / T(s));
    }

    template<typename T, std::size_t M, std::size_t N>
    Matrix<T, N, M> GetTranspose(const Matrix<T, M, N>& m)
    {
        Matrix<T, N, M> transpose;
        for (std::size_t i = 0; i < M; i++)
        {
            for (std::size_t j = 0; j < N; j++)
            {
                transpose(j, i) = m(i, j);
            }
        }
        return transpose;
    }

    template<typename T>
    Matrix<T, 2, 2> GetInverse(const Matrix<T, 2, 2>& m)
    {
        Matrix<T, 2, 2> inverse;

        const T idet = T(1) / ( m(0, 0) * m(1, 1) - m(0, 1) * m(1, 0) );

        inverse(0, 0) =  m(1, 1) * idet;
        inverse(0, 1) = -m(0, 1) * idet;
        inverse(1, 0) = -m(1, 0) * idet;
        inverse(1, 1) =  m(0, 0) * idet;

        return inverse;
    }

    template<typename T>
    Matrix<T, 3, 3> GetInverse(const Matrix<T, 3, 3>& m)
    {
        Matrix<T, 3, 3> inverse;

        const T a00 = m(1, 1) * m(2, 2) - m(1, 2) * m(2, 1);
        const T a01 = m(1, 0) * m(2, 2) - m(1, 2) * m(2, 0);
        const T a02 = m(1, 0) * m(2, 1) - m(1, 1) * m(2, 0);

        const T a10 = m(0, 1) * m(2, 2) - m(0, 2) * m(2, 1);
        const T a11 = m(0, 0) * m(2, 2) - m(0, 2) * m(2, 0);
        const T a12 = m(0, 0) * m(2, 1) - m(0, 1) * m(2, 0);

        const T a20 = m(0, 1) * m(1, 2) - m(0, 2) * m(1, 1);
        const T a21 = m(0, 0) * m(1, 2) - m(0, 2) * m(1, 0);
        const T a22 = m(0, 0) * m(1, 1) - m(0, 1) * m(1, 0);

        const T idet = T(1) / ( m(0, 0) * a00 - m(0, 1) * a01 + m(0, 2) * a02 );

        inverse(0, 0) =  a00 * idet;
        inverse(0, 1) = -a10 * idet;
        inverse(0, 2) =  a20 * idet;
        
        inverse(1, 0) = -a01 * idet;
        inverse(1, 1) =  a11 * idet;
        inverse(1, 2) = -a21 * idet;

        inverse(2, 0) =  a02 * idet;
        inverse(2, 1) = -a12 * idet;
        inverse(2, 2) =  a22 * idet;

        return inverse;
    }

    template<typename T>
    Matrix<T, 4, 4> GetInverse(const Matrix<T, 4, 4>& m)
    {
        // All praise stack overflow
        // https://stackoverflow.com/questions/2624422/efficient-4x4-matrix-inverse-affine-transform
    
        Matrix<T, 4, 4> inverse;
        
        const T s0 = m(0, 0) * m(1, 1) - m(1, 0) * m(0, 1);
        const T s1 = m(0, 0) * m(1, 2) - m(1, 0) * m(0, 2);
        const T s2 = m(0, 0) * m(1, 3) - m(1, 0) * m(0, 3);
        const T s3 = m(0, 1) * m(1, 2) - m(1, 1) * m(0, 2);
        const T s4 = m(0, 1) * m(1, 3) - m(1, 1) * m(0, 3);
        const T s5 = m(0, 2) * m(1, 3) - m(1, 2) * m(0, 3);

        const T c5 = m(2, 2) * m(3, 3) - m(3, 2) * m(2, 3);
        const T c4 = m(2, 1) * m(3, 3) - m(3, 1) * m(2, 3);
        const T c3 = m(2, 1) * m(3, 2) - m(3, 1) * m(2, 2);
        const T c2 = m(2, 0) * m(3, 3) - m(3, 0) * m(2, 3);
        const T c1 = m(2, 0) * m(3, 2) - m(3, 0) * m(2, 2);
        const T c0 = m(2, 0) * m(3, 1) - m(3, 0) * m(2, 1);

        // Affine transforms are always invertible, to not waste a check I'll 
        // directly divide If the transform is not affine, either we have bigger 
        // problems or the matrix is being used improperly
        const T idet = T(1) / (s0 * c5 - s1 * c4 + s2 * c3 + s3 * c2 - s4 * c1 + s5 * c0);

        inverse(0, 0) = ( m(1, 1) * c5 - m(1, 2) * c4 + m(1, 3) * c3) * idet;
        inverse(0, 1) = (-m(0, 1) * c5 + m(0, 2) * c4 - m(0, 3) * c3) * idet;
        inverse(0, 2) = ( m(3, 1) * s5 - m(3, 2) * s4 + m(3, 3) * s3) * idet;
        inverse(0, 3) = (-m(2, 1) * s5 + m(2, 2) * s4 - m(2, 3) * s3) * idet;

        inverse(1, 0) = (-m(1, 0) * c5 + m(1, 2) * c2 - m(1, 3) * c1) * idet;
        inverse(1, 1) = ( m(0, 0) * c5 - m(0, 2) * c2 + m(0, 3) * c1) * idet;
        inverse(1, 2) = (-m(3, 0) * s5 + m(3, 2) * s2 - m(3, 3) * s1) * idet;
        inverse(1, 3) = ( m(2, 0) * s5 - m(2, 2) * s2 + m(2, 3) * s1) * idet;

        inverse(2, 0) = ( m(1, 0) * c4 - m(1, 1) * c2 + m(1, 3) * c0) * idet;
        inverse(2, 1) = (-m(0, 0) * c4 + m(0, 1) * c2 - m(0, 3) * c0) * idet;
        inverse(2, 2) = ( m(3, 0) * s4 - m(3, 1) * s2 + m(3, 3) * s0) * idet;
        inverse(2, 3) = (-m(2, 0) * s4 + m(2, 1) * s2 - m(2, 3) * s0) * idet;

        inverse(3, 0) = (-m(1, 0) * c3 + m(1, 1) * c1 - m(1, 2) * c0) * idet;
        inverse(3, 1) = ( m(0, 0) * c3 - m(0, 1) * c1 + m(0, 2) * c0) * idet;
        inverse(3, 2) = (-m(3, 0) * s3 + m(3, 1) * s1 - m(3, 2) * s0) * idet;
        inverse(3, 3) = ( m(2, 0) * s3 - m(2, 1) * s1 + m(2, 2) * s0) * idet;

        return inverse;
    }

    lkedll void SetToTranslationMatrix(Matrix44f& targetMatrix, const Vector3f translation);
    lkedll void SetToRotationMatrix(Matrix44f& targetMatrix, const Quaternion& quaternion);
    lkedll void SetToScalingMatrix(Matrix44f& targetMatrix, const Vector3f scaling);
}