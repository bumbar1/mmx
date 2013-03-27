#ifndef MMX_TIME_HPP
#define MMX_TIME_HPP 1

#include "config.hpp"

#include <string>

namespace mmx {
	namespace time {

		MMX_API std::string to_string();

		MMX_API int hour();
		MMX_API int minute();
		MMX_API int second();

	}       // ~namespace time
}           // ~namespace mmx

#endif      // MMX_TIME_HPP
