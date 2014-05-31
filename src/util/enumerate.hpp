#ifndef MMX_UTIL_ENUMERATE_HPP
#define MMX_UTIL_ENUMERATE_HPP 1

#include "../config.hpp"

#include <iterator>

namespace mmx {

	/**
	 *
	 */
	template <class T>
	struct enumerated_pair {
		typedef T value_type;
		
		MMX_CONSTEXPR enumerated_pair(std::size_t i, value_type v) : index(i), value(v) {}
		MMX_CONSTEXPR enumerated_pair(const enumerated_pair& copy) : index(copy.index), value(copy.value) {}

		MMX_CONSTEXPR value_type operator* () { return value; }

		std::size_t  index;
		value_type   value;
	};

	/**
	 * http://stackoverflow.com/questions/10962290/find-position-of-element-in-c11-range-based-for-loop
	 */
	template <typename T>
	struct iterator_extractor { typedef typename T::iterator type; };

	/**
	 * http://stackoverflow.com/questions/10962290/find-position-of-element-in-c11-range-based-for-loop
	 */
	template <typename T>
	struct iterator_extractor<T const> { typedef typename T::const_iterator type; };

	/**
	 * http://stackoverflow.com/questions/10962290/find-position-of-element-in-c11-range-based-for-loop?lq=1
	 */
	template <typename T>
	class Indexer {
	public:
		class iterator {
			typedef typename iterator_extractor<T>::type inner_iterator;
			typedef typename std::iterator_traits<inner_iterator>::reference inner_reference;
		public:
			//typedef std::pair<size_t, inner_reference> reference;
			typedef enumerated_pair<inner_reference> reference;

			iterator(inner_iterator it): _pos(0), _it(it) {}

			reference operator*() const { return reference(_pos, *_it); }

			iterator& operator++() { ++_pos; ++_it; return *this; }
			iterator operator++(int) { iterator tmp(*this); ++*this; return tmp; }

			bool operator==(iterator const& it) const { return _it == it._it; }
			bool operator!=(iterator const& it) const { return !(*this == it); }

		private:
			std::size_t     _pos;
			inner_iterator  _it;
		};

		Indexer(T& t): _container(t) {}

		iterator begin() const { return iterator(_container.begin()); }
		iterator end() const { return iterator(_container.end()); }

	private:
		T& _container;
	}; // class Indexer

	/**
	 * http://stackoverflow.com/questions/10962290/find-position-of-element-in-c11-range-based-for-loop
	 */
	template <typename T>
	Indexer<T> enumerate(T& t) { return Indexer<T>(t); }

}         // ~namespace mmx

#endif    // MMX_UTIL_ENUMERATE_HPP 1
