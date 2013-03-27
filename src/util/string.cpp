#include "string.hpp"

namespace mmx {

	std::vector<std::string> split(const std::string& str, const char sep) {
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
	
	std::string to_lower(const std::string& str) {
		std::string out(str);
		std::transform(str.begin(), str.end(), out.begin(), [](char c){
			return std::tolower(c);
		});
		return out;
	}
	
	std::string to_upper(const std::string& str) {
		std::string out(str);
		std::transform(str.begin(), str.end(), out.begin(), [](char c){
			return std::toupper(c);
		});
		return out;
	}

}    // ~namespace mmx
