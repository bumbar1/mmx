#ifndef MMX_UTIL_FILE_HPP
#define MMX_UTIL_FILE_HPP 1

#include "../config.hpp"

#include <string>

#if defined( MMX_IS_MSVC ) || defined( MMX_IS_MINGW )
	#include <windows.h>
#endif

#include <sys/stat.h>

namespace mmx {

	/**
	 *
	 */
	bool is_file(const char* path) {
		struct stat buf;
		::stat(path, &buf);
		return S_ISREG(buf.st_mode);
	}

	/**
	 *
	 */
	bool is_file(const std::string& path) {
		return is_file(path.c_str());
	}

	/**
	 * path must be without trailing slash
	 */
	bool is_dir(const char* path) {
		struct stat buf;
		::stat(path, &buf);
		return S_ISDIR(buf.st_mode);
	}

	/**
	 *
	 */
	bool is_dir(const std::string& path) {
		return is_dir(path.c_str());
	}

	/**
	 *
	 */
	bool is_ext(const std::string& filename, const std::string& ext) {
		return filename.substr(filename.size() - ext.size(), ext.size()) == ext;
	}

	/**
	 * Windows only so far
	 */
#if defined( MMX_IS_MSVC ) || defined( MMX_IS_MINGW )
	std::string abspath(const std::string& relative) {
		if (!is_file(relative)) {
			// return empty string, throw an exception?
			return std::string("invalid file (" + relative + ")");
		}

		const int SIZE = 1024;
		char buffer[SIZE]{};

		::GetFullPathName(relative.c_str(), SIZE, buffer, nullptr);

		return std::string(buffer);
	}
#endif

}         // ~namespace mmx

#endif    // MMX_UTIL_FILE_HPP

