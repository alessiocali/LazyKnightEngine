#pragma once

#include <type_traits>
#include <array>
#include <cstdint>

namespace lazye
{
    template<
        std::size_t D, typename T,
        std::enable_if_t<std::is_arithmetic_v<T>, bool> = false,
        std::enable_if_t<(D > 1) && (D <= 4), bool> = false
	>
    class Vector
	{
	public:
		using Type = T;

		constexpr Vector() : m_Data { T(0) }
		{ }

		constexpr Vector(const Vector<D, T>& original) : m_Data { original.m_Data }
		{ }

		constexpr Vector(Vector<D, T>&& other) : m_Data(std::move(other.m_Data))
		{ }

		template<std::size_t S = D, typename std::enable_if_t<(S == 2), bool> = 0>
		constexpr Vector(T x, T y) : m_Data { x, y }
		{ }

		template<std::size_t S = D, typename std::enable_if_t<(S == 3), bool> = 0>
		constexpr Vector(T x, T y, T z) : m_Data { x, y, z }
		{ }

		template<std::size_t S = D, typename std::enable_if_t<(S == 4), bool> = 0>
		constexpr Vector(T x, T y, T z, T w) : m_Data { x, y, z, w }
		{ }

		constexpr Vector<D, T>& operator=(const Vector<D, T>& other)
		{
			if (this != &other)
			{
				m_Data = other.m_Data;
			}

			return *this;
		}

		constexpr Vector<D, T>& operator=(Vector<D, T>&& other)
		{
			if (this != &other)
			{
				m_Data = std::move(other.m_Data);
			}

			return *this;
		}

		inline constexpr const T& operator[] (std::size_t i) const { return m_Data[i]; }
		inline constexpr T& operator[] (std::size_t i) { return m_Data[i]; }

		inline constexpr const T* GetDataPtr() const { return m_Data.data(); }

		inline constexpr std::size_t Dimension() const { return D; }

		static constexpr Vector<D, T> GetZero() { return Vector<D, T>(); }

		static constexpr Vector<D, T> GetAxisI() { return GetAxis<0>(); }
		static constexpr Vector<D, T> GetAxisJ() { return GetAxis<1>(); }
		static constexpr Vector<D, T> GetAxisK() { return GetAxis<2>(); }
		static constexpr Vector<D, T> GetAxisL() { return GetAxis<3>(); }

	private:
		std::array<T, D> m_Data;

		template<std::size_t Idx, std::enable_if_t<(Idx < D), bool> = 0>
		static constexpr Vector<D, T> GetAxis()
		{
			Vector<D, T> axis;
			axis[Idx] = T(1);
			return axis;
		}
	};

	using Vector2ui = Vector<2, unsigned int>;
	using Vector3ui = Vector<3, unsigned int>;
	using Vector4ui = Vector<4, unsigned int>;

	using Vector2i = Vector<2, int>;
	using Vector3i = Vector<3, int>;
	using Vector4i = Vector<4, int>;

	using Vector2f = Vector<2, float>;
	using Vector3f = Vector<3, float>;
	using Vector4f = Vector<4, float>;
}