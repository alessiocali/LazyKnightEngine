#pragma once

#include <algorithm>
#include <type_traits>

#include <lazye/math/vectors.h>

namespace lazye
{
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
}