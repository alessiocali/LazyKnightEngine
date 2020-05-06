#pragma once

#include <type_traits>
#include <array>
#include <cstdint>

#include <math.h>

namespace lazye
{
	template<
		std::size_t D, typename T = float,
		std::enable_if_t<std::is_arithmetic_v<T>, bool> = 0,
		std::enable_if_t<(D > 1) && (D <= 4), bool> = 0
	>
	class Vector;

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
		T x = v1[1] * v2[2] - v1[2] * v2[1];
		T y = v1[2] * v2[0] - v1[0] * v2[2];
		T z = v1[0] * v2[1] - v2[0] * v1[1];
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
	constexpr bool EpsilonEqual(const Vector<D, T>& v1, const Vector<D, T>& v2)
	{
		for (std::size_t i = 0 ; i < D ; i++)
		{
			if (EpsilonNotEqual(v1[i], v2[i]))
			{
				return false;
			}
		}
		return true;
	}

	template<typename Mul, std::size_t D, typename T>
	constexpr Vector<D, T> operator*(Mul m, const Vector<D, T>& v)
	{
		return v * m;
	}

	template<typename Div, std::size_t D, typename T>
	constexpr Vector<D, T> operator/(Div d, const Vector<D, T>& v)
	{
		return v / d;
	}

    template<
        std::size_t D, typename T,
        std::enable_if_t<std::is_arithmetic_v<T>, bool>,
        std::enable_if_t<(D > 1) && (D <= 4), bool>
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

		template<typename Mul>
		inline constexpr Vector<D, T> operator*(Mul m) const
		{
			Vector<D, T> scaledVector;
			for (std::size_t i = 0; i < D; i++)
			{
				scaledVector[i] = m_Data[i] * m;
			}
			return scaledVector;
		}

		template<typename Div>
		inline constexpr Vector<D, T> operator/(Div d) const
		{
			return (*this) * (T(1) / T(d));
		}

		inline constexpr Vector<D, T> operator+(const Vector<D, T>& other) const
		{
			Vector<D, T> addedVector;
			for (std::size_t i = 0; i < D; i++)
			{
				addedVector[i] = m_Data[i] + other[i];
			}
			return addedVector;
		}

		inline constexpr Vector<D, T> operator-() const
		{
			Vector<D, T> negative;
			for (std::size_t i = 0; i < D; i++)
			{
				negative[i] = -m_Data[i];
			}
			return negative;
		}

		inline constexpr bool operator==(const Vector<D, T>& other) const
		{
			for (std::size_t i = 0; i < D; i++)
			{
				if (m_Data[i] != other[i])
				{
					return false;
				}
			}
			return true;
		}

		inline constexpr Vector<D, T> operator-(const Vector<D, T>& other) const
		{
			return (*this) + (-other);
		}

		inline constexpr const T& operator[] (std::size_t i) const { return m_Data[i]; }
		inline constexpr T& operator[] (std::size_t i) { return m_Data[i]; }

		inline constexpr std::size_t Dimension() const { return D; }

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

	using Vector2i = Vector<2, std::uint32_t>;
	using Vector3i = Vector<3, std::uint32_t>;
	using Vector4i = Vector<4, std::uint32_t>;

	using Vector2f = Vector<2, float>;
	using Vector3f = Vector<3, float>;
	using Vector4f = Vector<4, float>;
}