#include <array>
#include <algorithm>
#include <type_traits>

namespace lazye
{
	template<typename V>
	auto GetLengthSquared(const V& v1, const V& v2)
	{
		V::Type dot = 0;

		auto it1 = v1.cbegin();
		auto it2 = v2.cbegin();
		auto end = v1.cend();
		for ( ; it1 != end; it1++, it2++) 
		{
			dot += (*it1) * (*it2);
		}

		return dot;
	}

	template<typename V>
	auto GetLength(const V& v)
	{
		return std::sqrt(GetLengthSquared(v, v));
	}

	template<
		std::size_t D, typename T = float,
		std::enable_if_t<std::is_arithmetic_v<T>, bool> = 0,
		std::enable_if_t<(D > 1) && (D <= 4), bool> = 0
	>
	class Vector
	{
	public:
		using Type = T;

		Vector()
		{
			m_Data.fill(T(0));
		}

		template<std::size_t S = D, typename std::enable_if_t<(S == 2), bool> = 0>
		Vector(T x, T y)
		{
			m_Data[0] = x;
			m_Data[1] = y;
		}

		template<std::size_t S = D, typename std::enable_if_t<(S == 3), bool> = 0>
		Vector(T x, T y, T z)
		{
			m_Data[0] = x;
			m_Data[1] = y;
			m_Data[2] = z;
		}

		template<std::size_t S = D, typename std::enable_if_t<(S == 4), bool> = 0>
		Vector(T x, T y, T z, T w)
		{
			m_Data[0] = x;
			m_Data[1] = y;
			m_Data[2] = z;
			m_Data[3] = w;
		}

		inline const T& operator[] (std::size_t i) const { return m_Data[i]; }
		inline T& operator[] (std::size_t i) { return m_Data[i]; }

		inline auto begin() { return m_Data.begin(); }
		inline auto end() { return m_Data.end(); }
		inline auto cbegin() const { return m_Data.cbegin(); }
		inline auto cend() const { return m_Data.cend(); }

		inline const std::size_t Dimension() const { return D; }

	private:
		std::array<T, D> m_Data;
	};

	using Vector2f = Vector<2>;
	using Vector3f = Vector<3>;
	using Vector4f = Vector<4>;
}