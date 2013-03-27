#ifndef MMX_CONFIG_HPP
#define MMX_CONFIG_HPP 1

/// TODO: clang

// should only be defined when building dll
#if defined( MMX_DYNAMIC )
	#if defined( _WIN32 ) || defined( __WIN32__ )
		#define MMX_API_EXPORT    __declspec(dllexport)
		#define MMX_API_IMPORT    __declspec(dllimport)

		// MSVC++ 10 (1600, VS 2010) and MSVC++ 11 (1700, VS 2012) have adequate C++11 support
		#if defined( _MSC_VER ) && _MSC_VER >= 1600
			#define MMX_CONSTEXPR
			#define MMX_CLASS_DELETE
			#define MMX_CLASS_DEFAULT
			#define MMX_IS_MSVC          1
		// Windows and not Visual Studio (assume MinGW); todo: fix assumption
		#else
			#define MMX_CONSTEXPR        constexpr
			#define MMX_CLASS_DELETE     = delete
			#define MMX_CLASS_DEFAULT    = default
			#define MMX_IS_MINGW         1
		#endif
	// not Windows
	#else
		#if defined( __GNUC__ )
			#define MMX_IS_GCC           1
		#endif

		#define MMX_API_EXPORT
		#define MMX_API_IMPORT
		#define MMX_CONSTEXPR        constexpr
		#define MMX_CLASS_DELETE     = delete
		#define MMX_CLASS_DEFAULT    = default
	#endif

// static build
#else
	#define MMX_API_EXPORT
	#define MMX_API_IMPORT
	#if defined( _WIN32 ) || defined( __WIN32__ )
		#if defined( _MSC_VER ) && _MSC_VER >= 1600
			#define MMX_CONSTEXPR
			#define MMX_CLASS_DELETE
			#define MMX_CLASS_DEFAULT
			#define MMX_IS_MSVC  1
		#else
			#define MMX_CONSTEXPR        constexpr
			#define MMX_CLASS_DELETE     = delete
			#define MMX_CLASS_DEFAULT    = default
			#define MMX_IS_MINGW 1
		#endif
	#elif defined( __GNUC__ )
		#define MMX_CONSTEXPR        constexpr
		#define MMX_CLASS_DELETE     = delete
		#define MMX_CLASS_DEFAULT    = default
		#define MMX_IS_GCC       1
	#endif
#endif

#if defined( MMX_DYNAMIC )
	#define MMX_API	   MMX_API_EXPORT
#else
	#define MMX_API    MMX_API_IMPORT
#endif

typedef unsigned long long ulonglong;
typedef unsigned int       uint;
typedef unsigned char      byte;

#endif      // MMX_CONFIG_HPP
