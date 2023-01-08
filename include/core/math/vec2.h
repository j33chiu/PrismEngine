#pragma once

#include <assert.h>
#include <type_traits>

#include "prismTypeDef.h"
#include "floatCompare.h"

namespace prism {
namespace pml {

template<typename T>
struct vec<2, T> {
	static_assert(std::is_arithmetic<T>::value, "type parameter of this class must be arithmetic");
	union {T x; T r;};
	union {T y; T g;};

	// basic constructors 
	constexpr vec(T x, T y) 
		: x(x), y(y)
	{}

    constexpr vec(vec<1, T> const& v) 
		: x(v.x)
        , y(0)
	{}

	constexpr vec(vec<2, T> const& v) 
		: x(v.x)
        , y(v.y)
	{}

    constexpr vec(vec<3, T> const& v) 
		: x(v.x)
        , y(v.y)
	{}

    constexpr vec(vec<4, T> const& v) 
		: x(v.x)
        , y(v.y)
	{}

	constexpr vec()
		: x(0)
		, y(0)
	{}

	//constexpr vec(vec const& v) = default;

	// conversion constructors from other vec types and scalar types
    template<typename A>
    constexpr vec(A scalar) 
		: x(static_cast<T>(scalar)), y(static_cast<T>(scalar))
	{}

	template<typename A, typename B>
    constexpr vec(A scalar1, B scalar2) 
		: x(static_cast<T>(scalar1)), y(static_cast<T>(scalar2))
	{}

	template<typename A, typename B>
    constexpr vec(vec<1, A> const& v, B scalar) 
		: x(static_cast<T>(v.x)), y(static_cast<T>(scalar))
	{}

	template<typename A, typename B>
    constexpr vec(A scalar, vec<1, B> const& v) 
		: x(static_cast<T>(scalar)), y(static_cast<T>(v.x))
	{}

	template<typename A, typename B>
    constexpr vec(vec<1, A> const& v1, vec<1, B> const& v2) 
		: x(static_cast<T>(v1.x)), y(static_cast<T>(v2.x))
	{}

    template<typename A>
    constexpr vec(vec<1, A> const& v) 
		: x(static_cast<T>(v.x)), y(static_cast<T>(0))
	{}

    template<typename A>
    constexpr vec(vec<2, A> const& v) 
		: x(static_cast<T>(v.x)), y(static_cast<T>(v.y))
	{}

    template<typename A>
    constexpr vec(vec<3, A> const& v) 
		: x(static_cast<T>(v.x)), y(static_cast<T>(v.y))
	{}

    template<typename A>
    constexpr vec(vec<4, A> const& v) 
		: x(static_cast<T>(v.x)), y(static_cast<T>(v.y))
	{}

	// length of vector
	static constexpr int size() {
		return 2;
	}

	// get and set with []:
    constexpr T &operator[](int i) {
        assert(i >= 0 && i < this->size());
        switch(i) {
            default:
            case 0:
                return x;
			case 1:
				return y;
        }
    }

    constexpr const T &operator[](int i) const {
        assert(i >= 0 && i < this->size());
        switch(i) {
            default:
            case 0:
                return x;
			case 1:
				return y;
        }
    }

	// math operations:
    constexpr vec<2, T> &operator=(vec const& v) = default;

    template<typename A>
    constexpr vec<2, T> &operator=(vec<2, A> const& v) {
        x = static_cast<T>(v.x);
		y = static_cast<T>(v.y);
        return *this;
    }

    constexpr vec<2, T> &operator=(T scalar) {
        x = scalar;
		y = scalar;
        return *this;
    }

	template<typename A>
    constexpr vec<2, T> &operator=(A scalar) {
        x = static_cast<T>(scalar);
		y = static_cast<T>(scalar);
        return *this;
    }
    
    // element-wise +=
    template<typename A>
    constexpr vec<2, T> &operator+=(vec<1, A> const& v) {
        x += static_cast<T>(v.x);
        return *this;
    }

    template<typename A>
    constexpr vec<2, T> &operator+=(A scalar) {
        x += static_cast<T>(scalar);
		y += static_cast<T>(scalar);
        return *this;
    }

	template<typename A>
    constexpr vec<2, T> &operator+=(vec<2, A> const& v) {
        x += static_cast<T>(v.x);
		y += static_cast<T>(v.y);
        return *this;
    }

    // element-wise -=
    template<typename A>
    constexpr vec<2, T> &operator-=(vec<1, A> const& v) {
        x -= static_cast<T>(v.x);
        return *this;
    }

    template<typename A>
    constexpr vec<2, T> &operator-=(A scalar) {
        x -= static_cast<T>(scalar);
		y -= static_cast<T>(scalar);
        return *this;
    }

	template<typename A>
    constexpr vec<2, T> &operator-=(vec<2, A> const& v) {
        x -= static_cast<T>(v.x);
		y -= static_cast<T>(v.y);
        return *this;
    }

    // element-wise *=
    template<typename A>
    constexpr vec<2, T> &operator*=(vec<1, A> const& v) {
        x *= static_cast<T>(v.x);
		y = 0;
        return *this;
    }

    template<typename A>
    constexpr vec<2, T> &operator*=(A scalar) {
        x *= static_cast<T>(scalar);
		y *= static_cast<T>(scalar);
        return *this;
    }

	template<typename A>
    constexpr vec<2, T> &operator*=(vec<2, A> const& v) {
        x *= static_cast<T>(v.x);
		y *= static_cast<T>(v.y);
        return *this;
    }

    // element-wise /=
    template<typename A>
    constexpr vec<2, T> &operator/=(A scalar) {
        x /= static_cast<T>(scalar);
		y /= static_cast<T>(scalar);
        return *this;
    }

	template<typename A>
    constexpr vec<2, T> &operator/=(vec<2, A> const& v) {
        x /= static_cast<T>(v.x);
		y /= static_cast<T>(v.y);
        return *this;
    }

    // element-wise %=
    template<typename A>
    constexpr vec<2, T> &operator%=(A scalar) {
        x %= scalar;
		y %= scalar;
        return *this;
    }

	template<typename A>
    constexpr vec<2, T> &operator%=(vec<2, A> const& v) {
        x %= v.x;
		y %= v.y;
        return *this;
    }

    // element-wise &=
    template<typename A>
    constexpr vec<2, T> &operator&=(vec<1, A> const& v) {
        x &= v.x;
		y = 0;
        return *this;
    }

    template<typename A>
    constexpr vec<2, T> &operator&=(A scalar) {
        x &= scalar;
		y &= scalar;
        return *this;
    }

	template<typename A>
    constexpr vec<2, T> &operator&=(vec<2, A> const& v) {
        x &= v.x;
		y &= v.y;
        return *this;
    }

    // element-wise |=
    template<typename A>
    constexpr vec<2, T> &operator|=(vec<1, A> const& v) {
        x |= v.x;
        return *this;
    }

    template<typename A>
    constexpr vec<2, T> &operator|=(A scalar) {
        x |= scalar;
		y |= scalar;
        return *this;
    }

	template<typename A>
    constexpr vec<2, T> &operator|=(vec<2, A> const& v) {
        x |= v.x;
		y |= v.y;
        return *this;
    }

    // element-wise ^=
    template<typename A>
    constexpr vec<2, T> &operator^=(vec<1, A> const& v) {
        x ^= v.x;
        return *this;
    }

    template<typename A>
    constexpr vec<2, T> &operator^=(A scalar) {
        x ^= scalar;
		y ^= scalar;
        return *this;
    }
	
	template<typename A>
    constexpr vec<2, T> &operator^=(vec<2, A> const& v) {
        x ^= v.x;
		y ^= v.y;
        return *this;
    }

    // element-wise <<=
    template<typename A>
    constexpr vec<2, T> &operator<<=(vec<1, A> const& v) {
        x <<= static_cast<T>(v.x);
        return *this;
    }

    template<typename A>
    constexpr vec<2, T> &operator<<=(A scalar) {
        x <<= static_cast<T>(scalar);
		y <<= static_cast<T>(scalar);
        return *this;
    }

	template<typename A>
    constexpr vec<2, T> &operator<<=(vec<2, A> const& v) {
        x <<= static_cast<T>(v.x);
		y <<= static_cast<T>(v.y);
        return *this;
    }

    // element-wise >>=
    template<typename A>
    constexpr vec<2, T> &operator>>=(vec<1, A> const& v) {
        x >>= static_cast<T>(v.x);
        return *this;
    }

    template<typename A>
    constexpr vec<2, T> &operator>>=(A scalar) {
        x >>= static_cast<T>(scalar);
		y >>= static_cast<T>(scalar);
        return *this;
    }

	template<typename A>
    constexpr vec<2, T> &operator>>=(vec<2, A> const& v) {
        x >>= static_cast<T>(v.x);
		y >>= static_cast<T>(v.y);
        return *this;
    }


    // increment and decrement
    // ++vec , --vec
    constexpr vec<2, T> &operator++() {
        ++x;
		++y;
        return *this;
    }

    constexpr vec<2, T> &operator--() {
        --x;
		--y;
        return *this;
    }

    // vec++ , vec--
    constexpr vec<2, T> operator++(int) {
        vec<2, T> out(*this);
        ++(*this);
        return out;
    }

    constexpr vec<2, T> operator--(int) {
        vec<2, T> out(*this);
        --(*this);
        return out;
    }

    // unary + operator 
    constexpr vec<2, T> operator+() const {
        return vec<2, T>(x, y);
    }

    // unary - operator
    constexpr vec<2, T> operator-() const {
        return vec<2, T>(-x, -y);
    }

    // binary math operations
    // binary addition (+)
    template<typename A>
    constexpr vec<2, T> operator+(vec<1, A> const& v) const {
        return vec<2, T>(
			x + static_cast<T>(v.x),
			y
		);
    }

    template<typename A>
    constexpr vec<2, T> operator+(A scalar) const {
        return vec<2, T>(
			x + static_cast<T>(scalar),
			y + static_cast<T>(scalar)
		);
    }

	template<typename A>
	constexpr vec<2, T> operator+(vec<2, A> const& v) const {
        return vec<2, T>(
			x + static_cast<T>(v.x), 
			y + static_cast<T>(v.y)
		);
    }

    // binary subtraction (-)
    template<typename A>
    constexpr vec<2, T> operator-(vec<1, A> const& v) const {
        return vec<2, T>(
			x - static_cast<T>(v.x),
			y
		);
    }

    template<typename A>
    constexpr vec<2, T> operator-(A scalar) const {
        return vec<2, T>(
			x - static_cast<T>(scalar),
			y - static_cast<T>(scalar)
		);
    }

	template<typename A>
    constexpr vec<2, T> operator-(vec<2, A> const& v) const {
        return vec<2, T>(
			x - static_cast<T>(v.x),
			y - static_cast<T>(v.y)
		);
    }

    // binary multiplication (*)
    template<typename A>
    constexpr vec<2, T> operator*(vec<1, A> const& v) const {
        return vec<2, T>(
			x * static_cast<T>(v.x),
			0
		);
    }

    template<typename A>
    constexpr vec<2, T> operator*(A scalar) const {
        return vec<2, T>(
			x * static_cast<T>(scalar),
			y * static_cast<T>(scalar)
		);
    }

	template<typename A>
    constexpr vec<2, T> operator*(vec<2, A> const& v) const {
        return vec<2, T>(
			x * static_cast<T>(v.x),
			y * static_cast<T>(v.y)
		);
    }

    // binary division (/)
    template<typename A>
    constexpr vec<2, T> operator/(A scalar) const {
        return vec<2, T>(
			x / static_cast<T>(scalar),
			y / static_cast<T>(scalar)
		);
    }

	template<typename A>
    constexpr vec<2, T> operator/(vec<2, A> const& v) const {
        return vec<2, T>(
			x / static_cast<T>(v.x),
			y / static_cast<T>(v.y)
		);
    }

    // binary modulo (%)
    template<typename A>
    constexpr vec<2, T> operator%(A scalar) const {
        return vec<2, T>(
			x % static_cast<T>(scalar),
			y % static_cast<T>(scalar)
		);
    }

	template<typename A>
    constexpr vec<2, T> operator%(vec<2, A> const& v) const {
        return vec<2, T>(
			x % static_cast<T>(v.x),
			y % static_cast<T>(v.y)
		);
    }

    // binary and (&)
    template<typename A>
    constexpr vec<2, T> operator&(vec<1, A> const& v) const {
        return vec<2, T>(
			x & static_cast<T>(v.x),
			0
		);
    }

    template<typename A>
    constexpr vec<2, T> operator&(A scalar) const {
        return vec<2, T>(
			x & static_cast<T>(scalar),
			y & static_cast<T>(scalar)
		);
    }

	template<typename A>
    constexpr vec<2, T> operator&(vec<2, A> const& v) const {
        return vec<2, T>(
			x & static_cast<T>(v.x),
			y & static_cast<T>(v.y)
		);
    }

    // binary or (|)
    template<typename A>
    constexpr vec<2, T> operator|(vec<1, A> const& v) const {
        return vec<2, T>(
			x | static_cast<T>(v.x),
			y
		);
    }

    template<typename A>
    constexpr vec<2, T> operator|(A scalar) const {
        return vec<2, T>(
			x | static_cast<T>(scalar),
			y | static_cast<T>(scalar)
		);
    }

	template<typename A>
    constexpr vec<2, T> operator|(vec<2, A> const& v) const {
        return vec<2, T>(
			x | static_cast<T>(v.x),
			y | static_cast<T>(v.y)
		);
    }

    // binary xor (^)
    template<typename A>
    constexpr vec<2, T> operator^(vec<1, A> const& v) const {
        return vec<2, T>(
			x ^ static_cast<T>(v.x),
			y
		);
    }

    template<typename A>
    constexpr vec<2, T> operator^(A scalar) const {
        return vec<2, T>(
			x ^ static_cast<T>(scalar),
			y ^ static_cast<T>(scalar)
		);
    }

	template<typename A>
    constexpr vec<2, T> operator^(vec<2, A> const& v) const {
        return vec<2, T>(
			x ^ static_cast<T>(v.x),
			y ^ static_cast<T>(v.y)
		);
    }

    // binary left shift (<<)
    template<typename A>
    constexpr vec<2, T> operator<<(vec<1, A> const& v) const {
        return vec<2, T>(
			x << static_cast<T>(v.x),
			y
		);
    }

    template<typename A>
    constexpr vec<2, T> operator<<(A scalar) const {
        return vec<2, T>(
			x << static_cast<T>(scalar),
			y << static_cast<T>(scalar)
		);
    }

	template<typename A>
    constexpr vec<2, T> operator<<(vec<2, A> const& v) const {
        return vec<2, T>(
			x << static_cast<T>(v.x),
			y << static_cast<T>(v.y)
		);
    }

    // binary right shift (>>)
    template<typename A>
    constexpr vec<2, T> operator>>(vec<1, A> const& v) const {
        return vec<2, T>(
			x >> static_cast<T>(v.x),
			y
		);
    }

    template<typename A>
    constexpr vec<2, T> operator>>(A scalar) const {
        return vec<2, T>(
			x >> static_cast<T>(scalar),
			y >> static_cast<T>(scalar)
		);
    }

	template<typename A>
    constexpr vec<2, T> operator>>(vec<2, A> const& v) const {
        return vec<2, T>(
			x >> static_cast<T>(v.x),
			y >> static_cast<T>(v.y)
		);
    }

    // binary not (~)
    template<typename A>
    constexpr vec<2, T> operator~() const {
        return vec<2, T>(~x, ~y);
    }

    // boolean and compares
    template<typename A>
    bool operator==(A scalar) {
        return 
			equal(x, static_cast<T>(scalar)) && 
			equal(y, static_cast<T>(scalar));
    }

	template<typename A>
    bool operator==(vec<2, A> const& v) {
        return 
			equal(x, static_cast<T>(v.x)) &&
			equal(y, static_cast<T>(v.y));
    }

    template<typename A>
    constexpr bool operator!=(A scalar) {
        return !(*this == scalar);
    }

	template<typename A>
    constexpr bool operator!=(vec<2, A> const& v) {
        return !(*this == v);
    }

    constexpr vec<2, bool> operator&&(bool a) {
        return vec<2, bool>(
			x && a,
			y && a
		);
    }

	constexpr vec<2, bool> operator&&(vec<1, bool> const& v) {
        return vec<2, bool>(
			x && v.x,
			0
		);
    }

    constexpr vec<2, bool> operator||(bool a) {
        return vec<2, bool>(
			x || a,
			y || a
		);
    }

	constexpr vec<2, bool> operator||(vec<1, bool> const& v) {
        return vec<2, bool>(
			x || v.x,
			y
		);
    }
};

// scalar <math operation> vec1 overloads:
template<typename T, typename A>
constexpr vec<2, T> operator+(A scalar, vec<2, T> const& v) {
    return vec<2, T>(
		static_cast<T>(scalar) + v.x,
		static_cast<T>(scalar) + v.y
	);
}

template<typename T, typename A>
constexpr vec<2, T> operator+(vec<1, A> const& v1, vec<2, T> const& v2) {
    return vec<2, T>(
		static_cast<T>(v1.x) + v2.x,
		v2.y
	);
}

template<typename T, typename A>
constexpr vec<2, T> operator-(A scalar, vec<2, T> const& v) {
    return vec<2, T>(
		static_cast<T>(scalar) - v.x,
		static_cast<T>(scalar) - v.y
	);
}

template<typename T, typename A>
constexpr vec<2, T> operator-(vec<1, A> const& v1, vec<2, T> const& v2) {
    return vec<2, T>(
		static_cast<T>(v1.x) - v2.x,
		-v2.y
	);
}

template<typename T, typename A>
constexpr vec<2, T> operator*(A scalar, vec<2, T> const& v) {
    return vec<2, T>(
		static_cast<T>(scalar) * v.x,
		static_cast<T>(scalar) * v.y
	);
}

template<typename T, typename A>
constexpr vec<2, T> operator*(vec<1, A> const& v1, vec<2, T> const& v2) {
    return vec<2, T>(
		static_cast<T>(v1.x) * v2.x,
		0
	);
}

template<typename T, typename A>
constexpr vec<2, T> operator/(A scalar, vec<2, T> const& v) {
    return vec<2, T>(
		static_cast<T>(scalar) / v.x,
		static_cast<T>(scalar) / v.y
	);
}

template<typename T, typename A>
constexpr vec<2, T> operator/(vec<1, A> const& v1, vec<2, T> const& v2) {
    return vec<2, T>(
		static_cast<T>(v1.x) / v2.x,
		0
	);
}

template<typename T, typename A>
constexpr vec<2, T> operator%(A scalar, vec<2, T> const& v) {
    return vec<2, T>(
		static_cast<T>(scalar) % v.x,
		static_cast<T>(scalar) % v.y
	);
}

template<typename T, typename A>
constexpr vec<2, T> operator%(vec<1, A> const& v1, vec<2, T> const& v2) {
    return vec<2, T>(
		static_cast<T>(v1.x) % v2.x,
		0
	);
}

template<typename T, typename A>
constexpr vec<2, T> operator&(A scalar, vec<2, T> const& v) {
    return vec<2, T>(
		static_cast<T>(scalar) & v.x,
		static_cast<T>(scalar) & v.y
	);
}

template<typename T, typename A>
constexpr vec<2, T> operator&(vec<1, A> const& v1, vec<2, T> const& v2) {
    return vec<2, T>(
		static_cast<T>(v1.x) & v2.x,
		0
	);
}

template<typename T, typename A>
constexpr vec<2, T> operator|(A scalar, vec<2, T> const& v) {
    return vec<2, T>(
		static_cast<T>(scalar) | v.x,
		static_cast<T>(scalar) | v.y
	);
}

template<typename T, typename A>
constexpr vec<2, T> operator|(vec<1, A> const& v1, vec<2, T> const& v2) {
    return vec<2, T>(
		static_cast<T>(v1.x) | v2.x,
		v2.y
	);
}

template<typename T, typename A>
constexpr vec<2, T> operator^(A scalar, vec<2, T> const& v) {
    return vec<2, T>(
		static_cast<T>(scalar) ^ v.x,
		static_cast<T>(scalar) ^ v.y
	);
}

template<typename T, typename A>
constexpr vec<2, T> operator^(vec<1, A> const& v1, vec<2, T> const& v2) {
    return vec<2, T>(
		static_cast<T>(v1.x) ^ v2.x,
		v2.y
	);
}

template<typename T, typename A>
constexpr vec<2, T> operator<<(A scalar, vec<2, T> const& v) {
    return vec<2, T>(
		static_cast<T>(scalar) << v.x,
		static_cast<T>(scalar) << v.y
	);
}

template<typename T, typename A>
constexpr vec<2, T> operator<<(vec<1, A> const& v1, vec<2, T> const& v2) {
    return vec<2, T>(
		static_cast<T>(v1.x) << v2.x,
		0 << v2.y
	);
}

template<typename T, typename A>
constexpr vec<2, T> operator>>(A scalar, vec<2, T> const& v) {
    return vec<2, T>(
		static_cast<T>(scalar) >> v.x,
		static_cast<T>(scalar) >> v.y
	);
}

template<typename T, typename A>
constexpr vec<2, T> operator>>(vec<1, A> const& v1, vec<2, T> const& v2) {
    return vec<2, T>(
		static_cast<T>(v1.x) >> v2.x,
		0 >> v2.y
	);
}

constexpr vec<2, bool> operator&&(bool a, vec<2, bool> const& v) {
    return vec<2, bool>(
		a && v.x,
		a && v.y
	);
}

constexpr vec<2, bool> operator&&(vec<2, bool> const& v1, vec<2, bool> const& v2) {
	return vec<2, bool>(
		v1.x && v2.x,
		v1.y && v2.y
	);
}

constexpr vec<2, bool> operator||(bool a, vec<2, bool> const& v) {
    return vec<2, bool>(
		a || v.x,
		a || v.y
	);
}

constexpr vec<2, bool> operator||(vec<2, bool> const& v1, vec<2, bool> const& v2) {
	return vec<2, bool>(
		v1.x || v2.x,
		v1.y || v2.y
	);
}

}
}
