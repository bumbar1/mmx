#ifndef MMX_UTIL_RANGE_HPP
#define MMX_UTIL_RANGE_HPP 1

#include "../config.hpp"

#include <iterator>
#include <algorithm>
#include <utility>

namespace mmx {

	template <class T>
	class range_iterator : public std::iterator<std::random_access_iterator_tag, T, T> {
	public:
		typedef T value_type;

		MMX_CONSTEXPR range_iterator(value_type i, value_type step=1) : _count(i), _step(step) {}
		MMX_CONSTEXPR range_iterator(const range_iterator<T>& it)
			: _count(*it), _step(it._step)
		{
		}

		MMX_CONSTEXPR T operator * () const { return _count; }

		range_iterator operator ++ () { _count += _step; return *this; }

		MMX_CONSTEXPR bool operator < (const range_iterator& other) const {
			return (_step < 0) ? _count > *other : _count < *other;
		}

		MMX_CONSTEXPR bool operator == (const range_iterator& other) const {
			return _count == *other;
		}

		MMX_CONSTEXPR bool operator != (const range_iterator& other) const{
			return (_step < 0) ? _count > *other : _count < *other;
		}

	private:
		T _count;
		T _step;
	};

	template <class T>
	class Range {
	public:
		typedef T value_type;

		MMX_CONSTEXPR Range(value_type start, value_type end, value_type step)
			: _start(start, step), _end(end, step), _step(step) {}

		range_iterator<value_type> begin() const { return _start; }
		range_iterator<value_type> end() const { return _end; }

		MMX_CONSTEXPR Range reverse() { return Range(*_end, *_start, -_step); }
	private:
		range_iterator<value_type> _start;
		range_iterator<value_type> _end;
		value_type                 _step;
	};

	template <class T>
	MMX_CONSTEXPR Range<T> range(T start, T end, T step=1) { return {start, end, step}; }

	template <class T>
	MMX_CONSTEXPR Range<T> range(T end) { return {T(0), end, T(1)}; }

}         // ~namespace mmx

#endif    // MMX_UTIL_RANGE_HPP
