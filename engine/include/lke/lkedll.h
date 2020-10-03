#pragma once

#ifdef LAZYKNIGHT_STATIC
	#define lkedll
#else
	#if defined(_MSC_VER)
		#define EXPORT __declspec(dllexport)
		#define IMPORT __declspec(dllimport)
	#elif defined(__GNUC__)
		#define EXPORT __attribute__((visibility("default")))
		#define IMPORT
	#else
		#define EXPORT
		#define IMPORT
		#pragma warning Unknown dynamic link import/export semantics.
	#endif

	#ifdef LAZYKNIGHT_EXPORTS
		#define lkedll EXPORT
	#else
		#define lkedll IMPORT
	#endif // LAZYKNIGHT_EXPORTS

	// This will trigger everytime it hits a STL container in a dll class - even if it's private
	#ifdef _MSC_VER
		#pragma warning(disable: 4251)
	#endif

#endif // LAZYKNIGHT_STATIC