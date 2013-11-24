#ifndef MMX_UTIL_RANDOM_HPP
#define MMX_UTIL_RANDOM_HPP 1

#include "../config.hpp"

#include <random>
#include <iterator>  // iterator_traits
#include <initializer_list>
#include <type_traits>

// Compiling with MinGW (as of version 4.7.2, std::random_device not yet supported)
#if defined( MMX_IS_MINGW )
	#include <chrono>
	#define __MMX_RANDOM_CODE \
		static auto now = std::chrono::high_resolution_clock::now().time_since_epoch().count(); \
		static std::default_random_engine gen(now)
#else
	#define __MMX_RANDOM_CODE \
		std::random_device  rd; \
		std::mt19937        gen(rd())
#endif

/// TODO: http://stackoverflow.com/questions/7285975/match-multiple-types-for-template-specialization-resolution

namespace mmx {

	/**
	 * Includes both end points, closed interval [min, max].
	 */
	template <class T>
	typename std::enable_if<
		std::is_integral<T>::value, T
	>::type ranged_rand(T min, T max)  {
		__MMX_RANDOM_CODE;
		std::uniform_int_distribution<T>   dist(min, max);

		return dist(gen);
	}

	/**
	 * Includes both end points, closed interval [min, max].
	 */
	template <class T>
	typename std::enable_if<
		std::is_floating_point<T>::value, T
	>::type ranged_rand(T min, T max)  {
		__MMX_RANDOM_CODE;
		std::uniform_real_distribution<T>  dist(min, max);

		return dist(gen);
	}

	/**
	 *
	 */
	template <class InputIterator>
	typename std::iterator_traits<InputIterator>::value_type
	choice(InputIterator first, InputIterator last) {
		return *(first + ranged_rand(InputIterator(0), last - first - 1));
	}

	/**
	 *
	 */
	template <class T>
	T choice(std::initializer_list<T> list) {
		return choice(std::begin(list), std::end(list));
	}

	/**
	 *
	 */
	template <class T, class... Args>
	T choice(T first, Args... args) {
		return choice({first, args...});
	}

	/**
	 *
	 */
	bool coin_flip() {
		__MMX_RANDOM_CODE;
		std::bernoulli_distribution  dist(0.5);

		return dist(gen);
	}

	/**
	 *
	 */
	bool flip_coin() {
		return coin_flip();
	}

	/**
	 *
	 */
	uint dice_roll(uint side=6) {
		return ranged_rand<uint>(1, side);
	}

	/**
	 *
	 */
	uint roll_dice(uint side=6) {
		return dice_roll);
	}

}        // ~namespace mmx

#endif   // MMX_UTIL_RANDOM_HPP
