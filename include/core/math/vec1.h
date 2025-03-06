#pragma once

#include <assert.h>
#include <type_traits>

#include "prismTypeDef.h"
#include "floatCompare.h"

namespace prism {
namespace pml {

template<typename T>
struct vec<1, T> {
	static_assert(std::is_arithmetic<T>::value, "type parameter of this class must be arithmetic");
	union {T x; T r;};

	// basic constructors 
	constexpr vec(T x) 
		: x(x)
	{}

    constexpr vec(vec<1, T> const& v) 
		: x(v.x)
	{}

    constexpr vec(vec<2, T> const& v) 
		: x(v.x)
	{}

    constexpr vec(vec<3, T> const& v) 
		: x(v.x)
	{}

    constexpr vec(vec<4, T> const& v) 
		: x(v.x)
	{}

	constexpr vec()
		: x(0)
	{}

	//constexpr vec(vec const& v) = default;

	// conversion constructors from other vec types and scalar types
    template<typename A>
    constexpr vec(A scalar) 
		: x(static_cast<T>(scalar))
	{}

    template<typename A>
    constexpr vec(vec<1, A> const& v) 
		: x(static_cast<T>(v.x))
	{}

    template<typename A>
    constexpr vec(vec<2, A> const& v) 
		: x(static_cast<T>(v.x))
	{}

    template<typename A>
    constexpr vec(vec<3, A> const& v) 
		: x(static_cast<T>(v.x))
	{}

    template<typename A>
    constexpr vec(vec<4, A> const& v) 
		: x(static_cast<T>(v.x))
	{}

	// length of vector
	static constexpr int size() {
		return 1;
	}

	// get and set with []:
    constexpr T &operator[](int i) {
        assert(i >= 0 && i < size());
        switch(i) {
            default:
            case 0:
                return x;
        }
    }

    constexpr const T &operator[](int i) const {
        assert(i >= 0 && i < size());
        switch(i) {
            default:
            case 0:
                return x;
        }
    }

	// math operations:
    constexpr vec<1, T> &operator=(vec const& v) = default;

    template<typename A>
    constexpr vec<1, T> &operator=(vec<1, A> const& v) {
        x = static_cast<T>(v.x);
        return *this;
    }

    constexpr vec<1, T> &operator=(T scalar) {
        x = scalar;
        return *this;
    }

    template<typename A>
    constexpr vec<1, T> &operator=(A scalar) {
        x = static_cast<T>(scalar);
        return *this;
    }
    
    // element-wise +=
    template<typename A>
    constexpr vec<1, T> &operator+=(vec<1, A> const& v) {
        x += static_cast<T>(v.x);
        return *this;
    }

    template<typename A>
    constexpr vec<1, T> &operator+=(A scalar) {
        x += static_cast<T>(scalar);
        return *this;
    }

    // element-wise -=
    template<typename A>
    constexpr vec<1, T> &operator-=(vec<1, A> const& v) {
        x -= static_cast<T>(v.x);
        return *this;
    }

    template<typename A>
    constexpr vec<1, T> &operator-=(A scalar) {
        x -= static_cast<T>(scalar);
        return *this;
    }

    // element-wise *=
    template<typename A>
    constexpr vec<1, T> &operator*=(vec<1, A> const& v) {
        x *= static_cast<T>(v.x);
        return *this;
    }

    template<typename A>
    constexpr vec<1, T> &operator*=(A scalar) {
        x *= static_cast<T>(scalar);
        return *this;
    }

    // element-wise /=
    template<typename A>
    constexpr vec<1, T> &operator/=(vec<1, A> const& v) {
        x /= static_cast<T>(v.x);
        return *this;
    }

    template<typename A>
    constexpr vec<1, T> &operator/=(A scalar) {
        x /= static_cast<T>(scalar);
        return *this;
    }

    // element-wise %=
    template<typename A>
    constexpr vec<1, T> &operator%=(vec<1, A> const& v) {
        x %= v.x;
        return *this;
    }

    template<typename A>
    constexpr vec<1, T> &operator%=(A scalar) {
        x %= scalar;
        return *this;
    }

    // element-wise &=
    template<typename A>
    constexpr vec<1, T> &operator&=(vec<1, A> const& v) {
        x &= v.x;
        return *this;
    }

    template<typename A>
    constexpr vec<1, T> &operator&=(A scalar) {
        x &= scalar;
        return *this;
    }

    // element-wise |=
    template<typename A>
    constexpr vec<1, T> &operator|=(vec<1, A> const& v) {
        x |= v.x;
        return *this;
    }

    template<typename A>
    constexpr vec<1, T> &operator|=(A scalar) {
        x |= scalar;
        return *this;
    }

    // element-wise ^=
    template<typename A>
    constexpr vec<1, T> &operator^=(vec<1, A> const& v) {
        x ^= v.x;
        return *this;
    }

    template<typename A>
    constexpr vec<1, T> &operator^=(A scalar) {
        x ^= scalar;
        return *this;
    }

    // element-wise <<=
    template<typename A>
    constexpr vec<1, T> &operator<<=(vec<1, A> const& v) {
        x <<= static_cast<T>(v.x);
        return *this;
    }

    template<typename A>
    constexpr vec<1, T> &operator<<=(A scalar) {
        x <<= static_cast<T>(scalar);
        return *this;
    }

    // element-wise >>=
    template<typename A>
    constexpr vec<1, T> &operator>>=(vec<1, A> const& v) {
        x >>= static_cast<T>(v.x);
        return *this;
    }

    template<typename A>
    constexpr vec<1, T> &operator>>=(A scalar) {
        x >>= static_cast<T>(scalar);
        return *this;
    }


    // increment and decrement
    // ++vec , --vec
    constexpr vec<1, T> &operator++() {
        ++x;
        return *this;
    }

    constexpr vec<1, T> &operator--() {
        --x;
        return *this;
    }

    // vec++ , vec--
    constexpr vec<1, T> operator++(int) {
        vec<1, T> out(*this);
        ++(*this);
        return out;
    }

    constexpr vec<1, T> operator--(int) {
        vec<1, T> out(*this);
        --(*this);
        return out;
    }

    // unary + operator 
    constexpr vec<1, T> operator+() const {
        return vec<1, T>(x);
    }

    // unary - operator
    constexpr vec<1, T> operator-() const {
        return vec<1, T>(-x);
    }

    // binary math operations
    // binary addition (+)
    template<typename A>
    constexpr vec<1, T> operator+(vec<1, A> const& v) const {
        return vec<1, T>(x + static_cast<T>(v.x));
    }

    template<typename A>
    constexpr vec<1, T> operator+(A scalar) const {
        return vec<1, T>(x + static_cast<T>(scalar));
    }

    // binary subtraction (-)
    template<typename A>
    constexpr vec<1, T> operator-(vec<1, A> const& v) const {
        return vec<1, T>(x - static_cast<T>(v.x));
    }

    template<typename A>
    constexpr vec<1, T> operator-(A scalar) const {
        return vec<1, T>(x - static_cast<T>(scalar));
    }

    // binary multiplication (*)
    template<typename A>
    constexpr vec<1, T> operator*(vec<1, A> const& v) const {
        return vec<1, T>(x * static_cast<T>(v.x));
    }

    template<typename A>
    constexpr vec<1, T> operator*(A scalar) const {
        return vec<1, T>(x * static_cast<T>(scalar));
    }

    // binary division (/)
    template<typename A>
    constexpr vec<1, T> operator/(vec<1, A> const& v) const {
        return vec<1, T>(x / static_cast<T>(v.x));
    }

    template<typename A>
    constexpr vec<1, T> operator/(A scalar) const {
        return vec<1, T>(x / static_cast<T>(scalar));
    }

    // binary modulo (%)
    template<typename A>
    constexpr vec<1, T> operator%(vec<1, A> const& v) const {
        return vec<1, T>(x % static_cast<T>(v.x));
    }

    template<typename A>
    constexpr vec<1, T> operator%(A scalar) const {
        return vec<1, T>(x % static_cast<T>(scalar));
    }

    // binary and (&)
    template<typename A>
    constexpr vec<1, T> operator&(vec<1, A> const& v) const {
        return vec<1, T>(x & static_cast<T>(v.x));
    }

    template<typename A>
    constexpr vec<1, T> operator&(A scalar) const {
        return vec<1, T>(x & static_cast<T>(scalar));
    }

    // binary or (|)
    template<typename A>
    constexpr vec<1, T> operator|(vec<1, A> const& v) const {
        return vec<1, T>(x | static_cast<T>(v.x));
    }

    template<typename A>
    constexpr vec<1, T> operator|(A scalar) const {
        return vec<1, T>(x | static_cast<T>(scalar));
    }

    // binary xor (^)
    template<typename A>
    constexpr vec<1, T> operator^(vec<1, A> const& v) const {
        return vec<1, T>(x ^ static_cast<T>(v.x));
    }

    template<typename A>
    constexpr vec<1, T> operator^(A scalar) const {
        return vec<1, T>(x ^ static_cast<T>(scalar));
    }

    // binary left shift (<<)
    template<typename A>
    constexpr vec<1, T> operator<<(vec<1, A> const& v) const {
        return vec<1, T>(x << static_cast<T>(v.x));
    }

    template<typename A>
    constexpr vec<1, T> operator<<(A scalar) const {
        return vec<1, T>(x << static_cast<T>(scalar));
    }

    // binary right shift (>>)
    template<typename A>
    constexpr vec<1, T> operator>>(vec<1, A> const& v) const {
        return vec<1, T>(x >> static_cast<T>(v.x));
    }

    template<typename A>
    constexpr vec<1, T> operator>>(A scalar) const {
        return vec<1, T>(x >> static_cast<T>(scalar));
    }

    // binary not (~)
    template<typename A>
    constexpr vec<1, T> operator~() const {
        return vec<1, T>(~x);
    }

    // boolean and compares
    template<typename A>
    bool operator==(A scalar) {
        return equal(x, static_cast<T>(scalar));
    }

    template<typename A>
    bool operator==(vec<1, A> const& v) {
        return equal(x, static_cast<T>(v.x));
    }

    template<typename A>
    constexpr bool operator!=(A scalar) {
        return !(x == static_cast<T>(scalar));
    }

    template<typename A>
    constexpr bool operator!=(vec<1, A> const& v) {
        return !(x == static_cast<T>(v.x));
    }

    constexpr vec<1, bool> operator&&(bool a) {
        return vec<1, bool>(x && a);
    }

    constexpr vec<1, bool> operator||(bool a) {
        return vec<1, bool>(x || a);
    }
};

// scalar <math operation> vec1 overloads:
template<typename T, typename A>
constexpr vec<1, T> operator+(A scalar, vec<1, T> const& v) {
    return vec<1, T>(static_cast<T>(scalar) + v.x);
}

template<typename T, typename A>
constexpr vec<1, T> operator-(A scalar, vec<1, T> const& v) {
    return vec<1, T>(static_cast<T>(scalar) - v.x);
}

template<typename T, typename A>
constexpr vec<1, T> operator*(A scalar, vec<1, T> const& v) {
    return vec<1, T>(static_cast<T>(scalar) * v.x);
}

template<typename T, typename A>
constexpr vec<1, T> operator/(A scalar, vec<1, T> const& v) {
    return vec<1, T>(static_cast<T>(scalar) / v.x);
}

template<typename T, typename A>
constexpr vec<1, T> operator%(A scalar, vec<1, T> const& v) {
    return vec<1, T>(static_cast<T>(scalar) % v.x);
}

template<typename T, typename A>
constexpr vec<1, T> operator&(A scalar, vec<1, T> const& v) {
    return vec<1, T>(static_cast<T>(scalar) & v.x);
}

template<typename T, typename A>
constexpr vec<1, T> operator|(A scalar, vec<1, T> const& v) {
    return vec<1, T>(static_cast<T>(scalar) | v.x);
}

template<typename T, typename A>
constexpr vec<1, T> operator^(A scalar, vec<1, T> const& v) {
    return vec<1, T>(static_cast<T>(scalar) ^ v.x);
}

template<typename T, typename A>
constexpr vec<1, T> operator<<(A scalar, vec<1, T> const& v) {
    return vec<1, T>(static_cast<T>(scalar) << v.x);
}

template<typename T, typename A>
constexpr vec<1, T> operator>>(A scalar, vec<1, T> const& v) {
    return vec<1, T>(static_cast<T>(scalar) >> v.x);
}

constexpr vec<1, bool> operator&&(bool a, vec<1, bool> const& v) {
    return vec<1, bool>(a && v.x);
}

constexpr vec<1, bool> operator||(bool a, vec<1, bool> const& v) {
    return vec<1, bool>(a || v.x);
}

template<typename T>
constexpr bool operator==(vec<1, T> const& v1, vec<1, T> const& v2) {
	return 
		equal(v1.x, v2.x);
}

template<typename T>
constexpr bool operator!=(vec<1, T> const& v1, vec<1, T> const& v2) {
	return !(v1 == v2);
}

}
}
