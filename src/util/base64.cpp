#include "base64.hpp"

#include <algorithm>

namespace mmx {

	static const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	std::string base64_encode(const std::string& in) {
		int count = 0;
		int index = 0;
		int	size = in.size();

		std::string encoded(((size + ((size % 3) ? (3 - (size % 3)) : 0)) / 3) * 4, 0);

		unsigned const char* bytes = reinterpret_cast<unsigned const char*>(in.c_str());

		unsigned char arr3[3]{};
		unsigned char arr4[4]{};

		while (size--) {
			arr3[count++] = *bytes++;

			if (count == 3) {
				arr4[0] = (arr3[0] & 0xFC) >> 2;
				arr4[1] = ((arr3[0] & 0x03) << 4) + ((arr3[1] & 0xF0) >> 4);
				arr4[2] = ((arr3[1] & 0x0F) << 2) + ((arr3[2] & 0xC0) >> 6);
				arr4[3] = (arr3[2] & 0x3F);

				for (int i = 0; i < 4; ++i) {
					encoded[index++] = base64_chars[arr4[i]];
				}

				count = 0;
			}
		}

		if (count) {
			for (int i = count; i < 3; ++i)
				arr3[i] = '\0';

			arr4[0] = (arr3[0] & 0xFC) >> 2;
			arr4[1] = ((arr3[0] & 0x03) << 4) + ((arr3[1] & 0xF0) >> 4);
			arr4[2] = ((arr3[1] & 0x0F) << 2) + ((arr3[2] & 0xC0) >> 6);
			arr4[3] = (arr3[2] & 0x3F);

			for (int i = 0; i < count + 1; ++i) {
				encoded[index++] = base64_chars[arr4[i]];
			}

			while (count++ < 3) {
				encoded[index++] = '=';
			}
		}

		return encoded;
	}

	std::string base64_decode(const std::string& encoded) {
		int i = 0;
		int j = 0;
		int index = 0;
		int size = encoded.size();

		std::string decoded(size * 3 / 4 - std::count(std::begin(encoded), std::end(encoded), '='), 0);

		unsigned char arr3[3]{};
		unsigned char arr4[4]{};

		while (size-- && encoded[j] != '=' && (isalnum(encoded[j]) || (encoded[j] == '+') || (encoded[j] == '/'))) {
			arr4[i++] = encoded[j++];

			if (i == 4) {
				for (int k = 0; k < 4; ++k) {
					arr4[k] = base64_chars.find(arr4[k]);
				}

				arr3[0] = (arr4[0] << 2) + ((arr4[1] & 0x30) >> 4);
				arr3[1] = ((arr4[1] & 0xf) << 4) + ((arr4[2] & 0x3c) >> 2);
				arr3[2] = ((arr4[2] & 0x3) << 6) + arr4[3];

				for (int k = 0; k < 3; ++k) {
					decoded.at(index++) = arr3[k];
				}
				i = 0;
			}
		}

		if (i) {
			for (int k = i; k < 4; ++k) {
				arr4[k] = 0;
			}

			for (int k = 0; k < 4; ++k) {
				arr4[k] = base64_chars.find(arr4[k]);
			}

			arr3[0] = (arr4[0] << 2) + ((arr4[1] & 0x30) >> 4);
			arr3[1] = ((arr4[1] & 0xf) << 4) + ((arr4[2] & 0x3c) >> 2);
			arr3[2] = ((arr4[2] & 0x3) << 6) + arr4[3];

			for (int k = 0; k < i - 1; ++k) {
				decoded.at(index++) = arr3[k];
			}
		}

		return decoded;
	}

}    // ~namespace mmx

