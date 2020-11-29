#pragma once

#include <type_traits>
#include <cstring>
#include <array>

namespace lke
{
    /**
     *  A bidimensional Matrix implementation. Values are accessed in row-major
     *  order (operator() accepts (row, col)).
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
    private:
        using MatrixType = Matrix<T, M, N>;
        using ArrayType = std::array<T, M * N>;

    public:
        using ValueType = T;

        inline static constexpr std::size_t Size = N * M;
        inline static constexpr std::size_t RowCount = M;
        inline static constexpr std::size_t ColCount = N;

        Matrix() { m_Data.fill(T(0)); }
        Matrix(const ArrayType& array) : m_Data(array) { }

        static const MatrixType& GetZero()
        {
            static MatrixType s_Zero;
            return s_Zero;
        }

        template<std::enable_if_t<M == N, bool> = false>
        static const MatrixType& GetIdentity()
        {
            static bool s_Init = false;
            static MatrixType s_Identity = MatrixType::GetZero();

            if (!s_Init)
            {
                for (std::size_t i = 0; i < N; i++)
                {
                    s_Identity(i, i) = T(1);
                }

                s_Init = true;
            }

            return s_Identity;
        }

        inline const T* GetDataPtr() const { return m_Data.data(); }

        inline T& operator()(std::size_t i, std::size_t j) { return m_Data[i * N + j]; }
        inline const T& operator()(std::size_t i, std::size_t j) const { return m_Data[i * N + j]; }

    private:
        ArrayType m_Data;
    };

    using Matrix44f = Matrix<float, 4, 4>;
    using Matrix33f = Matrix<float, 3, 3>;
    using Matrix22f = Matrix<float, 2, 2>;
}