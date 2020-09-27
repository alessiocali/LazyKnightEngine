#pragma once

#ifdef LAZYKNIGHT_STATIC
	#define lkedll
#else
	#ifdef LAZYKNIGHT_EXPORTS
		#define lkedll __declspec(dllexport)
	#else
		#define lkedll __declspec(dllimport)
	#endif // LAZYKNIGHT_EXPORTS

	// This will trigger everytime it hits a STL container in a dll class - even if it's private
	#ifdef _MSC_VER
		#pragma warning(disable: 4251)
	#endif

#endif // LAZYKNIGHT_STATIC