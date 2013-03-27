#include <iostream>
#include <vector>
#include <stdexcept>

#include "src/mmx.hpp"

int main() {

	mmx::timer timer;

	timer.start();
	
	std::cout << "date: " << mmx::date::to_string() << std::endl;
	std::cout << "time: " << mmx::time::to_string() << std::endl;

	try {
		mmx::dir dir;

		// without trailing forward slash
		if (!mmx::is_dir("include/mmx")) {
			std::cout << "'include/mmx' is not a directory" << std::endl;
			throw std::runtime_error("'include/mmx' is not a directory");
		}

		dir.open("include/mmx/");

		std::cout << "files in '" << dir.path() << "'" << std::endl;

		for (auto& s : dir.read())
			std::cout << dir.path() << s << std::endl;

	} catch (std::runtime_error& e) {
		std::cout << "runtime error: " << e.what() << std::endl;
	} catch (...) {
		std::cout << "unhandled exception" << std::endl;
	}

	std::cout << std::endl;

	for (auto& s : mmx::split("Quick brown fox jumped over lazy dog.", ' '))
		std::cout << "[" << s << "], ";
	
	std::cout << std::endl;
	std::cout << (mmx::endian() == mmx::endian_little ? "little" : "big") << " endian" << std::endl;

	map(print<int, ','>, mmx::range(10));

	std::cout << std::endl;

	std::cout << "choice: " << mmx::choice("one", "two", "three", "four", "five") << std::endl;

	std::vector<std::string> v {
		"one", "two", "three", "four", "five"
	};
	
	for (const auto& e : mmx::enumerate(v))
		std::cout << e.index << ": " << e.value << "\n";

	timer.stop();

	std::cout << "elapsed time: " << timer.micro() << " us" << std::endl;

	return 0;
}
