#ifndef MMX_UTIL_HPP
#define MMX_UTIL_HPP 1

#include "config.hpp"

#include <algorithm>    // map
#include <iostream>     // print
#include <type_traits>  // enable_if, is_integral
#include <future>
#include <thread>
#include <chrono>

#include "util/base64.hpp"
#include "util/endian.hpp"
#include "util/enumerate.hpp"
#include "util/file.hpp"
#include "util/parse.hpp"
#include "util/random.hpp"
#include "util/range.hpp"
#include "util/string.hpp"

namespace mmx {

	/**
	 * http://graphics.stanford.edu/~seander/bithacks.html
	 */
	template <class T>
	MMX_CONSTEXPR
	typename std::enable_if<
		std::is_integral<T>::value, T
	>::type min(const T x, const T y) {
		return y ^ ((x ^ y) & -(x < y));
	}

	/**
	 * http://graphics.stanford.edu/~seander/bithacks.html
	 */
	template <class T>
	MMX_CONSTEXPR
	typename std::enable_if<
		std::is_integral<T>::value, T
	>::type max(const T x, const T y) {
		return x ^ ((x ^ y) & -(x < y));
	}

	/**
	 * http://www.dodgycoder.net/2012/02/coding-tricks-of-game-developers.html?m=1
	 */
	template <class T>
	MMX_CONSTEXPR
	typename std::enable_if<
		std::is_integral<T>::value, T
	>::type abs(const T x) {
		//const T mask = x >> (8 * sizeof(T) - 1);
		//return (x ^ mask) - mask;
		#define MASK (x >> (8 * sizeof(T) - 1))
		return (x ^ MASK) - MASK;
	}

	/**
	 * http://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetKernighan
	 */
	template <class T>
	typename std::enable_if<
		std::is_integral<T>::value, std::size_t
	>::type bits_on(T n) {
		size_t c = 0;      // c accumulates the total bits set in v

		for (; n; c++) {
			n &= n - 1;    // clear the least significant bit set
		}

		return c;
	}

	/// is_equal precision (internal, not to be exported)
	static const double epsilon = 1e-5d;

	/**
	 * http://www.parashift.com/c++-faq-lite/newbie.html#faq-29.17
	 */
	template <class T>
	MMX_CONSTEXPR
	typename std::enable_if<
		std::is_floating_point<T>::value, bool
	>::type is_equal(T x, T y) {
		return std::abs(x - y) <= epsilon * std::abs(x);
	}

	namespace __internal {
		template <class F>
		void timeout_callback(unsigned msec, F& f) {
			std::this_thread::sleep_for(std::chrono::milliseconds(msec));
			f();
		}
	}         // ~namespace __internal

	/**
	 * set_timeout(1000, []{ MessageBox(NULL, L"Showing after 1000 ms", L"Caption", 0); });
	 */
	template <class F>
	void set_timeout(unsigned msec, F&& f) {
		return std::async(std::bind(__internal::timeout_callback<F>, msec, std::forward<F>(f))).get();
	}

	/**
	 *
	 */
	template <class F, class S>
	void map(F&& f, S&& s) {
		std::for_each(std::begin(std::forward<S>(s)), std::end(std::forward<S>(s)), std::forward<F>(f));
	}

	/**
	 *
	 */
	template <class T, char sep='\n'>
	void print(const T x) {
		std::cout << mmx::to_string(x) << sep;
	}
	
}           // ~namespace mmx

#endif      // MMX_UTIL_HPP

