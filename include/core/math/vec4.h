#pragma once

#include <assert.h>
#include <type_traits>

#include "prismTypeDef.h"
#include "floatCompare.h"

namespace prism {
namespace pml {

template<typename T>
struct vec<4, T> {
	static_assert(std::is_arithmetic<T>::value, "type parameter of this class must be arithmetic");
	union {T x; T r;};
	union {T y; T g;};
	union {T z; T b;};
	union {T w; T a;};

	// basic constructors 
	constexpr vec(T x, T y, T z, T w) 
		: x(x)
		, y(y)
		, z(z)
		, w(w)
	{}

	constexpr vec(vec<1, T> const& v) 
		: x(v.x)
		, y(0)
		, z(0)
		, w(0)
	{}

	constexpr vec(vec<2, T> const& v) 
		: x(v.x)
		, y(v.y)
		, z(0)
		, w(0)
	{}

	constexpr vec(vec<3, T> const& v) 
		: x(v.x)
		, y(v.y)
		, z(v.z)
		, w(0)
	{}

	constexpr vec(vec<4, T> const& v) 
		: x(v.x)
		, y(v.y)
		, z(v.z)
		, w(v.w)
	{}

	constexpr vec()
		: x(0)
		, y(0)
		, z(0)
		, w(0)
	{}

	//constexpr vec(vec const& v) = default;

	// conversion constructors from other vec types and scalar types
    template<typename A>
    constexpr vec(A scalar) 
		: x(static_cast<T>(scalar))
		, y(static_cast<T>(scalar))
		, z(static_cast<T>(scalar))
		, w(static_cast<T>(scalar))
	{}

	template<typename A, typename B, typename C, typename D>
    constexpr vec(A scalar1, B scalar2, C scalar3, D scalar4) 
		: x(static_cast<T>(scalar1))
		, y(static_cast<T>(scalar2))
		, z(static_cast<T>(scalar3))
		, w(static_cast<T>(scalar4))
	{}

	template<typename A, typename B, typename C, typename D>
    constexpr vec(vec<1, A> const& v, B scalar1, C scalar2, D scalar3) 
		: x(static_cast<T>(v.x))
		, y(static_cast<T>(scalar1))
		, z(static_cast<T>(scalar2))
		, w(static_cast<T>(scalar3))
	{}

	template<typename A, typename B, typename C, typename D>
    constexpr vec(A scalar1, vec<1, B> const& v, C scalar2, D scalar3) 
		: x(static_cast<T>(scalar1))
		, y(static_cast<T>(v.x))
		, z(static_cast<T>(scalar2))
		, w(static_cast<T>(scalar3))
	{}

	template<typename A, typename B, typename C, typename D>
    constexpr vec(A scalar1, B scalar2, vec<1, C> const& v, D scalar3) 
		: x(static_cast<T>(scalar1))
		, y(static_cast<T>(scalar2))
		, z(static_cast<T>(v.x))
		, w(static_cast<T>(scalar3))
	{}

	template<typename A, typename B, typename C, typename D>
    constexpr vec(A scalar1, B scalar2, C scalar3, vec<1, D> const& v) 
		: x(static_cast<T>(scalar1))
		, y(static_cast<T>(scalar2))
		, z(static_cast<T>(scalar3))
		, w(static_cast<T>(v.x))
	{}

	template<typename A, typename B, typename C, typename D>
    constexpr vec(vec<1, A> const& v1, vec<1, B> const& v2, C scalar1, D scalar2) 
		: x(static_cast<T>(v1.x))
		, y(static_cast<T>(v2.x))
		, z(static_cast<T>(scalar1))
		, w(static_cast<T>(scalar2))
	{}

	template<typename A, typename B, typename C, typename D>
    constexpr vec(vec<1, A> const& v1, B scalar1, vec<1, C> const& v2, D scalar2) 
		: x(static_cast<T>(v1.x))
		, y(static_cast<T>(scalar1))
		, z(static_cast<T>(v2.x))
		, w(static_cast<T>(scalar2))
	{}

	template<typename A, typename B, typename C, typename D>
    constexpr vec(vec<1, A> const& v1, B scalar1, C scalar2, vec<1, D> const& v2) 
		: x(static_cast<T>(v1.x))
		, y(static_cast<T>(scalar1))
		, z(static_cast<T>(scalar2))
		, w(static_cast<T>(v2.x))
	{}

	template<typename A, typename B, typename C, typename D>
    constexpr vec(A scalar1, vec<1, B> const& v1, vec<1, C> const& v2, D scalar2) 
		: x(static_cast<T>(scalar1))
		, y(static_cast<T>(v1.x))
		, z(static_cast<T>(v2.x))
		, w(static_cast<T>(scalar2))
	{}

	template<typename A, typename B, typename C, typename D>
    constexpr vec(A scalar1, vec<1, B> const& v1, C scalar2, vec<1, D> const& v2) 
		: x(static_cast<T>(scalar1))
		, y(static_cast<T>(v1.x))
		, z(static_cast<T>(scalar2))
		, w(static_cast<T>(v2.x))
	{}

	template<typename A, typename B, typename C, typename D>
    constexpr vec(A scalar1, B scalar2, vec<1, C> const& v1, vec<1, D> const& v2) 
		: x(static_cast<T>(scalar1))
		, y(static_cast<T>(scalar2))
		, z(static_cast<T>(v1.x))
		, w(static_cast<T>(v2.x))
	{}

	template<typename A, typename B, typename C, typename D>
    constexpr vec(A scalar, vec<1, B> const& v1, vec<1, C> const& v2, vec<1, D> const& v3) 
		: x(static_cast<T>(scalar))
		, y(static_cast<T>(v1.x))
		, z(static_cast<T>(v2.x))
		, w(static_cast<T>(v3.x))
	{}

	template<typename A, typename B, typename C, typename D>
    constexpr vec(vec<1, A> const& v1, B scalar, vec<1, C> const& v2, vec<1, D> const& v3) 
		: x(static_cast<T>(v1.x))
		, y(static_cast<T>(scalar))
		, z(static_cast<T>(v2.x))
		, w(static_cast<T>(v3.x))
	{}

	template<typename A, typename B, typename C, typename D>
    constexpr vec(vec<1, A> const& v1, vec<1, B> const& v2, C scalar, vec<1, D> const& v3) 
		: x(static_cast<T>(v1.x))
		, y(static_cast<T>(v2.x))
		, z(static_cast<T>(scalar))
		, w(static_cast<T>(v3.x))
	{}

	template<typename A, typename B, typename C, typename D>
    constexpr vec(vec<1, A> const& v1, vec<1, B> const& v2, vec<1, C> const& v3, D scalar) 
		: x(static_cast<T>(v1.x))
		, y(static_cast<T>(v2.x))
		, z(static_cast<T>(v3.x))
		, w(static_cast<T>(scalar))
	{}

	template<typename A, typename B, typename C>
    constexpr vec(vec<2, A> const& v, B scalar1, C scalar2) 
		: x(static_cast<T>(v.x))
		, y(static_cast<T>(v.y))
		, z(static_cast<T>(scalar1))
		, w(static_cast<T>(scalar2))
	{}

	template<typename A, typename B, typename C>
    constexpr vec(vec<2, A> const& v1, vec<1, B> const& v2, C scalar) 
		: x(static_cast<T>(v1.x))
		, y(static_cast<T>(v1.y))
		, z(static_cast<T>(v2.x))
		, w(static_cast<T>(scalar))
	{}

	template<typename A, typename B, typename C>
    constexpr vec(vec<2, A> const& v1, B scalar, vec<1, C> const& v2) 
		: x(static_cast<T>(v1.x))
		, y(static_cast<T>(v1.y))
		, z(static_cast<T>(scalar))
		, w(static_cast<T>(v2.x))
	{}

	template<typename A, typename B, typename C>
    constexpr vec(vec<2, A> const& v1, vec<1, B> const& v2, vec<1, C> const& v3) 
		: x(static_cast<T>(v1.x))
		, y(static_cast<T>(v1.y))
		, z(static_cast<T>(v2.x))
		, w(static_cast<T>(v3.x))
	{}

	template<typename A, typename B, typename C>
    constexpr vec(A scalar1, vec<2, B> const& v, C scalar2) 
		: x(static_cast<T>(scalar1))
		, y(static_cast<T>(v.x))
		, z(static_cast<T>(v.y))
		, w(static_cast<T>(scalar2))
	{}

	template<typename A, typename B, typename C>
    constexpr vec(vec<1, A> const& v1, vec<2, B> const& v2, C scalar) 
		: x(static_cast<T>(v1.x))
		, y(static_cast<T>(v2.x))
		, z(static_cast<T>(v2.y))
		, w(static_cast<T>(scalar))
	{}

	template<typename A, typename B, typename C>
    constexpr vec(A scalar, vec<2, B> const& v1, vec<1, C> const& v2) 
		: x(static_cast<T>(scalar))
		, y(static_cast<T>(v1.x))
		, z(static_cast<T>(v1.y))
		, w(static_cast<T>(v2.x))
	{}

	template<typename A, typename B, typename C>
    constexpr vec(vec<1, A> v1, vec<2, B> const& v2, vec<1, C> const& v3) 
		: x(static_cast<T>(v1.x))
		, y(static_cast<T>(v2.x))
		, z(static_cast<T>(v2.y))
		, w(static_cast<T>(v3.x))
	{}

	template<typename A, typename B, typename C>
    constexpr vec(A scalar1, B scalar2, vec<2, C> const& v) 
		: x(static_cast<T>(scalar1))
		, y(static_cast<T>(scalar2))
		, z(static_cast<T>(v.x))
		, w(static_cast<T>(v.y))
	{}

	template<typename A, typename B, typename C>
    constexpr vec(vec<1, A> const& v1, B scalar, vec<2, C> const& v2) 
		: x(static_cast<T>(v1.x))
		, y(static_cast<T>(scalar))
		, z(static_cast<T>(v2.x))
		, w(static_cast<T>(v2.y))
	{}

	template<typename A, typename B, typename C>
    constexpr vec(A scalar, vec<1, B> const& v1, vec<2, C> const& v2) 
		: x(static_cast<T>(scalar))
		, y(static_cast<T>(v1.x))
		, z(static_cast<T>(v2.x))
		, w(static_cast<T>(v2.y))
	{}

	template<typename A, typename B, typename C>
    constexpr vec(vec<1, A> const& v1, vec<1, B> const& v2, vec<2, C> const& v3) 
		: x(static_cast<T>(v1.x))
		, y(static_cast<T>(v2.x))
		, z(static_cast<T>(v3.x))
		, w(static_cast<T>(v3.y))
	{}

	template<typename A, typename B>
    constexpr vec(vec<3, A> const& v, B scalar) 
		: x(static_cast<T>(v.x))
		, y(static_cast<T>(v.y))
		, z(static_cast<T>(v.z))
		, w(static_cast<T>(scalar))
	{}

	template<typename A, typename B>
    constexpr vec(A scalar, vec<3, B> const& v) 
		: x(static_cast<T>(scalar))
		, y(static_cast<T>(v.x))
		, z(static_cast<T>(v.y))
		, w(static_cast<T>(v.z))
	{}

    template<typename A>
    constexpr vec(vec<1, A> const& v) 
		: x(static_cast<T>(v.x))
		, y(static_cast<T>(0))
		, z(static_cast<T>(0))
		, w(static_cast<T>(0))
	{}

	template<typename A>
    constexpr vec(vec<2, A> const& v) 
		: x(static_cast<T>(v.x))
		, y(static_cast<T>(v.y))
		, z(static_cast<T>(0))
		, w(static_cast<T>(0))
	{}

	template<typename A>
    constexpr vec(vec<3, A> const& v) 
		: x(static_cast<T>(v.x))
		, y(static_cast<T>(v.y))
		, z(static_cast<T>(v.z))
		, w(static_cast<T>(0))
	{}

    template<typename A>
    constexpr vec(vec<4, A> const& v) 
		: x(static_cast<T>(v.x))
		, y(static_cast<T>(v.y))
		, z(static_cast<T>(v.z))
		, w(static_cast<T>(v.w))
	{}

	// length of vector
	static constexpr int size() {
		return 4;
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
			case 3:
				return w;
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
			case 3:
				return w;
        }
    }

	// math operations:
    constexpr vec<4, T> &operator=(vec const& v) = default;

    template<typename A>
    constexpr vec<4, T> &operator=(vec<4, A> const& v) {
        x = static_cast<T>(v.x);
		y = static_cast<T>(v.y);
		z = static_cast<T>(v.z);
		w = static_cast<T>(v.w);
        return *this;
    }

	constexpr vec<4, T> &operator=(T scalar) {
        x = scalar;
		y = scalar;
		z = scalar;
		w = scalar;
        return *this;
    }

	template<typename A>
    constexpr vec<4, T> &operator=(A scalar) {
        x = static_cast<T>(scalar);
		y = static_cast<T>(scalar);
		z = static_cast<T>(scalar);
		w = static_cast<T>(scalar);
        return *this;
    }
    
    // element-wise +=
    template<typename A>
    constexpr vec<4, T> &operator+=(vec<1, A> const& v) {
        x += static_cast<T>(v.x);
        return *this;
    }

    template<typename A>
    constexpr vec<4, T> &operator+=(A scalar) {
        x += static_cast<T>(scalar);
		y += static_cast<T>(scalar);
		z += static_cast<T>(scalar);
		w += static_cast<T>(scalar);
        return *this;
    }

	template<typename A>
    constexpr vec<4, T> &operator+=(vec<2, A> const& v) {
        x += static_cast<T>(v.x);
		y += static_cast<T>(v.y);
        return *this;
    }

	template<typename A>
    constexpr vec<4, T> &operator+=(vec<3, A> const& v) {
        x += static_cast<T>(v.x);
		y += static_cast<T>(v.y);
		z += static_cast<T>(v.z);
        return *this;
    }

	template<typename A>
    constexpr vec<4, T> &operator+=(vec<4, A> const& v) {
        x += static_cast<T>(v.x);
		y += static_cast<T>(v.y);
		z += static_cast<T>(v.z);
		w += static_cast<T>(v.w);
        return *this;
    }

    // element-wise -=
    template<typename A>
    constexpr vec<4, T> &operator-=(vec<1, A> const& v) {
        x -= static_cast<T>(v.x);
        return *this;
    }

    template<typename A>
    constexpr vec<4, T> &operator-=(A scalar) {
        x -= static_cast<T>(scalar);
		y -= static_cast<T>(scalar);
		z -= static_cast<T>(scalar);
		w -= static_cast<T>(scalar);
        return *this;
    }

	template<typename A>
    constexpr vec<4, T> &operator-=(vec<2, A> const& v) {
        x -= static_cast<T>(v.x);
		y -= static_cast<T>(v.y);
        return *this;
    }

	template<typename A>
    constexpr vec<4, T> &operator-=(vec<3, A> const& v) {
        x -= static_cast<T>(v.x);
		y -= static_cast<T>(v.y);
		z -= static_cast<T>(v.z);
        return *this;
    }

	template<typename A>
    constexpr vec<4, T> &operator-=(vec<4, A> const& v) {
        x -= static_cast<T>(v.x);
		y -= static_cast<T>(v.y);
		z -= static_cast<T>(v.z);
		w -= static_cast<T>(v.w);
        return *this;
    }

    // element-wise *=
    template<typename A>
    constexpr vec<4, T> &operator*=(vec<1, A> const& v) {
        x *= static_cast<T>(v.x);
		y = 0;
		z = 0;
		w = 0;
        return *this;
    }

    template<typename A>
    constexpr vec<4, T> &operator*=(A scalar) {
        x *= static_cast<T>(scalar);
		y *= static_cast<T>(scalar);
		z *= static_cast<T>(scalar);
		w *= static_cast<T>(scalar);
        return *this;
    }

	template<typename A>
    constexpr vec<4, T> &operator*=(vec<2, A> const& v) {
        x *= static_cast<T>(v.x);
		y *= static_cast<T>(v.y);
		z = 0;
		w = 0;
        return *this;
    }

	template<typename A>
    constexpr vec<4, T> &operator*=(vec<3, A> const& v) {
        x *= static_cast<T>(v.x);
		y *= static_cast<T>(v.y);
		z *= static_cast<T>(v.z);
		w = 0;
        return *this;
    }

	template<typename A>
    constexpr vec<4, T> &operator*=(vec<4, A> const& v) {
        x *= static_cast<T>(v.x);
		y *= static_cast<T>(v.y);
		z *= static_cast<T>(v.z);
		w *= static_cast<T>(v.w);
        return *this;
    }

    // element-wise /=
    template<typename A>
    constexpr vec<4, T> &operator/=(A scalar) {
        x /= static_cast<T>(scalar);
		y /= static_cast<T>(scalar);
		z /= static_cast<T>(scalar);
		w /= static_cast<T>(scalar);
        return *this;
    }

	template<typename A>
    constexpr vec<4, T> &operator/=(vec<4, A> const& v) {
        x /= static_cast<T>(v.x);
		y /= static_cast<T>(v.y);
		z /= static_cast<T>(v.z);
		w /= static_cast<T>(v.w);
        return *this;
    }

    // element-wise %=
    template<typename A>
    constexpr vec<4, T> &operator%=(A scalar) {
        x %= scalar;
		y %= scalar;
		z %= scalar;
		w %= scalar;
        return *this;
    }

	template<typename A>
    constexpr vec<4, T> &operator%=(vec<4, A> const& v) {
        x %= v.x;
		y %= v.y;
		z %= v.z;
		w %= v.w;
        return *this;
    }

    // element-wise &=
    template<typename A>
    constexpr vec<4, T> &operator&=(vec<1, A> const& v) {
        x &= v.x;
		y = 0;
		z = 0;
		w = 0;
        return *this;
    }

    template<typename A>
    constexpr vec<4, T> &operator&=(A scalar) {
        x &= scalar;
		y &= scalar;
		z &= scalar;
		w &= scalar;
        return *this;
    }

	template<typename A>
    constexpr vec<4, T> &operator&=(vec<2, A> const& v) {
        x &= v.x;
		y &= v.y;
		z = 0;
		w = 0;
        return *this;
    }

	template<typename A>
    constexpr vec<4, T> &operator&=(vec<3, A> const& v) {
        x &= v.x;
		y &= v.y;
		z &= v.z;
		w = 0;
        return *this;
    }

	template<typename A>
    constexpr vec<4, T> &operator&=(vec<4, A> const& v) {
        x &= v.x;
		y &= v.y;
		z &= v.z;
		w &= v.w;
        return *this;
    }

    // element-wise |=
    template<typename A>
    constexpr vec<4, T> &operator|=(vec<1, A> const& v) {
        x |= v.x;
        return *this;
    }

    template<typename A>
    constexpr vec<4, T> &operator|=(A scalar) {
        x |= scalar;
		y |= scalar;
		z |= scalar;
		w |= scalar;
        return *this;
    }

	template<typename A>
    constexpr vec<4, T> &operator|=(vec<2, A> const& v) {
        x |= v.x;
		y |= v.y;
        return *this;
    }

	template<typename A>
    constexpr vec<4, T> &operator|=(vec<3, A> const& v) {
        x |= v.x;
		y |= v.y;
		z |= v.z;
        return *this;
    }

	template<typename A>
    constexpr vec<4, T> &operator|=(vec<4, A> const& v) {
        x |= v.x;
		y |= v.y;
		z |= v.z;
		w |= v.w;
        return *this;
    }

    // element-wise ^=
    template<typename A>
    constexpr vec<4, T> &operator^=(vec<1, A> const& v) {
        x ^= v.x;
        return *this;
    }

    template<typename A>
    constexpr vec<4, T> &operator^=(A scalar) {
        x ^= scalar;
		y ^= scalar;
		z ^= scalar;
		w ^= scalar;
        return *this;
    }

	template<typename A>
    constexpr vec<4, T> &operator^=(vec<2, A> const& v) {
        x ^= v.x;
		y ^= v.y;
        return *this;
    }

	template<typename A>
    constexpr vec<4, T> &operator^=(vec<3, A> const& v) {
        x ^= v.x;
		y ^= v.y;
		z ^= v.z;
        return *this;
    }

	template<typename A>
    constexpr vec<4, T> &operator^=(vec<4, A> const& v) {
        x ^= v.x;
		y ^= v.y;
		z ^= v.z;
		w ^= v.w;
        return *this;
    }

    // element-wise <<=
    template<typename A>
    constexpr vec<4, T> &operator<<=(vec<1, A> const& v) {
        x <<= static_cast<T>(v.x);
        return *this;
    }

    template<typename A>
    constexpr vec<4, T> &operator<<=(A scalar) {
        x <<= static_cast<T>(scalar);
		y <<= static_cast<T>(scalar);
		z <<= static_cast<T>(scalar);
		w <<= static_cast<T>(scalar);
        return *this;
    }

	template<typename A>
    constexpr vec<4, T> &operator<<=(vec<2, A> const& v) {
        x <<= static_cast<T>(v.x);
		y <<= static_cast<T>(v.y);
        return *this;
    }

	template<typename A>
    constexpr vec<4, T> &operator<<=(vec<3, A> const& v) {
        x <<= static_cast<T>(v.x);
		y <<= static_cast<T>(v.y);
		z <<= static_cast<T>(v.z);
        return *this;
    }

	template<typename A>
    constexpr vec<4, T> &operator<<=(vec<4, A> const& v) {
        x <<= static_cast<T>(v.x);
		y <<= static_cast<T>(v.y);
		z <<= static_cast<T>(v.z);
		w <<= static_cast<T>(v.w);
        return *this;
    }

    // element-wise >>=
    template<typename A>
    constexpr vec<4, T> &operator>>=(vec<1, A> const& v) {
        x >>= static_cast<T>(v.x);
        return *this;
    }

    template<typename A>
    constexpr vec<4, T> &operator>>=(A scalar) {
        x >>= static_cast<T>(scalar);
		y >>= static_cast<T>(scalar);
		z >>= static_cast<T>(scalar);
		w >>= static_cast<T>(scalar);
        return *this;
    }

	template<typename A>
    constexpr vec<4, T> &operator>>=(vec<2, A> const& v) {
        x >>= static_cast<T>(v.x);
		y >>= static_cast<T>(v.y);
        return *this;
    }

	template<typename A>
    constexpr vec<4, T> &operator>>=(vec<3, A> const& v) {
        x >>= static_cast<T>(v.x);
		y >>= static_cast<T>(v.y);
		z >>= static_cast<T>(v.z);
        return *this;
    }

	template<typename A>
    constexpr vec<4, T> &operator>>=(vec<4, A> const& v) {
        x >>= static_cast<T>(v.x);
		y >>= static_cast<T>(v.y);
		z >>= static_cast<T>(v.z);
		w >>= static_cast<T>(v.w);
        return *this;
    }


    // increment and decrement
    // ++vec , --vec
    constexpr vec<4, T> &operator++() {
        ++x;
		++y;
		++z;
		++w;
        return *this;
    }

    constexpr vec<4, T> &operator--() {
        --x;
		--y;
		--z;
		--w;
        return *this;
    }

    // vec++ , vec--
    constexpr vec<4, T> operator++(int) {
        vec<4, T> out(*this);
        ++(*this);
        return out;
    }

    constexpr vec<4, T> operator--(int) {
        vec<4, T> out(*this);
        --(*this);
        return out;
    }

    // unary + operator 
    constexpr vec<4, T> operator+() const {
        return vec<4, T>(x, y, z, w);
    }

    // unary - operator
    constexpr vec<4, T> operator-() const {
        return vec<4, T>(-x, -y, -z, -w);
    }

    // binary math operations
    // binary addition (+)
    template<typename A>
    constexpr vec<4, T> operator+(vec<1, A> const& v) const {
        return vec<4, T>(
			x + static_cast<T>(v.x), 
			y,
			z,
			w
		);
    }

    template<typename A>
    constexpr vec<4, T> operator+(A scalar) const {
        return vec<4, T>(
			x + static_cast<T>(scalar),
			y + static_cast<T>(scalar),
			z + static_cast<T>(scalar),
			w + static_cast<T>(scalar)
		);
    }

	template<typename A>
	constexpr vec<4, T> operator+(vec<2, A> const& v) const {
        return vec<4, T>(
			x + static_cast<T>(v.x), 
			y + static_cast<T>(v.y),
			z,
			w
		);
    }

	template<typename A>
	constexpr vec<4, T> operator+(vec<3, A> const& v) const {
        return vec<4, T>(
			x + static_cast<T>(v.x), 
			y + static_cast<T>(v.y),
			z + static_cast<T>(v.z),
			w
		);
    }

	template<typename A>
	constexpr vec<4, T> operator+(vec<4, A> const& v) const {
        return vec<4, T>(
			x + static_cast<T>(v.x), 
			y + static_cast<T>(v.y),
			z + static_cast<T>(v.z),
			w + static_cast<T>(v.w)
		);
    }

    // binary subtraction (-)
    template<typename A>
    constexpr vec<4, T> operator-(vec<1, A> const& v) const {
        return vec<4, T>(
			x - static_cast<T>(v.x), 
			y,
			z,
			w
		);
    }

    template<typename A>
    constexpr vec<4, T> operator-(A scalar) const {
        return vec<4, T>(
			x - static_cast<T>(scalar),
			y - static_cast<T>(scalar),
			z - static_cast<T>(scalar),
			w - static_cast<T>(scalar)
		);
    }

	template<typename A>
	constexpr vec<4, T> operator-(vec<2, A> const& v) const {
        return vec<4, T>(
			x - static_cast<T>(v.x), 
			y - static_cast<T>(v.y),
			z,
			w
		);
    }

	template<typename A>
	constexpr vec<4, T> operator-(vec<3, A> const& v) const {
        return vec<4, T>(
			x - static_cast<T>(v.x), 
			y - static_cast<T>(v.y),
			z - static_cast<T>(v.z),
			w
		);
    }

	template<typename A>
	constexpr vec<4, T> operator-(vec<4, A> const& v) const {
        return vec<4, T>(
			x - static_cast<T>(v.x), 
			y - static_cast<T>(v.y),
			z - static_cast<T>(v.z),
			w - static_cast<T>(v.w)
		);
    }

    // binary multiplication (*)
    template<typename A>
    constexpr vec<4, T> operator*(vec<1, A> const& v) const {
        return vec<4, T>(
			x * static_cast<T>(v.x), 
			0,
			0,
			0
		);
    }

    template<typename A>
    constexpr vec<4, T> operator*(A scalar) const {
        return vec<4, T>(
			x * static_cast<T>(scalar),
			y * static_cast<T>(scalar),
			z * static_cast<T>(scalar),
			w * static_cast<T>(scalar)
		);
    }

	template<typename A>
	constexpr vec<4, T> operator*(vec<2, A> const& v) const {
        return vec<4, T>(
			x * static_cast<T>(v.x), 
			y * static_cast<T>(v.y),
			0,
			0
		);
    }

	template<typename A>
	constexpr vec<4, T> operator*(vec<3, A> const& v) const {
        return vec<4, T>(
			x * static_cast<T>(v.x), 
			y * static_cast<T>(v.y),
			z * static_cast<T>(v.z),
			0
		);
    }

	template<typename A>
	constexpr vec<4, T> operator*(vec<4, A> const& v) const {
        return vec<4, T>(
			x * static_cast<T>(v.x), 
			y * static_cast<T>(v.y),
			z * static_cast<T>(v.z),
			w * static_cast<T>(v.w)
		);
    }

    // binary division (/)
    template<typename A>
    constexpr vec<4, T> operator/(A scalar) const {
        return vec<4, T>(
			x / static_cast<T>(scalar),
			y / static_cast<T>(scalar),
			z / static_cast<T>(scalar),
			w / static_cast<T>(scalar)
		);
    }

	template<typename A>
	constexpr vec<4, T> operator/(vec<4, A> const& v) const {
        return vec<4, T>(
			x / static_cast<T>(v.x), 
			y / static_cast<T>(v.y),
			z / static_cast<T>(v.z),
			w / static_cast<T>(v.w)
		);
    }	

    // binary modulo (%)
    template<typename A>
    constexpr vec<4, T> operator%(A scalar) const {
        return vec<4, T>(
			x % static_cast<T>(scalar),
			y % static_cast<T>(scalar),
			z % static_cast<T>(scalar),
			w % static_cast<T>(scalar)
		);
    }

	template<typename A>
	constexpr vec<4, T> operator%(vec<4, A> const& v) const {
        return vec<4, T>(
			x % static_cast<T>(v.x), 
			y % static_cast<T>(v.y),
			z % static_cast<T>(v.z),
			w % static_cast<T>(v.w)
		);
    }	

    // binary and (&)
    template<typename A>
    constexpr vec<4, T> operator&(vec<1, A> const& v) const {
        return vec<4, T>(
			x & static_cast<T>(v.x), 
			0,
			0,
			0
		);
    }

    template<typename A>
    constexpr vec<4, T> operator&(A scalar) const {
        return vec<4, T>(
			x & static_cast<T>(scalar),
			y & static_cast<T>(scalar),
			z & static_cast<T>(scalar),
			w & static_cast<T>(scalar)
		);
    }

	template<typename A>
	constexpr vec<4, T> operator&(vec<2, A> const& v) const {
        return vec<4, T>(
			x & static_cast<T>(v.x), 
			y & static_cast<T>(v.y),
			0,
			0
		);
    }

	template<typename A>
	constexpr vec<4, T> operator&(vec<3, A> const& v) const {
        return vec<4, T>(
			x & static_cast<T>(v.x), 
			y & static_cast<T>(v.y),
			z & static_cast<T>(v.z),
			0
		);
    }

	template<typename A>
	constexpr vec<4, T> operator&(vec<4, A> const& v) const {
        return vec<4, T>(
			x & static_cast<T>(v.x), 
			y & static_cast<T>(v.y),
			z & static_cast<T>(v.z),
			w & static_cast<T>(v.w)
		);
    }	

    // binary or (|)
    template<typename A>
    constexpr vec<4, T> operator|(vec<1, A> const& v) const {
        return vec<4, T>(
			x | static_cast<T>(v.x), 
			y,
			z,
			w
		);
    }

    template<typename A>
    constexpr vec<4, T> operator|(A scalar) const {
        return vec<4, T>(
			x | static_cast<T>(scalar),
			y | static_cast<T>(scalar),
			z | static_cast<T>(scalar),
			w | static_cast<T>(scalar)
		);
    }

	template<typename A>
	constexpr vec<4, T> operator|(vec<2, A> const& v) const {
        return vec<4, T>(
			x | static_cast<T>(v.x), 
			y | static_cast<T>(v.y),
			z,
			w
		);
    }

	template<typename A>
	constexpr vec<4, T> operator|(vec<3, A> const& v) const {
        return vec<4, T>(
			x | static_cast<T>(v.x), 
			y | static_cast<T>(v.y),
			z | static_cast<T>(v.z),
			w
		);
    }

	template<typename A>
	constexpr vec<4, T> operator|(vec<4, A> const& v) const {
        return vec<4, T>(
			x | static_cast<T>(v.x), 
			y | static_cast<T>(v.y),
			z | static_cast<T>(v.z),
			w | static_cast<T>(v.w)
		);
    }	

    // binary xor (^)
    template<typename A>
    constexpr vec<4, T> operator^(vec<1, A> const& v) const {
        return vec<4, T>(
			x ^ static_cast<T>(v.x), 
			y,
			z,
			w
		);
    }

    template<typename A>
    constexpr vec<4, T> operator^(A scalar) const {
        return vec<4, T>(
			x ^ static_cast<T>(scalar),
			y ^ static_cast<T>(scalar),
			z ^ static_cast<T>(scalar),
			w ^ static_cast<T>(scalar)
		);
    }

	template<typename A>
	constexpr vec<4, T> operator^(vec<2, A> const& v) const {
        return vec<4, T>(
			x ^ static_cast<T>(v.x), 
			y ^ static_cast<T>(v.y),
			z,
			w
		);
    }

	template<typename A>
	constexpr vec<4, T> operator^(vec<3, A> const& v) const {
        return vec<4, T>(
			x ^ static_cast<T>(v.x), 
			y ^ static_cast<T>(v.y),
			z ^ static_cast<T>(v.z),
			w
		);
    }

	template<typename A>
	constexpr vec<4, T> operator^(vec<4, A> const& v) const {
        return vec<4, T>(
			x ^ static_cast<T>(v.x), 
			y ^ static_cast<T>(v.y),
			z ^ static_cast<T>(v.z),
			w ^ static_cast<T>(v.w)
		);
    }	

    // binary left shift (<<)
    template<typename A>
    constexpr vec<4, T> operator<<(vec<1, A> const& v) const {
        return vec<4, T>(
			x << static_cast<T>(v.x), 
			y,
			z,
			w
		);
    }

    template<typename A>
    constexpr vec<4, T> operator<<(A scalar) const {
        return vec<4, T>(
			x << static_cast<T>(scalar),
			y << static_cast<T>(scalar),
			z << static_cast<T>(scalar),
			w << static_cast<T>(scalar)
		);
    }

	template<typename A>
	constexpr vec<4, T> operator<<(vec<2, A> const& v) const {
        return vec<4, T>(
			x << static_cast<T>(v.x), 
			y << static_cast<T>(v.y),
			z,
			w
		);
    }

	template<typename A>
	constexpr vec<4, T> operator<<(vec<3, A> const& v) const {
        return vec<4, T>(
			x << static_cast<T>(v.x), 
			y << static_cast<T>(v.y),
			z << static_cast<T>(v.z),
			w
		);
    }

	template<typename A>
	constexpr vec<4, T> operator<<(vec<4, A> const& v) const  {
        return vec<4, T>(
			x << static_cast<T>(v.x), 
			y << static_cast<T>(v.y),
			z << static_cast<T>(v.z),
			w << static_cast<T>(v.w)
		);
    }	

    // binary right shift (>>)
    template<typename A>
    constexpr vec<4, T> operator>>(vec<1, A> const& v) const {
        return vec<4, T>(
			x >> static_cast<T>(v.x), 
			y,
			z,
			w
		);
    }

    template<typename A>
    constexpr vec<4, T> operator>>(A scalar) const {
        return vec<4, T>(
			x >> static_cast<T>(scalar),
			y >> static_cast<T>(scalar),
			z >> static_cast<T>(scalar),
			w >> static_cast<T>(scalar)
		);
    }

	template<typename A>
	constexpr vec<4, T> operator>>(vec<2, A> const& v) const {
        return vec<4, T>(
			x >> static_cast<T>(v.x), 
			y >> static_cast<T>(v.y),
			z,
			w
		);
    }

	template<typename A>
	constexpr vec<4, T> operator>>(vec<3, A> const& v) const {
        return vec<4, T>(
			x >> static_cast<T>(v.x), 
			y >> static_cast<T>(v.y),
			z >> static_cast<T>(v.z),
			w
		);
    }

	template<typename A>
	constexpr vec<4, T> operator>>(vec<4, A> const& v) const {
        return vec<4, T>(
			x >> static_cast<T>(v.x), 
			y >> static_cast<T>(v.y),
			z >> static_cast<T>(v.z),
			w >> static_cast<T>(v.w)
		);
    }

    // binary not (~)
    template<typename A>
    constexpr vec<4, T> operator~() const {
        return vec<4, T>(~x, ~y, ~z, ~w);
    }

    // boolean and compares
    template<typename A>
    bool operator==(A scalar) {
        return 
			equal(x, static_cast<T>(scalar)) && 
			equal(y, static_cast<T>(scalar)) && 
			equal(z, static_cast<T>(scalar)) && 
			equal(w, static_cast<T>(scalar));
    }

	template<typename A>
    bool operator==(vec<4, A> const& v) {
        return 
			equal(x, static_cast<T>(v.x)) &&
			equal(y, static_cast<T>(v.y)) &&
			equal(z, static_cast<T>(v.z)) &&
			equal(w, static_cast<T>(v.w));
    }

    template<typename A>
    constexpr bool operator!=(A scalar) {
        return !(*this == scalar);
    }

	template<typename A>
    constexpr bool operator!=(vec<4, A> const& v) {
        return !(*this == v);
    }

    constexpr vec<4, bool> operator&&(bool a) {
        return vec<4, bool>(
			x && a,
			y && a,
			z && a,
			w && a
		);
    }

	constexpr vec<4, bool> operator&&(vec<1, bool> const& v) {
        return vec<4, bool>(
			x && v.x,
			0,
			0,
			0
		);
    }

	constexpr vec<4, bool> operator&&(vec<2, bool> const& v) {
        return vec<4, bool>(
			x && v.x,
			y && v.y,
			0,
			0
		);
    }

	constexpr vec<4, bool> operator&&(vec<3, bool> const& v) {
        return vec<4, bool>(
			x && v.x,
			y && v.y,
			z && v.z,
			0
		);
    }

    constexpr vec<4, bool> operator||(bool a) {
        return vec<4, bool>(
			x || a,
			y || a,
			z || a,
			w || a
		);
    }

	constexpr vec<4, bool> operator||(vec<1, bool> const& v) {
        return vec<4, bool>(
			x || v.x,
			y,
			z,
			w
		);
    }

	constexpr vec<4, bool> operator||(vec<2, bool> const& v) {
        return vec<4, bool>(
			x || v.x,
			y || v.y,
			z,
			w
		);
    }

	constexpr vec<4, bool> operator||(vec<3, bool> const& v) {
        return vec<4, bool>(
			x || v.x,
			y || v.y,
			z || v.z,
			w
		);
    }
};

// scalar <math operation> vec1 overloads:
// + operation
template<typename T, typename A>
constexpr vec<4, T> operator+(A scalar, vec<4, T> const& v) {
    return vec<4, T>(
		static_cast<T>(scalar) + v.x,
		static_cast<T>(scalar) + v.y,
		static_cast<T>(scalar) + v.z,
		static_cast<T>(scalar) + v.w
	);
}

template<typename T, typename A>
constexpr vec<4, T> operator+(vec<1, A> const& v1, vec<4, T> const& v2) {
    return vec<4, T>(
		static_cast<T>(v1.x) + v2.x,
		v2.y,
		v2.z,
		v2.w
	);
}

template<typename T, typename A>
constexpr vec<4, T> operator+(vec<2, A> const& v1, vec<4, T> const& v2) {
    return vec<4, T>(
		static_cast<T>(v1.x) + v2.x,
		static_cast<T>(v1.y) + v2.y,
		v2.z,
		v2.w
	);
}

template<typename T, typename A>
constexpr vec<4, T> operator+(vec<3, A> const& v1, vec<4, T> const& v2) {
    return vec<4, T>(
		static_cast<T>(v1.x) + v2.x,
		static_cast<T>(v1.y) + v2.y,
		static_cast<T>(v1.z) + v2.z,
		v2.w
	);
}

// - operation
template<typename T, typename A>
constexpr vec<4, T> operator-(A scalar, vec<4, T> const& v) {
    return vec<4, T>(
		static_cast<T>(scalar) - v.x,
		static_cast<T>(scalar) - v.y,
		static_cast<T>(scalar) - v.z,
		static_cast<T>(scalar) - v.w
	);
}

template<typename T, typename A>
constexpr vec<4, T> operator-(vec<1, A> const& v1, vec<4, T> const& v2) {
    return vec<4, T>(
		static_cast<T>(v1.x) - v2.x,
		-v2.y,
		-v2.z,
		-v2.w
	);
}

template<typename T, typename A>
constexpr vec<4, T> operator-(vec<2, A> const& v1, vec<4, T> const& v2) {
    return vec<4, T>(
		static_cast<T>(v1.x) - v2.x,
		static_cast<T>(v1.y) - v2.y,
		-v2.z,
		-v2.w
	);
}

template<typename T, typename A>
constexpr vec<4, T> operator-(vec<3, A> const& v1, vec<4, T> const& v2) {
    return vec<4, T>(
		static_cast<T>(v1.x) - v2.x,
		static_cast<T>(v1.y) - v2.y,
		static_cast<T>(v1.z) - v2.z,
		-v2.w
	);
}

// * operation
template<typename T, typename A>
constexpr vec<4, T> operator*(A scalar, vec<4, T> const& v) {
    return vec<4, T>(
		static_cast<T>(scalar) * v.x,
		static_cast<T>(scalar) * v.y,
		static_cast<T>(scalar) * v.z,
		static_cast<T>(scalar) * v.w
	);
}

template<typename T, typename A>
constexpr vec<4, T> operator*(vec<1, A> const& v1, vec<4, T> const& v2) {
    return vec<4, T>(
		static_cast<T>(v1.x) * v2.x,
		0,
		0,
		0
	);
}

template<typename T, typename A>
constexpr vec<4, T> operator*(vec<2, A> const& v1, vec<4, T> const& v2) {
    return vec<4, T>(
		static_cast<T>(v1.x) * v2.x,
		static_cast<T>(v1.y) * v2.y,
		0,
		0
	);
}

template<typename T, typename A>
constexpr vec<4, T> operator*(vec<3, A> const& v1, vec<4, T> const& v2) {
    return vec<4, T>(
		static_cast<T>(v1.x) * v2.x,
		static_cast<T>(v1.y) * v2.y,
		static_cast<T>(v1.z) * v2.z,
		0
	);
}

// / operation
template<typename T, typename A>
constexpr vec<4, T> operator/(A scalar, vec<4, T> const& v) {
    return vec<4, T>(
		static_cast<T>(scalar) / v.x,
		static_cast<T>(scalar) / v.y,
		static_cast<T>(scalar) / v.z,
		static_cast<T>(scalar) / v.w
	);
}

template<typename T, typename A>
constexpr vec<4, T> operator/(vec<1, A> const& v1, vec<4, T> const& v2) {
    return vec<4, T>(
		static_cast<T>(v1.x) / v2.x,
		0,
		0,
		0
	);
}

template<typename T, typename A>
constexpr vec<4, T> operator/(vec<2, A> const& v1, vec<4, T> const& v2) {
    return vec<4, T>(
		static_cast<T>(v1.x) / v2.x,
		static_cast<T>(v1.y) / v2.y,
		0,
		0
	);
}

template<typename T, typename A>
constexpr vec<4, T> operator/(vec<3, A> const& v1, vec<4, T> const& v2) {
    return vec<4, T>(
		static_cast<T>(v1.x) / v2.x,
		static_cast<T>(v1.y) / v2.y,
		static_cast<T>(v1.z) / v2.z,
		0
	);
}

// % operator
template<typename T, typename A>
constexpr vec<4, T> operator%(A scalar, vec<4, T> const& v) {
    return vec<4, T>(
		static_cast<T>(scalar) % v.x,
		static_cast<T>(scalar) % v.y,
		static_cast<T>(scalar) % v.z,
		static_cast<T>(scalar) % v.w
	);
}

template<typename T, typename A>
constexpr vec<4, T> operator%(vec<1, A> const& v1, vec<4, T> const& v2) {
    return vec<4, T>(
		static_cast<T>(v1.x) % v2.x,
		0,
		0,
		0
	);
}

template<typename T, typename A>
constexpr vec<4, T> operator%(vec<2, A> const& v1, vec<4, T> const& v2) {
    return vec<4, T>(
		static_cast<T>(v1.x) % v2.x,
		static_cast<T>(v1.y) % v2.y,
		0,
		0
	);
}

template<typename T, typename A>
constexpr vec<4, T> operator%(vec<3, A> const& v1, vec<4, T> const& v2) {
    return vec<4, T>(
		static_cast<T>(v1.x) % v2.x,
		static_cast<T>(v1.y) % v2.y,
		static_cast<T>(v1.z) % v2.z,
		0
	);
}

// & operator
template<typename T, typename A>
constexpr vec<4, T> operator&(A scalar, vec<4, T> const& v) {
    return vec<4, T>(
		static_cast<T>(scalar) & v.x,
		static_cast<T>(scalar) & v.y,
		static_cast<T>(scalar) & v.z,
		static_cast<T>(scalar) & v.w
	);
}

template<typename T, typename A>
constexpr vec<4, T> operator&(vec<1, A> const& v1, vec<4, T> const& v2) {
    return vec<4, T>(
		static_cast<T>(v1.x) & v2.x,
		0,
		0,
		0
	);
}

template<typename T, typename A>
constexpr vec<4, T> operator&(vec<2, A> const& v1, vec<4, T> const& v2) {
    return vec<4, T>(
		static_cast<T>(v1.x) & v2.x,
		static_cast<T>(v1.y) & v2.y,
		0,
		0
	);
}

template<typename T, typename A>
constexpr vec<4, T> operator&(vec<3, A> const& v1, vec<4, T> const& v2) {
    return vec<4, T>(
		static_cast<T>(v1.x) & v2.x,
		static_cast<T>(v1.y) & v2.y,
		static_cast<T>(v1.y) & v2.z,
		0
	);
}

// | operator
template<typename T, typename A>
constexpr vec<4, T> operator|(A scalar, vec<4, T> const& v) {
    return vec<4, T>(
		static_cast<T>(scalar) | v.x,
		static_cast<T>(scalar) | v.y,
		static_cast<T>(scalar) | v.z,
		static_cast<T>(scalar) | v.w
	);
}

template<typename T, typename A>
constexpr vec<4, T> operator|(vec<1, A> const& v1, vec<4, T> const& v2) {
    return vec<4, T>(
		static_cast<T>(v1.x) | v2.x,
		v2.y,
		v2.z,
		v2.w
	);
}

template<typename T, typename A>
constexpr vec<4, T> operator|(vec<2, A> const& v1, vec<4, T> const& v2) {
    return vec<4, T>(
		static_cast<T>(v1.x) | v2.x,
		static_cast<T>(v1.y) | v2.y,
		v2.z,
		v2.w
	);
}

template<typename T, typename A>
constexpr vec<4, T> operator|(vec<3, A> const& v1, vec<4, T> const& v2) {
    return vec<4, T>(
		static_cast<T>(v1.x) | v2.x,
		static_cast<T>(v1.y) | v2.y,
		static_cast<T>(v1.z) | v2.z,
		v2.w
	);
}

// ^ operator
template<typename T, typename A>
constexpr vec<4, T> operator^(A scalar, vec<4, T> const& v) {
    return vec<4, T>(
		static_cast<T>(scalar) ^ v.x,
		static_cast<T>(scalar) ^ v.y,
		static_cast<T>(scalar) ^ v.z,
		static_cast<T>(scalar) ^ v.w
	);
}

template<typename T, typename A>
constexpr vec<4, T> operator^(vec<1, A> const& v1, vec<4, T> const& v2) {
    return vec<4, T>(
		static_cast<T>(v1.x) ^ v2.x,
		v2.y,
		v2.z,
		v2.w
	);
}

template<typename T, typename A>
constexpr vec<4, T> operator^(vec<2, A> const& v1, vec<4, T> const& v2) {
    return vec<4, T>(
		static_cast<T>(v1.x) ^ v2.x,
		static_cast<T>(v1.y) ^ v2.y,
		v2.z,
		v2.w
	);
}

template<typename T, typename A>
constexpr vec<4, T> operator^(vec<3, A> const& v1, vec<4, T> const& v2) {
    return vec<4, T>(
		static_cast<T>(v1.x) ^ v2.x,
		static_cast<T>(v1.y) ^ v2.y,
		static_cast<T>(v1.z) ^ v2.z,
		v2.w
	);
}

// << operator
template<typename T, typename A>
constexpr vec<4, T> operator<<(A scalar, vec<4, T> const& v) {
    return vec<4, T>(
		static_cast<T>(scalar) << v.x,
		static_cast<T>(scalar) << v.y,
		static_cast<T>(scalar) << v.z,
		static_cast<T>(scalar) << v.w
	);
}

template<typename T, typename A>
constexpr vec<4, T> operator<<(vec<1, A> const& v1, vec<4, T> const& v2) {
    return vec<4, T>(
		static_cast<T>(v1.x) << v2.x,
		0 << v2.y,
		0 << v2.z,
		0 << v2.w
	);
}

template<typename T, typename A>
constexpr vec<4, T> operator<<(vec<2, A> const& v1, vec<4, T> const& v2) {
    return vec<4, T>(
		static_cast<T>(v1.x) << v2.x,
		static_cast<T>(v1.y) << v2.y,
		0 << v2.z,
		0 << v2.w
	);
}

template<typename T, typename A>
constexpr vec<4, T> operator<<(vec<3, A> const& v1, vec<4, T> const& v2) {
    return vec<4, T>(
		static_cast<T>(v1.x) << v2.x,
		static_cast<T>(v1.y) << v2.y,
		static_cast<T>(v1.z) << v2.z,
		0 << v2.w
	);
}

// >> operation
template<typename T, typename A>
constexpr vec<4, T> operator>>(A scalar, vec<4, T> const& v) {
    return vec<4, T>(
		static_cast<T>(scalar) >> v.x,
		static_cast<T>(scalar) >> v.y,
		static_cast<T>(scalar) >> v.z,
		static_cast<T>(scalar) >> v.w
	);
}

template<typename T, typename A>
constexpr vec<4, T> operator>>(vec<1, A> const& v1, vec<4, T> const& v2) {
    return vec<4, T>(
		static_cast<T>(v1.x) >> v2.x,
		0 >> v2.y,
		0 >> v2.z,
		0 >> v2.w
	);
}

template<typename T, typename A>
constexpr vec<4, T> operator>>(vec<2, A> const& v1, vec<4, T> const& v2) {
    return vec<4, T>(
		static_cast<T>(v1.x) >> v2.x,
		static_cast<T>(v1.y) >> v2.y,
		0 >> v2.z,
		0 >> v2.w
	);
}

template<typename T, typename A>
constexpr vec<4, T> operator>>(vec<3, A> const& v1, vec<4, T> const& v2) {
    return vec<4, T>(
		static_cast<T>(v1.x) >> v2.x,
		static_cast<T>(v1.y) >> v2.y,
		static_cast<T>(v1.z) >> v2.z,
		0 >> v2.w
	);
}

constexpr vec<4, bool> operator&&(bool a, vec<4, bool> const& v) {
    return vec<4, bool>(
		a && v.x,
		a && v.y,
		a && v.z,
		a && v.w
	);
}

constexpr vec<4, bool> operator&&(vec<4, bool> const& v1, vec<4, bool> const& v2) {
	return vec<4, bool>(
		v1.x && v2.x,
		v1.y && v2.y,
		v1.z && v2.z,
		v1.w && v2.w
	);
}

constexpr vec<4, bool> operator||(bool a, vec<4, bool> const& v) {
    return vec<4, bool>(
		a || v.x,
		a || v.y,
		a || v.z,
		a || v.w
	);
}

constexpr vec<4, bool> operator||(vec<4, bool> const& v1, vec<4, bool> const& v2) {
	return vec<4, bool>(
		v1.x || v2.x,
		v1.y || v2.y,
		v1.z || v2.z,
		v1.w || v2.w
	);
}

template<typename T>
constexpr bool operator==(vec<4, T> const& v1, vec<4, T> const& v2) {
	return 
		equal(v1.x, v2.x) &&
		equal(v1.y, v2.y) &&
		equal(v1.z, v2.z) &&
		equal(v1.w, v2.w);
}

template<typename T>
constexpr bool operator!=(vec<4, T> const& v1, vec<4, T> const& v2) {
	return !(v1 == v2);
}

}
}