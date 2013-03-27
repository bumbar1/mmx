#ifndef MMX_DIR_HPP
#define MMX_DIR_HPP 1

#include "config.hpp"

#include <string>
#include <vector>

#include <dirent.h>

namespace mmx {

	class MMX_API dir {
	public:
		dir();
		dir(const std::string& path);

		dir(const dir&) MMX_CLASS_DELETE;
		dir& operator = (const dir& ) MMX_CLASS_DELETE;

		virtual ~dir();

		void                     open(const std::string& path);
		void                     open();
		void                     close();
		void                     rewind();
	#if !defined( MMX_IS_MSVC )
		void                     seek(unsigned long location);
	#endif
		void                     read(std::vector<std::string>&& files);
		std::vector<std::string> read();
		std::string              path() const;
	#if !defined( MMX_IS_MSVC )
		unsigned long long       offset() const;
	#endif
		bool                     is_open() const;

	private:
		DIR*                     _dir;
		dirent*                  _pdir;
		std::string              _path;
	};

}           // ~namespace mmx

#endif      // MMX_DIR_HPP
