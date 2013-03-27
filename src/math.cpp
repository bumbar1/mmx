#include "math.hpp"

#include <cmath>

namespace mmx {

	bool is_prime(uint n) {
		if (n < 2)
			return false;

		int sn = int(std::sqrt(n)) + 1;

		for (int i = 2; i < sn; ++i)
			if ((n % i) * n == 0)
				return false;
		return true;
	}

	uint log2(ulonglong n) {
		uint ret = -1;

		while (n >>= 1)
			++ret;
			
		return ret;
	}

}		 // ~namespace mmx
