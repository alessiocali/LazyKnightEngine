#pragma once
#include <lazye/lazye.h>

#include <algorithm>
#include <type_traits>

namespace lazye
{
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
	constexpr bool EpsilonEqual(const T& t1, const T& t2)
	{
		auto scale = std::max({ T(1), std::abs(t1), std::abs(t2) });
		return std::abs(t1 - t2) <= std::numeric_limits<T>::epsilon() * scale;
	}

	template<typename T>
	constexpr bool EpsilonNotEqual(const T& t1, const T& t2)
	{
		return !EpsilonEqual(t1, t2);
	}

	template<typename T>
	constexpr bool EpsilonNull(const T& t)
	{
		return EpsilonEqual(t, T());
	}

	lazyedll float Sin(Radians angle);
	lazyedll float Cos(Radians angle);
}