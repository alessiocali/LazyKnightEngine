#pragma once

#include <type_traits>
#include <cstring>

namespace lazye
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
    public:
        using MatrixType = Matrix<T, M, N>;

        Matrix() { std::fill(m_Data, m_Data + M * N, T(0)); }
        Matrix(const T(&list)[N * M]) { std::memcpy(m_Data, list, N * M * sizeof(T)); }

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