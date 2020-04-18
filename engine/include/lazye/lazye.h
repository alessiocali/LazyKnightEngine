#pragma once

#include <lazye/math/math.h>
#include <lazye/math/vectors.h>
#include <lazye/math/physic_units.h>
#include <lazye/asserts.h>

#ifdef LAZYE_STATIC
	#define lazyedll
#else
	#ifdef LAZYE_EXPORTS
		#define lazyedll __declspec(dllexport)
	#else
		#define lazyedll __declspec(dllimport)
	#endif // LAZYE_EXPORTS

	// This will trigger everytime it hits a STL container in a dll class - even if it's private
	#ifdef _MSC_VER
		#pragma warning(disable: 4251)
	#endif

#endif // LAZYE_STATIC
