#include "file.hpp"

#include <sys/stat.h>

#if defined( MMX_IS_MSVC ) || defined( MMX_IS_MINGW )
	#include <windows.h>
#endif

namespace mmx {

	bool is_file(const char* path) {
		struct stat buf;
		::stat(path, &buf);
		return S_ISREG(buf.st_mode);
	}

	bool is_file(const std::string& path) {
		return is_file(path.c_str());
	}

	bool is_dir(const char* path) {
		struct stat buf;
		::stat(path, &buf);
		return S_ISDIR(buf.st_mode);
	}

	bool is_dir(const std::string& path) {
		return is_dir(path.c_str());
	}

	bool is_ext(const std::string& filename, const std::string& ext) {
		return filename.substr(filename.size() - ext.size(), ext.size()) == ext;
	}

#if defined( MMX_IS_MSVC ) || defined( MMX_IS_MINGW )
	std::string abspath(const std::string& relative) {
		if (!is_file(relative))
			// return empty string, throw an exception?
			return std::string("invalid file (" + relative + ")");

		const int SIZE = 1024;
		char buffer[SIZE]{};

		::GetFullPathName(relative.c_str(), SIZE, buffer, nullptr);

		return std::string(buffer);

		//char full[_MAX_PATH];
		//if (std::_fullpath(full, relative.c_str(), _MAX_PATH))
		//	return std::string(full);
		//return std::string("invalid path");
	}
#endif

}         // ~namespace mmx
