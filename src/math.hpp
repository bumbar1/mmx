#ifndef MMX_MATH_HPP
#define MMX_MATH_HPP 1

#include "config.hpp"

#include <cmath>          // pow

namespace mmx {

	/// Mathematical constants to 16 decimal places.
	const double pi  = 3.1415926535897932;
	const double e   = 2.7182818284590452;
	const double phi = 1.6180339887498948;

	/**
	 *
	 */
	template <class T>
	MMX_CONSTEXPR T gcd(const T a, const T b) {
		return (!b) ? a : gcd(b, a % b);
	}

	/**
	 *
	 */
	template <class T>
	MMX_CONSTEXPR T lcm(const T a, const T b) {
		return (a * b) / gcd(a, b);
	}

	/**
	 *
	 */
	MMX_API bool is_prime(uint n);

	/**
	 * Uses Binet's formula. Returns n-th Fibonacci's number
	 */
	MMX_CONSTEXPR long double fibonacci(uint n) {
		#define sqrt5 static_cast<double>(2.2360679774997898)
		return static_cast<long double>((std::pow(phi, n) - std::pow(1 - phi, n)) / sqrt5);
	}

	/**
	 * 20! is max that can be stored in long long (8 bytes wide).
	 * ~1754! can be stored in long double
	 */
	MMX_CONSTEXPR long double factorial(uint n) {
		return (n <= 1) ? 1 : n * factorial(n - 1);
	}

	/**
	 *
	 */
	MMX_CONSTEXPR long double binomial_coefficient(uint n, uint k) {
		return factorial(n) / (factorial(k) * factorial(n - k));
	}

	/**
	 *
	 */
	MMX_API uint log2(ulonglong n);
	
	/**
	 *
	 */
	template <typename T>
	MMX_CONSTEXPR T clamp(T value, T min, T max) {
		return (value < min) ? min : (value > max) ? max : value;
	}

}           // ~namespace mmx

#endif      // MMX_MATH_HPP

