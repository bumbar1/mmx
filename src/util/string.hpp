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
	MMX_API std::vector<std::string> split(const std::string& str, const char sep=' ');
	
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
	inline std::string to_string(const T& x) {
		std::ostringstream out;
		out << x;
		return out.str();
	}

	/**
	 *
	 */
	template <>
	inline std::string to_string<std::string>(const std::string& str) {
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
	 * http://www.parashift.com/c++-faq-lite/templates.html#faq-35.8
	 */
	template <>
	inline std::string to_string<double>(const double& x) {
		const int sigdigits = std::numeric_limits<double>::digits10;
		std::ostringstream out;
		out << std::setprecision(sigdigits) << x;
		return out.str();
	}

	/**
	 * http://www.parashift.com/c++-faq-lite/templates.html#faq-35.8
	 */
	template <>
	inline std::string to_string<float>(const float& x) {
		const int sigdigits = std::numeric_limits<float>::digits10;
		std::ostringstream out;
		out << std::setprecision(sigdigits) << x;
		return out.str();
	}

	/**
	 * http://www.parashift.com/c++-faq-lite/templates.html#faq-35.8
	 */
	template <>
	inline std::string to_string<long double>(const long double& x) {
		const int sigdigits = std::numeric_limits<long double>::digits10;
		std::ostringstream out;
		out << std::setprecision(sigdigits) << x;
		return out.str();
	}

	/**
	 *
	 */
	MMX_API std::string to_lower(const std::string& str);
	
	/**
	 *
	 */
	MMX_API std::string to_upper(const std::string& str);

}         // ~namespace mmx

#endif    // MMX_UTIL_STRING_HPP
