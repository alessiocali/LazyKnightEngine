#pragma once

#include <type_traits>
#include <cstring>

#include <lazye/math/vectors.h>

namespace lazye
{
    /**
     *  A bidimensional Matrix implementation.
     *
     *  @param <T>:     The underlying type of the Matrix
     *  @param <M>:     The number of rows of the Matrix
     *  @param <N>:     The number of columns of the Matrix
     */
    template<
        typename T, std::size_t M, std::size_t N,
        std::enable_if_t<std::is_floating_point_v<T>, bool> = false,
        std::enable_if_t<(M > 1 && N > 1 && M < 5 && N < 5), bool> = false
    >
    class Matrix
    {
    public:
        using MatrixType = Matrix<T, M, N>;

        Matrix() { std::memset(m_Data, T(0), M * N * sizeof(T)); }
        Matrix(const T(&list)[N * M]) { std::memcpy(m_Data, list, N * M * sizeof(T)); }

        static MatrixType GetZero() { return MatrixType(); }
        
        template<std::enable_if_t<M == N, bool> = false>
        static MatrixType GetIdentity()
        {
            MatrixType result = MatrixType::GetZero();
            for (std::size_t i = 0; i < N; i++)
            {
                result(i, i) = T(1);
            }
            return result;
        }

        inline const T* GetDataPtr() const { return m_Data; }

        inline T& operator()(std::size_t i, std::size_t j) { return m_Data[i * N + j]; }
        inline const T& operator()(std::size_t i, std::size_t j) const { return m_Data[i * N + j]; }

    private:
        T m_Data[M * N];
    };

    using Matrix44f = Matrix<float, 4, 4>;
    using Matrix33f = Matrix<float, 3, 3>;
    using Matrix22f = Matrix<float, 2, 2>;
}