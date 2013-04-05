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
	 * http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
	 */
	inline std::string& trim_left(std::string& s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
		return s;
	}

	/**
	 * http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
	 */
	inline std::string& trim_right(std::string& s) {
		s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
		return s;
	}

	/**
	 * http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
	 */
	inline std::string& trim(std::string& str) {
		return trim_left(trim_right(str));
	}

	/**
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
