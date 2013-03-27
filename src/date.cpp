#include "date.hpp"

#include <ctime>
#include <sstream>
#include <iomanip>

namespace mmx {
	namespace date {
	
		std::string to_string() {
			time_t t = std::time(0);
			struct tm* now = localtime(&t);

			std::stringstream ss;

			ss << (1900 + now->tm_year) << '-'
			   << std::setw(2) << std::setfill('0') << (now->tm_mon + 1) << '-'
			   << std::setw(2) << std::setfill('0') << now->tm_mday;

			return ss.str();
		}

		int year() {
			time_t t = std::time(0);
			struct tm* now = localtime(&t);

			return now->tm_year + 1900;
		}

		int month() {
			time_t t = std::time(0);
			struct tm* now = localtime(&t);

			return now->tm_mon + 1;
		}

		int day() {
			time_t t = std::time(0);
			struct tm* now = localtime(&t);

			return now->tm_mday;
		}

		int year_day() {
			time_t t = std::time(0);
			struct tm* now = localtime(&t);

			return now->tm_yday;
		}

		int week_day() {
			time_t t = std::time(0);
			struct tm* now = localtime(&t);

			return now->tm_wday;
		}
	
	}	// ~namespace date
}       // ~namespace mmx
