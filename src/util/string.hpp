#ifndef MMX_UTIL_STRING_HPP
#define MMX_UTIL_STRING_HPP 1

#include "../config.hpp"

#include <string>
#include <sstream>
#include <vector>
#include <limits>
#include <iomanip>
#include <algorithm>

namespace mmx {

	/**
	 *
	 */
	std::vector<std::string> split(const std::string& str, const char sep=' ') {
		std::vector<std::string> list;
		size_t a = !std::string::npos;
		size_t b = 0;

		while (a != std::string::npos) {
			a = str.find(sep, b);
			std::string s(str.substr(b, a - b));
			if (!s.empty())
				list.push_back(s);
			b = a + 1;
		}

		return list;
	}

	/**
	 *
	 */
	std::string trim_left(std::string src) {
		return src.erase(0, src.find_first_not_of(" \t\n\r"));
	}

	/**
	 *
	 */
	std::string trim_right(std::string src) {
		return src.erase(src.find_last_not_of(" \t\n\r") + 1);
	}

	/**
	 *
	 */
	std::string trim(std::string src) {
		return trim_left(trim_right(src));
	}

	/**
	 * T = (unsigned) char, (unsigned) short, (unsigned) int, (unsigned) long, (unsigned) long long
	 *
	 * http://www.parashift.com/c++-faq-lite/templates.html#faq-35.8
	 */
	template <class T>
	inline typename std::enable_if<
		std::is_integral<T>::value, std::string
	>::type to_string(const T& x) {
		std::ostringstream out;
		out << x;
		return out.str();
	}

	/**
	 * T = float, double, long double
	 *
	 * http://www.parashift.com/c++-faq-lite/templates.html#faq-35.8
	 */
	template <class T>
	inline typename std::enable_if<
		std::is_floating_point<T>::value, std::string
	>::type to_string(const T& x) {
		const int sigdigits = std::numeric_limits<T>::digits10;
		std::ostringstream out;
		out << std::setprecision(sigdigits) << x;
		return out.str();
	}

	/**
	 *
	 */
	inline std::string to_string(const std::string& str) {
		return str;
	}

	/**
	 * http://www.parashift.com/c++-faq-lite/templates.html#faq-35.8
	 */
	template <>
	inline std::string to_string<bool>(const bool& x) {
		std::ostringstream out;
		out << std::boolalpha << x;
		return out.str();
	}

	/**
	 *
	 */
	std::string to_lower(const std::string& str) {
		std::string out(str);
		std::transform(str.begin(), str.end(), out.begin(), [](char c){
			return std::tolower(c);
		});
		return out;
	}

	/**
	 *
	 */
	std::string to_upper(const std::string& str) {
		std::string out(str);
		std::transform(str.begin(), str.end(), out.begin(), [](char c){
			return std::toupper(c);
		});
		return out;
	}

}         // ~namespace mmx

#endif    // MMX_UTIL_STRING_HPP

