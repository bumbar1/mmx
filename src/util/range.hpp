#ifndef MMX_UTIL_RANGE_HPP
#define MMX_UTIL_RANGE_HPP 1

#include "../config.hpp"

#include <iterator>
#include <algorithm>
#include <utility>

namespace mmx {

	/**
	 * TODO: reverse method
	 */
	template <class T>
	class range_iterator : public std::iterator<std::random_access_iterator_tag, T, T> {
	public:
		typedef T type;

		MMX_CONSTEXPR range_iterator(type i, type step=1) : _count(i), _step(step), _ref(_count) {}
		MMX_CONSTEXPR range_iterator(const range_iterator<T>& it, type step=1)
			: _count(*it), _step(step), _ref(_count)
		{
		}

		MMX_CONSTEXPR T& operator * () const { return _ref; }

		range_iterator operator ++ () { _count += _step; _ref = _count; return *this; }
		range_iterator operator ++ (int) { auto tmp = *this; ++(*this); return tmp; }
		range_iterator operator -- () { _count -= _step; _ref = _count; return *this; }
		range_iterator operator -- (int) { auto tmp = *this; --(*this); return tmp; }

		bool operator < (const range_iterator& other) const {
			return _count < other._count;
		}

		bool operator == (const range_iterator& other) const {
			return _count == *other;
		}

		bool operator != (const range_iterator& other) const{
			return _count < *other;
		}

	private:
		T _count;
		T _step;
		T& _ref;
	};

	template <class T>
	class Range {
	public:
		typedef T type;

		MMX_CONSTEXPR Range(T begin, T end, T step=1) : _begin(begin, step), _end(end, step) {}

		range_iterator<T> begin() const { return _begin; }
		range_iterator<T> end() const { return _end; }

		Range& reverse() { std::reverse(_begin, _end); return *this; }
	private:
		range_iterator<T> _begin;
		range_iterator<T> _end;
	};

	template <class T>
	MMX_CONSTEXPR Range<T> range(T begin, T end, T step=1) { return {begin, end, step}; }

	template <class T>
	MMX_CONSTEXPR Range<T> range(T end, T step=1) { return {T(0), end, step}; }

}         // ~namespace mmx

#endif    // MMX_UTIL_RANGE_HPP
