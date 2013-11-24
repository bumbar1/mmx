#ifndef MMX_VECTOR2_HPP
#define MMX_VECTOR2_HPP 1

#include "config.hpp"

#include <ostream>		// << operator
#include <cmath>		// sin, cos, atan2
#include <stdexcept>	// invalid_argument

namespace mmx {

	/**
	 * http://higherorderfun.com/blog/2012/06/03/math-for-game-programmers-05-vector-cheat-sheet/
	 */
	template <class T>
	class vector2 {
	public:
		MMX_CONSTEXPR vector2(const T a, const T b) : x(a), y(b) {}
		MMX_CONSTEXPR vector2(const vector2& v) : x(v.x), y(v.y) {}

		vector2& operator = (const vector2& other) {
			if (this != &other) {
				x = other.x;
				y = other.y;
			}
			return *this;
		}

		MMX_CONSTEXPR vector2 operator - () const { return {-x, -y}; }
		MMX_CONSTEXPR vector2 operator + (const vector2& v) const { return {x + v.x, y + v.y}; }
		MMX_CONSTEXPR vector2 operator - (const vector2& v) const { return {x - v.x, y - v.y}; }
		MMX_CONSTEXPR vector2 operator * (const vector2& v) const { return {x * v.x, y * v.y}; }

		vector2 operator / (const vector2& v) const {
			if (v.x == 0 || v.y == 0)
				throw std::invalid_argument("vector2: almost divied by zero!");
			return {x / v.x, y / v.y};
		}

		vector2& operator += (const vector2& v) {
			x += v.x;
			y += v.y;
			return *this;
		}

		vector2& operator -= (const vector2& v) {
			x -= v.x;
			y -= v.y;
			return *this;
		}

		vector2& operator *= (const vector2& v) {
			x *= v.x;
			y *= v.y;
			return *this;
		}

		vector2& operator /= (const vector2& v) {
			if (v.x == 0 || v.y == 0)
				throw std::invalid_argument("vector2: almost divied by zero!");
			x /= v.x;
			y /= v.y;
			return *this;
		}

		MMX_CONSTEXPR vector2 operator * (T scalar) const { return {x * scalar, y * scalar}; }

		vector2 operator / (T scalar) const {
			if (scalar == 0)
				throw std::invalid_argument("vector2: almost divied by zero!");
			return {x / scalar, y / scalar};
		}

		vector2& operator *= (T scalar) const {
			x *= scalar;
			y *= scalar;
			return *this;
		}

		vector2& operator /= (T scalar) const {
			if (scalar == 0)
				throw std::invalid_argument("vector2: almost divided by zero!");
			x /= scalar;
			y /= scalar;
			return *this;
		}

		MMX_CONSTEXPR bool operator == (const vector2& v) const { return x == v.x && y == v.y; }
		MMX_CONSTEXPR bool operator != (const vector2& v) const { return x != v.x || y != v.y; }

		friend std::ostream& operator << (std::ostream& os, const vector2& v) {
			os << '(' << v.x << ", " << v.y << ')';
			return os;
		}

		MMX_CONSTEXPR T dot(const vector2& v) const { return x * v.x + y * v.y; }
		MMX_CONSTEXPR T cross(const vector2& v) const { return x * v.y - y * v.x; }
		MMX_CONSTEXPR T length() const { return std::sqrt(x * x + y * y); }
		MMX_CONSTEXPR T squared_length() const { return x * x + y * y; }

		MMX_CONSTEXPR vector2 unit() const { return *this / length(); }

		/** Assumes that y axis points up, otherwise this is turn_right **/
		MMX_CONSTEXPR vector2 turn_left() const { return {-y, x}; }

		/** Assumes that y axis points up, otherwise this is turn_left **/
		MMX_CONSTEXPR vector2 turn_right() const { return {y, -x}; }

		MMX_CONSTEXPR vector2 rotate(double angle) const {
			return {x * std::cos(angle) - y * std::sin(angle), x * std::sin(angle) + y * std::cos(angle)};
		}

		MMX_CONSTEXPR double angle() const { return std::atan2(y, x); }

		T x;
		T y;
	};

	template <class T>
	MMX_CONSTEXPR vector2<T> operator * (T scalar, vector2<T>& v) { return vector2<T>(v.x * scalar, v.y * scalar); }

	typedef vector2<float>  v2f;
	typedef vector2<double> v2d;
	typedef vector2<int>    v2i;
	
	typedef vector2<float>  vec2f;
	typedef vector2<double> vec2d;
	typedef vector2<int>    vec2i;
	
	typedef vector2<float>  vector2f;
	typedef vector2<double> vector2d;
	typedef vector2<int>    vector2i;
	
}           // ~namespace mmx

#endif      // MMX_VECTOR2_HPP
