#ifndef MMX_UTIL_BASE64_HPP
#define MMX_UTIL_BASE64_HPP 1

#include "../config.hpp"

#include <string>
#include <initializer_list>

namespace mmx {

	/**
	 *
	 */
	MMX_API std::string base64_encode(const std::string& in);

	/**
	 *
	 */
	template <class T>
	std::string base64_encode(std::initializer_list<T> list) {
		std::string s(list.size(), 0);
		std::copy(std::begin(list), std::end(list), std::begin(s));
		return base64_encode(s);
	}

	/**
	 *
	 */
	template <class First, class... Args>
	std::string base64_encode(First first, Args... args) {
		return base64_encode({first, args...});
	}

	/**
	 *
	 */
	MMX_API std::string base64_decode(const std::string& encoded);

}         // ~namespace mmx

#endif    // MMX_UTIL_BASE64_HPP

