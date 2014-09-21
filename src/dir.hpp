#ifndef MMX_DIR_HPP
#define MMX_DIR_HPP 1

#include "config.hpp"

#include <string>
#include <vector>
#include <stdexcept>

#include <dirent.h>

namespace mmx {

	class MMX_API dir {
	public:
		dir()
			: dir(".")
		{
		}

		dir(const std::string& path)
			: _dir(nullptr)
			, _pdir(nullptr)
			, _path(path)
		{
			open();
		}

		dir(const dir&) MMX_CLASS_DELETE;
		dir& operator = (const dir& ) MMX_CLASS_DELETE;
		dir(dir&&) MMX_CLASS_DELETE;
		dir&& operator = (dir&&) MMX_CLASS_DELETE;

		virtual ~dir() {
			close();
		};

		void open() {
			if (_path.empty()) {
				throw std::runtime_error("dir: no directory specified to open");
			}

			close();

			_dir = ::opendir(_path.c_str());

			if (_dir == nullptr) {
				throw std::runtime_error("dir: failed to open '" + _path + "'");
			}
		}

		void open(const std::string& path) {
			_path = path;
			open();
		}

		void close() {
			if (_dir) {
				::closedir(_dir);
			}
		}

		void rewind() {
			::rewinddir(_dir);
		}
		

		void read(std::vector<std::string>& files) {
			while ((_pdir = ::readdir(_dir))) {
				files.push_back(_pdir->d_name);
			}
		}

		std::vector<std::string> read() {
			std::vector<std::string> files;
			read(files);
			return files;
		}

		std::string path() const {
			return _path;
		}

		bool is_open() const {
			return _dir != nullptr;
		}

	#if !defined( MMX_IS_MSVC )
		void seek(unsigned long location) {
			seekdir(_dir, location);
		}

		ulonglong offset() const {
			return telldir(_dir);
		}
	#endif

	private:
		DIR*         _dir;
		dirent*      _pdir;
		std::string  _path;
	};

}           // ~namespace mmx

#endif      // MMX_DIR_HPP

