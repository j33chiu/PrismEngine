#pragma once

#include <assert.h>
#include <type_traits>

#include "prismTypeDef.h"
#include "floatCompare.h"

namespace prism {
namespace pml {

template<typename T>
struct vec<3, T> {
	static_assert(std::is_arithmetic<T>::value, "type parameter of this class must be arithmetic");
	union {T x; T r;};
	union {T y; T g;};
	union {T z; T b;};

	// basic constructors 
	constexpr vec(T x, T y, T z) 
		: x(x)
		, y(y)
		, z(z)
	{}

	constexpr vec(vec<1, T> const& v) 
		: x(v.x)
		, y(0)
		, z(0)
	{}

	constexpr vec(vec<2, T> const& v) 
		: x(v.x)
		, y(v.y)
		, z(0)
	{}

	constexpr vec(vec<3, T> const& v) 
		: x(v.x)
		, y(v.y)
		, z(v.z)
	{}

	constexpr vec(vec<4, T> const& v) 
		: x(v.x)
		, y(v.y)
		, z(v.z)
	{}


	constexpr vec()
		: x(static_cast<T>(0))
		, y(static_cast<T>(0))
		, z(static_cast<T>(0))
	{}

	//constexpr vec(vec const& v) = default;

	// conversion constructors from other vec types and scalar types
    template<typename A>
    constexpr vec(A scalar) 
		: x(static_cast<T>(scalar))
		, y(static_cast<T>(scalar))
		, z(static_cast<T>(scalar))
	{}

	template<typename A, typename B, typename C>
    constexpr vec(A scalar1, B scalar2, C scalar3) 
		: x(static_cast<T>(scalar1))
		, y(static_cast<T>(scalar2))
		, z(static_cast<T>(scalar3))
	{}

	template<typename A, typename B, typename C>
    constexpr vec(vec<1, A> const& v, B scalar1, C scalar2) 
		: x(static_cast<T>(v.x))
		, y(static_cast<T>(scalar1))
		, z(static_cast<T>(scalar2))
	{}

	template<typename A, typename B, typename C>
    constexpr vec(A scalar1, vec<1, B> const& v, C scalar2) 
		: x(static_cast<T>(scalar1))
		, y(static_cast<T>(v.x))
		, z(static_cast<T>(scalar2))
	{}

	template<typename A, typename B, typename C>
    constexpr vec(A scalar1, B scalar2, vec<1, C> const& v) 
		: x(static_cast<T>(scalar1))
		, y(static_cast<T>(scalar2))
		, z(static_cast<T>(v.x))
	{}

	template<typename A, typename B, typename C>
    constexpr vec(vec<1, A> const& v1, vec<1, B> const& v2, C scalar) 
		: x(static_cast<T>(v1.x))
		, y(static_cast<T>(v2.x))
		, z(static_cast<T>(scalar))
	{}

	template<typename A, typename B, typename C>
    constexpr vec(vec<1, A> const& v1, B scalar, vec<1, C> const& v2) 
		: x(static_cast<T>(v1.x))
		, y(static_cast<T>(scalar))
		, z(static_cast<T>(v2.x))
	{}

	template<typename A, typename B, typename C>
    constexpr vec(A scalar, vec<1, B> const& v1, vec<1, C> const& v2) 
		: x(static_cast<T>(scalar))
		, y(static_cast<T>(v1.x))
		, z(static_cast<T>(v2.x))
	{}

	template<typename A, typename B, typename C>
    constexpr vec(vec<1, A> const& v1, vec<1, B> const& v2, vec<1, C> const& v3) 
		: x(static_cast<T>(v1.x))
		, y(static_cast<T>(v2.x))
		, z(static_cast<T>(v3.x))
	{}

	template<typename A, typename B>
    constexpr vec(vec<2, A> const& v1, B scalar) 
		: x(static_cast<T>(v1.x))
		, y(static_cast<T>(v1.y))
		, z(static_cast<T>(scalar))
	{}

	template<typename A, typename B>
    constexpr vec(vec<2, A> const& v1, vec<1, B> const& v2) 
		: x(static_cast<T>(v1.x))
		, y(static_cast<T>(v1.y))
		, z(static_cast<T>(v2.x))
	{}

	template<typename A, typename B>
    constexpr vec(A scalar, vec<2, B> const& v1) 
		: x(static_cast<T>(scalar))
		, y(static_cast<T>(v1.x))
		, z(static_cast<T>(v1.y))
	{}

	template<typename A, typename B>
    constexpr vec(vec<1, A> const& v1, vec<2, B> const& v2) 
		: x(static_cast<T>(v1.x))
		, y(static_cast<T>(v2.x))
		, z(static_cast<T>(v2.y))
	{}

    template<typename A>
    constexpr vec(vec<1, A> const& v) 
		: x(static_cast<T>(v.x))
		, y(static_cast<T>(0))
		, z(static_cast<T>(0))
	{}

	template<typename A>
    constexpr vec(vec<2, A> const& v) 
		: x(static_cast<T>(v.x))
		, y(static_cast<T>(v.y))
		, z(static_cast<T>(0))
	{}

    template<typename A>
    constexpr vec(vec<3, A> const& v) 
		: x(static_cast<T>(v.x))
		, y(static_cast<T>(v.y))
		, z(static_cast<T>(v.z))
	{}

    template<typename A>
    constexpr vec(vec<4, A> const& v) 
		: x(static_cast<T>(v.x))
		, y(static_cast<T>(v.y))
		, z(static_cast<T>(v.z))
	{}

	// length of vector
	static constexpr int size() {
		return 3;
	}

	// get and set with []:
    constexpr T &operator[](int i) {
        assert(i >= 0 && i < size());
        switch(i) {
            default:
            case 0:
                return x;
			case 1:
				return y;
			case 2:
				return z;
        }
    }

    constexpr const T &operator[](int i) const {
        assert(i >= 0 && i < size());
        switch(i) {
            default:
            case 0:
                return x;
			case 1:
				return y;
			case 2:
				return z;
        }
    }

	// math operations:
    constexpr vec<3, T> &operator=(vec const& v) = default;

    template<typename A>
    constexpr vec<3, T> &operator=(vec<3, A> const& v) {
        x = static_cast<T>(v.x);
		y = static_cast<T>(v.y);
		z = static_cast<T>(v.z);
        return *this;
    }

	constexpr vec<3, T> &operator=(T scalar) {
        x = scalar;
		y = scalar;
		z = scalar;
        return *this;
    }

	template<typename A>
    constexpr vec<3, T> &operator=(A scalar) {
        x = static_cast<T>(scalar);
		y = static_cast<T>(scalar);
		z = static_cast<T>(scalar);
        return *this;
    }
    
    // element-wise +=
    template<typename A>
    constexpr vec<3, T> &operator+=(vec<1, A> const& v) {
        x += static_cast<T>(v.x);
        return *this;
    }

    template<typename A>
    constexpr vec<3, T> &operator+=(A scalar) {
        x += static_cast<T>(scalar);
		y += static_cast<T>(scalar);
		z += static_cast<T>(scalar);
        return *this;
    }

	template<typename A>
    constexpr vec<3, T> &operator+=(vec<2, A> const& v) {
        x += static_cast<T>(v.x);
		y += static_cast<T>(v.y);
        return *this;
    }

	template<typename A>
    constexpr vec<3, T> &operator+=(vec<3, A> const& v) {
        x += static_cast<T>(v.x);
		y += static_cast<T>(v.y);
		z += static_cast<T>(v.z);
        return *this;
    }

    // element-wise -=
    template<typename A>
    constexpr vec<3, T> &operator-=(vec<1, A> const& v) {
        x -= static_cast<T>(v.x);
        return *this;
    }

    template<typename A>
    constexpr vec<3, T> &operator-=(A scalar) {
        x -= static_cast<T>(scalar);
		y -= static_cast<T>(scalar);
		z -= static_cast<T>(scalar);
        return *this;
    }

	template<typename A>
    constexpr vec<3, T> &operator-=(vec<2, A> const& v) {
        x -= static_cast<T>(v.x);
		y -= static_cast<T>(v.y);
        return *this;
    }

	template<typename A>
    constexpr vec<3, T> &operator-=(vec<3, A> const& v) {
        x -= static_cast<T>(v.x);
		y -= static_cast<T>(v.y);
		z -= static_cast<T>(v.z);
        return *this;
    }

    // element-wise *=
    template<typename A>
    constexpr vec<3, T> &operator*=(vec<1, A> const& v) {
        x *= static_cast<T>(v.x);
		y = 0;
		z = 0;
        return *this;
    }

    template<typename A>
    constexpr vec<3, T> &operator*=(A scalar) {
        x *= static_cast<T>(scalar);
		y *= static_cast<T>(scalar);
		z *= static_cast<T>(scalar);
        return *this;
    }

	template<typename A>
    constexpr vec<3, T> &operator*=(vec<2, A> const& v) {
        x *= static_cast<T>(v.x);
		y *= static_cast<T>(v.y);
		z = 0;
        return *this;
    }

	template<typename A>
    constexpr vec<3, T> &operator*=(vec<3, A> const& v) {
        x *= static_cast<T>(v.x);
		y *= static_cast<T>(v.y);
		z *= static_cast<T>(v.z);
        return *this;
    }

    // element-wise /=
    template<typename A>
    constexpr vec<3, T> &operator/=(A scalar) {
        x /= static_cast<T>(scalar);
		y /= static_cast<T>(scalar);
		z /= static_cast<T>(scalar);
        return *this;
    }

	template<typename A>
    constexpr vec<3, T> &operator/=(vec<3, A> const& v) {
        x /= static_cast<T>(v.x);
		y /= static_cast<T>(v.y);
		z /= static_cast<T>(v.z);
        return *this;
    }

    // element-wise %=
    template<typename A>
    constexpr vec<3, T> &operator%=(A scalar) {
        x %= scalar;
		y %= scalar;
		z %= scalar;
        return *this;
    }

	template<typename A>
    constexpr vec<3, T> &operator%=(vec<3, A> const& v) {
        x %= v.x;
		y %= v.y;
		z %= v.z;
        return *this;
    }

    // element-wise &=
    template<typename A>
    constexpr vec<3, T> &operator&=(vec<1, A> const& v) {
        x &= v.x;
		y = 0;
		z = 0;
        return *this;
    }

    template<typename A>
    constexpr vec<3, T> &operator&=(A scalar) {
        x &= scalar;
		y &= scalar;
		z &= scalar;
        return *this;
    }

	template<typename A>
    constexpr vec<3, T> &operator&=(vec<2, A> const& v) {
        x &= v.x;
		y &= v.y;
		z = 0;
        return *this;
    }

	template<typename A>
    constexpr vec<3, T> &operator&=(vec<3, A> const& v) {
        x &= v.x;
		y &= v.y;
		z &= v.z;
        return *this;
    }

    // element-wise |=
    template<typename A>
    constexpr vec<3, T> &operator|=(vec<1, A> const& v) {
        x |= v.x;
        return *this;
    }

    template<typename A>
    constexpr vec<3, T> &operator|=(A scalar) {
        x |= scalar;
		y |= scalar;
		z |= scalar;
        return *this;
    }

	template<typename A>
    constexpr vec<3, T> &operator|=(vec<2, A> const& v) {
        x |= v.x;
		y |= v.y;
        return *this;
    }

	template<typename A>
    constexpr vec<3, T> &operator|=(vec<3, A> const& v) {
        x |= v.x;
		y |= v.y;
		z |= v.z;
        return *this;
    }

    // element-wise ^=
    template<typename A>
    constexpr vec<3, T> &operator^=(vec<1, A> const& v) {
        x ^= v.x;
        return *this;
    }

    template<typename A>
    constexpr vec<3, T> &operator^=(A scalar) {
        x ^= scalar;
		y ^= scalar;
		z ^= scalar;
        return *this;
    }

	template<typename A>
    constexpr vec<3, T> &operator^=(vec<2, A> const& v) {
        x ^= v.x;
		y ^= v.y;
        return *this;
    }

	template<typename A>
    constexpr vec<3, T> &operator^=(vec<3, A> const& v) {
        x ^= v.x;
		y ^= v.y;
		z ^= v.z;
        return *this;
    }

    // element-wise <<=
    template<typename A>
    constexpr vec<3, T> &operator<<=(vec<1, A> const& v) {
        x <<= static_cast<T>(v.x);
        return *this;
    }

    template<typename A>
    constexpr vec<3, T> &operator<<=(A scalar) {
        x <<= static_cast<T>(scalar);
		y <<= static_cast<T>(scalar);
		z <<= static_cast<T>(scalar);
        return *this;
    }

	template<typename A>
    constexpr vec<3, T> &operator<<=(vec<2, A> const& v) {
        x <<= static_cast<T>(v.x);
		y <<= static_cast<T>(v.y);
        return *this;
    }

	template<typename A>
    constexpr vec<3, T> &operator<<=(vec<3, A> const& v) {
        x <<= static_cast<T>(v.x);
		y <<= static_cast<T>(v.y);
		z <<= static_cast<T>(v.z);
        return *this;
    }

    // element-wise >>=
    template<typename A>
    constexpr vec<3, T> &operator>>=(vec<1, A> const& v) {
        x >>= static_cast<T>(v.x);
        return *this;
    }

    template<typename A>
    constexpr vec<3, T> &operator>>=(A scalar) {
        x >>= static_cast<T>(scalar);
		y >>= static_cast<T>(scalar);
		z >>= static_cast<T>(scalar);
        return *this;
    }

	template<typename A>
    constexpr vec<3, T> &operator>>=(vec<2, A> const& v) {
        x >>= static_cast<T>(v.x);
		y >>= static_cast<T>(v.y);
        return *this;
    }

	template<typename A>
    constexpr vec<3, T> &operator>>=(vec<3, A> const& v) {
        x >>= static_cast<T>(v.x);
		y >>= static_cast<T>(v.y);
		z >>= static_cast<T>(v.z);
        return *this;
    }


    // increment and decrement
    // ++vec , --vec
    constexpr vec<3, T> &operator++() {
        ++x;
		++y;
		++z;
        return *this;
    }

    constexpr vec<3, T> &operator--() {
        --x;
		--y;
		--z;
        return *this;
    }

    // vec++ , vec--
    constexpr vec<3, T> operator++(int) {
        vec<3, T> out(*this);
        ++(*this);
        return out;
    }

    constexpr vec<3, T> operator--(int) {
        vec<3, T> out(*this);
        --(*this);
        return out;
    }

    // unary + operator 
    constexpr vec<3, T> operator+() const {
        return vec<3, T>(x, y, z);
    }

    // unary - operator
    constexpr vec<3, T> operator-() const {
        return vec<3, T>(-x, -y, -z);
    }

    // binary math operations
    // binary addition (+)
    template<typename A>
    constexpr vec<3, T> operator+(vec<1, A> const& v) const {
        return vec<3, T>(
			x + static_cast<T>(v.x), 
			y,
			z
		);
    }

    template<typename A>
    constexpr vec<3, T> operator+(A scalar) const {
        return vec<3, T>(
			x + static_cast<T>(scalar),
			y + static_cast<T>(scalar),
			z + static_cast<T>(scalar)
		);
    }

	template<typename A>
	constexpr vec<3, T> operator+(vec<2, A> const& v) const {
        return vec<3, T>(
			x + static_cast<T>(v.x), 
			y + static_cast<T>(v.y),
			z
		);
    }

	template<typename A>
	constexpr vec<3, T> operator+(vec<3, A> const& v) const {
        return vec<3, T>(
			x + static_cast<T>(v.x), 
			y + static_cast<T>(v.y),
			z + static_cast<T>(v.z)
		);
    }

    // binary subtraction (-)
    template<typename A>
    constexpr vec<3, T> operator-(vec<1, A> const& v) const {
        return vec<3, T>(
			x - static_cast<T>(v.x), 
			y,
			z
		);
    }

    template<typename A>
    constexpr vec<3, T> operator-(A scalar) const {
        return vec<3, T>(
			x - static_cast<T>(scalar),
			y - static_cast<T>(scalar),
			z - static_cast<T>(scalar)
		);
    }

	template<typename A>
	constexpr vec<3, T> operator-(vec<2, A> const& v) const {
        return vec<3, T>(
			x - static_cast<T>(v.x), 
			y - static_cast<T>(v.y),
			z
		);
    }

	template<typename A>
	constexpr vec<3, T> operator-(vec<3, A> const& v) const {
        return vec<3, T>(
			x - static_cast<T>(v.x), 
			y - static_cast<T>(v.y),
			z - static_cast<T>(v.z)
		);
    }

    // binary multiplication (*)
    template<typename A>
    constexpr vec<3, T> operator*(vec<1, A> const& v) const {
        return vec<3, T>(
			x * static_cast<T>(v.x), 
			0,
			0
		);
    }

    template<typename A>
    constexpr vec<3, T> operator*(A scalar) const {
        return vec<3, T>(
			x * static_cast<T>(scalar),
			y * static_cast<T>(scalar),
			z * static_cast<T>(scalar)
		);
    }

	template<typename A>
	constexpr vec<3, T> operator*(vec<2, A> const& v) const {
        return vec<3, T>(
			x * static_cast<T>(v.x), 
			y * static_cast<T>(v.y),
			0
		);
    }

	template<typename A>
	constexpr vec<3, T> operator*(vec<3, A> const& v) const {
        return vec<3, T>(
			x * static_cast<T>(v.x), 
			y * static_cast<T>(v.y),
			z * static_cast<T>(v.z)
		);
    }

    // binary division (/)
    template<typename A>
    constexpr vec<3, T> operator/(A scalar) const {
        return vec<3, T>(
			x / static_cast<T>(scalar),
			y / static_cast<T>(scalar),
			z / static_cast<T>(scalar)
		);
    }

	template<typename A>
	constexpr vec<3, T> operator/(vec<3, A> const& v) const {
        return vec<3, T>(
			x / static_cast<T>(v.x), 
			y / static_cast<T>(v.y),
			z / static_cast<T>(v.z)
		);
    }

    // binary modulo (%)
    template<typename A>
    constexpr vec<3, T> operator%(A scalar) const {
        return vec<3, T>(
			x % static_cast<T>(scalar),
			y % static_cast<T>(scalar),
			z % static_cast<T>(scalar)
		);
    }

	template<typename A>
	constexpr vec<3, T> operator%(vec<3, A> const& v) const {
        return vec<3, T>(
			x % static_cast<T>(v.x), 
			y % static_cast<T>(v.y),
			z % static_cast<T>(v.z)
		);
    }

    // binary and (&)
    template<typename A>
    constexpr vec<3, T> operator&(vec<1, A> const& v) const {
        return vec<3, T>(
			x & static_cast<T>(v.x), 
			0,
			0
		);
    }

    template<typename A>
    constexpr vec<3, T> operator&(A scalar) const {
        return vec<3, T>(
			x & static_cast<T>(scalar),
			y & static_cast<T>(scalar),
			z & static_cast<T>(scalar)
		);
    }

	template<typename A>
	constexpr vec<3, T> operator&(vec<2, A> const& v) const {
        return vec<3, T>(
			x & static_cast<T>(v.x), 
			y & static_cast<T>(v.y),
			0
		);
    }

	template<typename A>
	constexpr vec<3, T> operator&(vec<3, A> const& v) const {
        return vec<3, T>(
			x & static_cast<T>(v.x), 
			y & static_cast<T>(v.y),
			z & static_cast<T>(v.z)
		);
    }

    // binary or (|)
    template<typename A>
    constexpr vec<3, T> operator|(vec<1, A> const& v) const {
        return vec<3, T>(
			x | static_cast<T>(v.x), 
			y,
			z
		);
    }

    template<typename A>
    constexpr vec<3, T> operator|(A scalar) const {
        return vec<3, T>(
			x | static_cast<T>(scalar),
			y | static_cast<T>(scalar),
			z | static_cast<T>(scalar)
		);
    }

	template<typename A>
	constexpr vec<3, T> operator|(vec<2, A> const& v) const {
        return vec<3, T>(
			x | static_cast<T>(v.x), 
			y | static_cast<T>(v.y),
			z
		);
    }

	template<typename A>
	constexpr vec<3, T> operator|(vec<3, A> const& v) const {
        return vec<3, T>(
			x | static_cast<T>(v.x), 
			y | static_cast<T>(v.y),
			z | static_cast<T>(v.z)
		);
    }

    // binary xor (^)
    template<typename A>
    constexpr vec<3, T> operator^(vec<1, A> const& v) const {
        return vec<3, T>(
			x ^ static_cast<T>(v.x), 
			y,
			z
		);
    }

    template<typename A>
    constexpr vec<3, T> operator^(A scalar) const {
        return vec<3, T>(
			x ^ static_cast<T>(scalar),
			y ^ static_cast<T>(scalar),
			z ^ static_cast<T>(scalar)
		);
    }

	template<typename A>
	constexpr vec<3, T> operator^(vec<2, A> const& v) const {
        return vec<3, T>(
			x ^ static_cast<T>(v.x), 
			y ^ static_cast<T>(v.y),
			z
		);
    }

	template<typename A>
	constexpr vec<3, T> operator^(vec<3, A> const& v) const {
        return vec<3, T>(
			x ^ static_cast<T>(v.x), 
			y ^ static_cast<T>(v.y),
			z ^ static_cast<T>(v.z)
		);
    }

    // binary left shift (<<)
    template<typename A>
    constexpr vec<3, T> operator<<(vec<1, A> const& v) const {
        return vec<3, T>(
			x << static_cast<T>(v.x), 
			y,
			z
		);
    }

    template<typename A>
    constexpr vec<3, T> operator<<(A scalar) const {
        return vec<3, T>(
			x << static_cast<T>(scalar),
			y << static_cast<T>(scalar),
			z << static_cast<T>(scalar)
		);
    }

	template<typename A>
	constexpr vec<3, T> operator<<(vec<2, A> const& v) const {
        return vec<3, T>(
			x << static_cast<T>(v.x), 
			y << static_cast<T>(v.y),
			z
		);
    }

	template<typename A>
	constexpr vec<3, T> operator<<(vec<3, A> const& v) const {
        return vec<3, T>(
			x << static_cast<T>(v.x), 
			y << static_cast<T>(v.y),
			z << static_cast<T>(v.z)
		);
    }

    // binary right shift (>>)
    template<typename A>
    constexpr vec<3, T> operator>>(vec<1, A> const& v) const {
        return vec<3, T>(
			x >> static_cast<T>(v.x), 
			y,
			z
		);
    }

    template<typename A>
    constexpr vec<3, T> operator>>(A scalar) const {
        return vec<3, T>(
			x >> static_cast<T>(scalar),
			y >> static_cast<T>(scalar),
			z >> static_cast<T>(scalar)
		);
    }

	template<typename A>
	constexpr vec<3, T> operator>>(vec<2, A> const& v) const {
        return vec<3, T>(
			x >> static_cast<T>(v.x), 
			y >> static_cast<T>(v.y),
			z
		);
    }

	template<typename A>
	constexpr vec<3, T> operator>>(vec<3, A> const& v) const {
        return vec<3, T>(
			x >> static_cast<T>(v.x), 
			y >> static_cast<T>(v.y),
			z >> static_cast<T>(v.z)
		);
    }

    // binary not (~)
    template<typename A>
    constexpr vec<3, T> operator~() const {
        return vec<3, T>(~x, ~y, ~z);
    }

    // boolean and compares
    template<typename A>
    bool operator==(A scalar) {
        return 
			equal(x, static_cast<T>(scalar)) && 
			equal(y, static_cast<T>(scalar)) && 
			equal(z, static_cast<T>(scalar));
    }

	template<typename A>
    bool operator==(vec<3, A> const& v) {
        return 
			equal(x, static_cast<T>(v.x)) &&
			equal(y, static_cast<T>(v.y)) &&
			equal(z, static_cast<T>(v.z));
    }

    template<typename A>
    constexpr bool operator!=(A scalar) {
        return !(*this == scalar);
    }

	template<typename A>
    constexpr bool operator!=(vec<3, A> const& v) {
        return !(*this == v);
    }

    constexpr vec<3, bool> operator&&(bool a) {
        return vec<3, bool>(
			x && a,
			y && a,
			z && a
		);
    }

	constexpr vec<3, bool> operator&&(vec<1, bool> const& v) {
        return vec<3, bool>(
			x && v.x,
			0,
			0
		);
    }

	constexpr vec<3, bool> operator&&(vec<2, bool> const& v) {
        return vec<3, bool>(
			x && v.x,
			y && v.y,
			0
		);
    }

    constexpr vec<3, bool> operator||(bool a) {
        return vec<3, bool>(
			x || a,
			y || a,
			z || a
		);
    }

	constexpr vec<3, bool> operator||(vec<1, bool> const& v) {
        return vec<3, bool>(
			x || v.x,
			y,
			z
		);
    }

	constexpr vec<3, bool> operator||(vec<2, bool> const& v) {
        return vec<3, bool>(
			x || v.x,
			y || v.y,
			z
		);
    }
};

// scalar <math operation> vec1 overloads:
template<typename T, typename A>
constexpr vec<3, T> operator+(A scalar, vec<3, T> const& v) {
    return vec<3, T>(
		static_cast<T>(scalar) + v.x,
		static_cast<T>(scalar) + v.y,
		static_cast<T>(scalar) + v.z
	);
}

template<typename T, typename A>
constexpr vec<3, T> operator+(vec<1, A> const& v1, vec<3, T> const& v2) {
    return vec<3, T>(
		static_cast<T>(v1.x) + v2.x,
		v2.y,
		v2.z
	);
}

template<typename T, typename A>
constexpr vec<3, T> operator+(vec<2, A> const& v1, vec<3, T> const& v2) {
    return vec<3, T>(
		static_cast<T>(v1.x) + v2.x,
		static_cast<T>(v1.y) + v2.y,
		v2.z
	);
}

template<typename T, typename A>
constexpr vec<3, T> operator-(A scalar, vec<3, T> const& v) {
    return vec<3, T>(
		static_cast<T>(scalar) - v.x,
		static_cast<T>(scalar) - v.y,
		static_cast<T>(scalar) - v.z
	);
}

template<typename T, typename A>
constexpr vec<3, T> operator-(vec<1, A> const& v1, vec<3, T> const& v2) {
    return vec<3, T>(
		static_cast<T>(v1.x) - v2.x,
		-v2.y,
		-v2.z
	);
}

template<typename T, typename A>
constexpr vec<3, T> operator-(vec<2, A> const& v1, vec<3, T> const& v2) {
    return vec<3, T>(
		static_cast<T>(v1.x) - v2.x,
		static_cast<T>(v1.y) - v2.y,
		-v2.z
	);
}

template<typename T, typename A>
constexpr vec<3, T> operator*(A scalar, vec<3, T> const& v) {
    return vec<3, T>(
		static_cast<T>(scalar) * v.x,
		static_cast<T>(scalar) * v.y,
		static_cast<T>(scalar) * v.z
	);
}

template<typename T, typename A>
constexpr vec<3, T> operator*(vec<1, A> const& v1, vec<3, T> const& v2) {
    return vec<3, T>(
		static_cast<T>(v1.x) * v2.x,
		0,
		0
	);
}

template<typename T, typename A>
constexpr vec<3, T> operator*(vec<2, A> const& v1, vec<3, T> const& v2) {
    return vec<3, T>(
		static_cast<T>(v1.x) * v2.x,
		static_cast<T>(v1.y) * v2.y,
		0
	);
}

template<typename T, typename A>
constexpr vec<3, T> operator/(A scalar, vec<3, T> const& v) {
    return vec<3, T>(
		static_cast<T>(scalar) / v.x,
		static_cast<T>(scalar) / v.y,
		static_cast<T>(scalar) / v.z
	);
}

template<typename T, typename A>
constexpr vec<3, T> operator/(vec<1, A> const& v1, vec<3, T> const& v2) {
    return vec<3, T>(
		static_cast<T>(v1.x) / v2.x,
		0,
		0
	);
}

template<typename T, typename A>
constexpr vec<3, T> operator/(vec<2, A> const& v1, vec<3, T> const& v2) {
    return vec<3, T>(
		static_cast<T>(v1.x) / v2.x,
		static_cast<T>(v1.y) / v2.y,
		0
	);
}

template<typename T, typename A>
constexpr vec<3, T> operator%(A scalar, vec<3, T> const& v) {
    return vec<3, T>(
		static_cast<T>(scalar) % v.x,
		static_cast<T>(scalar) % v.y,
		static_cast<T>(scalar) % v.z
	);
}

template<typename T, typename A>
constexpr vec<3, T> operator%(vec<1, A> const& v1, vec<3, T> const& v2) {
    return vec<3, T>(
		static_cast<T>(v1.x) % v2.x,
		0,
		0
	);
}

template<typename T, typename A>
constexpr vec<3, T> operator%(vec<2, A> const& v1, vec<3, T> const& v2) {
    return vec<3, T>(
		static_cast<T>(v1.x) % v2.x,
		static_cast<T>(v1.y) % v2.y,
		0
	);
}

template<typename T, typename A>
constexpr vec<3, T> operator&(A scalar, vec<3, T> const& v) {
    return vec<3, T>(
		static_cast<T>(scalar) & v.x,
		static_cast<T>(scalar) & v.y,
		static_cast<T>(scalar) & v.z
	);
}

template<typename T, typename A>
constexpr vec<3, T> operator&(vec<1, A> const& v1, vec<3, T> const& v2) {
    return vec<3, T>(
		static_cast<T>(v1.x) & v2.x,
		0,
		0
	);
}

template<typename T, typename A>
constexpr vec<3, T> operator&(vec<2, A> const& v1, vec<3, T> const& v2) {
    return vec<3, T>(
		static_cast<T>(v1.x) & v2.x,
		static_cast<T>(v1.y) & v2.y,
		0
	);
}

template<typename T, typename A>
constexpr vec<3, T> operator|(A scalar, vec<3, T> const& v) {
    return vec<3, T>(
		static_cast<T>(scalar) | v.x,
		static_cast<T>(scalar) | v.y,
		static_cast<T>(scalar) | v.z
	);
}

template<typename T, typename A>
constexpr vec<3, T> operator|(vec<1, A> const& v1, vec<3, T> const& v2) {
    return vec<3, T>(
		static_cast<T>(v1.x) | v2.x,
		v2.y,
		v2.z
	);
}

template<typename T, typename A>
constexpr vec<3, T> operator|(vec<2, A> const& v1, vec<3, T> const& v2) {
    return vec<3, T>(
		static_cast<T>(v1.x) | v2.x,
		static_cast<T>(v1.y) | v2.y,
		v2.z
	);
}

template<typename T, typename A>
constexpr vec<3, T> operator^(A scalar, vec<3, T> const& v) {
    return vec<3, T>(
		static_cast<T>(scalar) ^ v.x,
		static_cast<T>(scalar) ^ v.y,
		static_cast<T>(scalar) ^ v.z
	);
}

template<typename T, typename A>
constexpr vec<3, T> operator^(vec<1, A> const& v1, vec<3, T> const& v2) {
    return vec<3, T>(
		static_cast<T>(v1.x) ^ v2.x,
		v2.y,
		v2.z
	);
}

template<typename T, typename A>
constexpr vec<3, T> operator^(vec<2, A> const& v1, vec<3, T> const& v2) {
    return vec<3, T>(
		static_cast<T>(v1.x) ^ v2.x,
		static_cast<T>(v1.y) ^ v2.y,
		v2.z
	);
}


template<typename T, typename A>
constexpr vec<3, T> operator<<(A scalar, vec<3, T> const& v) {
    return vec<3, T>(
		static_cast<T>(scalar) << v.x,
		static_cast<T>(scalar) << v.y,
		static_cast<T>(scalar) << v.z
	);
}

template<typename T, typename A>
constexpr vec<3, T> operator<<(vec<1, A> const& v1, vec<3, T> const& v2) {
    return vec<3, T>(
		static_cast<T>(v1.x) << v2.x,
		0 << v2.y,
		0 << v2.z
	);
}

template<typename T, typename A>
constexpr vec<3, T> operator<<(vec<2, A> const& v1, vec<3, T> const& v2) {
    return vec<3, T>(
		static_cast<T>(v1.x) << v2.x,
		static_cast<T>(v1.y) << v2.y,
		0 << v2.z
	);
}

template<typename T, typename A>
constexpr vec<3, T> operator>>(A scalar, vec<3, T> const& v) {
    return vec<3, T>(
		static_cast<T>(scalar) >> v.x,
		static_cast<T>(scalar) >> v.y,
		static_cast<T>(scalar) >> v.z
	);
}

template<typename T, typename A>
constexpr vec<3, T> operator>>(vec<1, A> const& v1, vec<3, T> const& v2) {
    return vec<3, T>(
		static_cast<T>(v1.x) >> v2.x,
		0 >> v2.y,
		0 >> v2.z
	);
}

template<typename T, typename A>
constexpr vec<3, T> operator>>(vec<2, A> const& v1, vec<3, T> const& v2) {
    return vec<3, T>(
		static_cast<T>(v1.x) >> v2.x,
		static_cast<T>(v1.y) >> v2.y,
		0 >> v2.z
	);
}

constexpr vec<3, bool> operator&&(bool a, vec<3, bool> const& v) {
    return vec<3, bool>(
		a && v.x,
		a && v.y,
		a && v.z
	);
}

constexpr vec<3, bool> operator&&(vec<3, bool> const& v1, vec<3, bool> const& v2) {
	return vec<3, bool>(
		v1.x && v2.x,
		v1.y && v2.y,
		v1.z && v2.z
	);
}

constexpr vec<3, bool> operator||(bool a, vec<3, bool> const& v) {
    return vec<3, bool>(
		a || v.x,
		a || v.y,
		a || v.z
	);
}

constexpr vec<3, bool> operator||(vec<3, bool> const& v1, vec<3, bool> const& v2) {
	return vec<3, bool>(
		v1.x || v2.x,
		v1.y || v2.y,
		v1.z || v2.z
	);
}

}
}
