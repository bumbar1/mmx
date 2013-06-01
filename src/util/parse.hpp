#ifndef MMX_UTIL_PARSE_HPP
#define MMX_UTIL_PARSE_HPP 1

#include "../config.hpp"

#include <string>
#include <sstream>
#include <exception>

namespace mmx {

	class parse_error : public std::exception {
	public:
		parse_error(const std::string& what) : _what(what) {}

		const char* what() const noexcept { return _what.c_str(); }
	private:
		std::string _what;
	};

	/**
	 *
	 */
	template <class T>
	inline T parse(const std::string& str) {
		T n;
		std::stringstream ss(str);
		ss >> n;
		if (ss.fail())
			throw parse_error("error parsing (with arg: " + str + ")");
		return n;
	}

	/**
	 *
	 */
	template <class T>
	inline T parse(const char* chars) {
		return parse<T>(std::string(chars));
	}

}         // ~namespace mmx

#endif    // MMX_UTIL_PARSE_HPP
