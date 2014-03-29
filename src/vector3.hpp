#ifndef MMX_VECTOR3_HPP
#define MMX_VECTOR3_HPP 1

#include "config.hpp"

#include <ostream>          // << operator
#include <cmath>            // sin, cos, atan2
#include <stdexcept>        // invalid_argument

namespace mmx {

	/**
	 *
	 */
	template <class T>
	class vector3 {
	public:
		MMX_CONSTEXPR vector3(const T a, const T b, const T c) : x(a), y(b), z(c) {}
		MMX_CONSTEXPR vector3(const vector3& v) : x(v.x), y(v.y), z(v.z) {}

		vector3& operator = (const vector3& other) {
			if (this != &other) {
				x = other.x;
				y = other.y;
				z = other.z;
			}
			return *this;
		}

		MMX_CONSTEXPR vector3 operator - () const { return {-x, -y, -z}; }
		MMX_CONSTEXPR vector3 operator + (const vector3& v) const { return {x + v.x, y + v.y, z + v.z}; }
		MMX_CONSTEXPR vector3 operator - (const vector3& v) const { return {x - v.x, y - v.y, z - v.z}; }
		MMX_CONSTEXPR vector3 operator * (const vector3& v) const { return {x * v.x, y * v.y, z * v.z}; }

		vector3 operator / (const vector3& v) const {
			if (v.x == 0 || v.y == 0 || v.z == 0) {
				throw std::invalid_argument("vector3: almost divied by zero!");
			}
			return {x / v.x, y / v.y, z / v.z};
		}

		vector3& operator += (const vector3& v) {
			x += v.x;
			y += v.y;
			z += v.z;
			return *this;
		}

		vector3& operator -= (const vector3& v) {
			x -= v.x;
			y -= v.y;
			z -= v.z;
			return *this;
		}

		vector3& operator *= (const vector3& v) {
			x *= v.x;
			y *= v.y;
			z *= v.z;
			return *this;
		}

		vector3& operator /= (const vector3& v) {
			if (v.x == 0 || v.y == 0 || v.z == 0) {
				throw std::invalid_argument("vector3: almost divied by zero!");
			}
			x /= v.x;
			y /= v.y;
			z /= v.z;
			return *this;
		}

		MMX_CONSTEXPR vector3 operator * (T scalar) const { return {x * scalar, y * scalar, z * scalar}; }

		vector3 operator / (T scalar) const {
			if (scalar == 0) {
				throw std::invalid_argument("vector3: almost divied by zero!");
			}
			return {x / scalar, y / scalar, z / scalar};
		}

		vector3& operator *= (T scalar) const {
			x *= scalar;
			y *= scalar;
			z *= scalar;
			return *this;
		}

		vector3& operator /= (T scalar) const {
			if (scalar == 0) {
				throw std::invalid_argument("vector3: almost divided by zero!");
			}
			x /= scalar;
			y /= scalar;
			z /= scalar;
			return *this;
		}

		MMX_CONSTEXPR bool operator == (const vector3& v) const { return x == v.x && y == v.y && z == v.z; }
		MMX_CONSTEXPR bool operator != (const vector3& v) const { return x != v.x || y != v.y || z != v.z; }

		friend std::ostream& operator << (std::ostream& os, const vector3& v) {
			os << '(' << v.x << ", " << v.y << ", " << v.z << ')';
			return os;
		}

		MMX_CONSTEXPR T dot(const vector3& v) const { return x * v.x + y * v.y + z * v.z; }

		MMX_CONSTEXPR T cross(const vector3& v) const {
			return (y * v.z - z * v.y) + (z * v.x - x * v.z) + (x * v.y - y * v.x);
		}

		MMX_CONSTEXPR T length() const { return std::sqrt(x * x + y * y + z * z); }
		MMX_CONSTEXPR T squared_length() const { return x * x + y * y + z * z; }

		MMX_CONSTEXPR vector3 unit() const { return *this / length(); }

		/** Assumes that y axis points up, otherwise this is turn_right **/
		//MMX_CONSTEXPR vector3 turn_left() const { return {-y, x}; }

		/** Assumes that y axis points up, otherwise this is turn_left **/
		//MMX_CONSTEXPR vector3 turn_right() const { return {y, -x}; }

		//MMX_CONSTEXPR vector3 rotate(double angle) const {
		//	return {x * std::cos(angle) - y * std::sin(angle), x * std::sin(angle) + y * std::cos(angle)};
		//}

		//MMX_CONSTEXPR double angle() const { return std::atan2(y, x); }

		T x;
		T y;
		T z;
	};

	template <class T>
	MMX_CONSTEXPR vector3<T> operator * (T scalar, vector3<T>& v) { return vector3<T>(v.x * scalar, v.y * scalar); }

	typedef vector3<float>  v3f;
	typedef vector3<double> v3d;
	typedef vector3<int>    v3i;
	
	typedef vector3<float>  vec3f;
	typedef vector3<double> vec3d;
	typedef vector3<int>    vec3i;
	
	typedef vector3<float>  vector3f;
	typedef vector3<double> vector3d;
	typedef vector3<int>    vector3i;
	
}           // ~namespace mmx

#endif      // MMX_VECTOR3_HPP

