#include "util.hpp"

/** x && !(x & (x - 1)) **/

namespace mmx {

	const bool endian_little = true;
	const bool endian_big    = false;

	bool endian() {
		return static_cast<char>(int(0x12345678)) == 0x78;
	}

}		// ~namespace
