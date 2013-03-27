#ifndef MMX_DATE_HPP
#define MMX_DATE_HPP 1

#include "config.hpp"

#include <string>

namespace mmx {
	namespace date {

		MMX_API std::string to_string();

		MMX_API int year();
		MMX_API int month();
		MMX_API int day();
		MMX_API int year_day();    // 0-365
		MMX_API int week_day();    // 0-6

	}       // ~namespace date
}           // ~namespace mmx

#endif      // MMX_DATE_HPP
