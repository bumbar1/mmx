#include "time.hpp"

#include <ctime>
#include <sstream>
#include <iomanip>

namespace mmx {
	namespace time {
	
		std::string to_string() {
			time_t t = std::time(0);
			struct tm* now = localtime(&t);

			std::stringstream ss;

			ss << std::setw(2) << std::setfill('0') << now->tm_hour << ':'
			   << std::setw(2) << std::setfill('0') << now->tm_min << ':'
			   << std::setw(2) << std::setfill('0') << now->tm_sec;

			return ss.str();
		}

		int hour() {
			time_t t = std::time(0);
			struct tm* now = localtime(&t);

			return now->tm_hour;
		}

		int minute() {
			time_t t = std::time(0);
			struct tm* now = localtime(&t);

			return now->tm_min;
		}

		int second() {
			time_t t = std::time(0);
			struct tm* now = localtime(&t);

			return now->tm_sec;
		}
		
	}	// ~namespace time
}		// ~namespace mmx
