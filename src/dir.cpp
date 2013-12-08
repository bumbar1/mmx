#include "dir.hpp"

#include <stdexcept>

namespace mmx {

	dir::dir()
		: dir(".")
	{
	}

	dir::dir(const std::string& path)
		: _dir(nullptr),
		  _pdir(nullptr),
		  _path(path)
	{
		open();
	}

	dir::~dir() {
		close();
	}

	void dir::open() {
		if (_path.empty())
			throw std::runtime_error("dir: no directory specified to open");
			
		close();

		_dir = ::opendir(_path.c_str());

		if (_dir == nullptr)
			throw std::runtime_error("dir: failed to open '" + _path + "'");
	}

	void dir::open(const std::string& path) {
		_path = path;
		open();
	}

	void dir::close() {
		if (_dir)
			::closedir(_dir);
	}

	void dir::rewind() {
		::rewinddir(_dir);
	}

#if !defined( MMX_IS_MSVC )
	void dir::seek(unsigned long location) {
		seekdir(_dir, location);
	}
#endif

	void dir::read(std::vector<std::string>& files) {
		while ((_pdir = ::readdir(_dir)))
			files.push_back(_pdir->d_name);
	}

	std::vector<std::string> dir::read() {
		std::vector<std::string> files;
		read(files);
		return files;
	}

#if !defined( MMX_IS_MSVC )
	unsigned long long dir::offset() const {
		return telldir(_dir);
	}
#endif

	bool dir::is_open() const {
		return _dir != nullptr;
	}

	std::string dir::path() const {
		return _path;
	}

}		// ~namespace mmx
