#ifndef MMX_UTIL_ENDIAN_HPP
#define MMX_UTIL_ENDIAN_HPP 1

#include "../config.hpp"

namespace mmx {

	const bool endian_little = true;
	const bool endian_big    = false;

	/**
	 * Checks endianess of the machine.
	 *
	 * big   : 0x12, 0x34, 0x56, 0x78
	 * little: 0x78, 0x56, 0x34, 0x12
	 */
	MMX_CONSTEXPR bool endian() {
		return static_cast<char>(int(0x12345678)) == 0x78;
	}

}       // ~namespace mmx

#endif	// MMX_UTIL_ENDIAN_HPP

