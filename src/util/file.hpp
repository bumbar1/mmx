#ifndef MMX_UTIL_FILE_HPP
#define MMX_UTIL_FILE_HPP 1

#include "../config.hpp"

#include <string>

namespace mmx {

	/**
	 *
	 */
	MMX_API bool is_file(const char* path);

	/**
	 *
	 */
	MMX_API bool is_file(const std::string& path);

	/**
	 * path must be without trailing slash
	 */
	MMX_API bool is_dir(const char* path);

	/**
	 *
	 */
	MMX_API bool is_dir(const std::string& path);

	/**
	 *
	 */
	MMX_API bool is_ext(const std::string& filename, const std::string& ext);

	/**
	 * Windows only so far
	 */
#if defined( MMX_IS_MSVC ) || defined( MMX_IS_MINGW )
	MMX_API std::string abspath(const std::string& relative);
#endif

}         // ~namespace mmx

#endif    // MMX_UTIL_FILE_HPP
