#pragma once

#include <assert.h>
#include <type_traits>
#include <vector>

#include "prismTypeDef.h"
#include "matFunc.h"

namespace prism {
namespace pml {

/**
 * 2x2 matrix specification
 * data is organized in column-major order, i.e. data[0] is column 1, data[1] is column 2 of the matrix
*/

template<typename T>
struct mat<2, 2, T> {
    static_assert(std::is_arithmetic<T>::value, "type parameter of this class must be arithmetic");

private:
    vec<2, T> data[2];

public:
    // properties:
    static constexpr int rows() {
        return 2;
    }

    static constexpr int cols() {
        return 2;
    }

    // basic constructors
    constexpr mat()
        : data{vec<2, T>(1, 0), vec<2, T>(0, 1)}
    {}

    constexpr mat(mat<2, 2, T> const& m) 
        : data{vec<2, T>(m[0]), vec<2, T>(m[1])}
    {}

    constexpr mat(mat<3, 3, T> const& m) 
        : data{vec<2, T>(m[0]), vec<2, T>(m[1])}
    {}

    constexpr mat(mat<4, 4, T> const& m) 
        : data{vec<2, T>(m[0]), vec<2, T>(m[1])}
    {}

    constexpr mat(T const& a) 
        : data{vec<2, T>(a, 0), vec<2, T>(0, a)}
    {}

    constexpr mat(
        T const& x0, T const& y0,  // column 1
        T const& x1, T const& y1)  // column 2
        : data{vec<2, T>(x0, y0), vec<2, T>(x1, y1)}
    {}

    constexpr mat(vec<2, T> const& v1, vec<2, T> const& v2)
        : data{vec<2, T>(v1), vec<2, T>(v2)}
    {}

    // conversion constructors
    template<typename A>
    constexpr mat(mat<2, 2, A> const& m)
        : data{vec<2, T>(m[0]), vec<2, T>(m[1])}
    {
        static_assert(std::numeric_limits<A>::is_iec559 || std::numeric_limits<A>::is_integer, "matrix only accepts float or int types");
    }

    template<typename A>
    constexpr mat(mat<3, 3, A> const& m)
        : data{vec<2, T>(m[0]), vec<2, T>(m[1])}
    {
        static_assert(std::numeric_limits<A>::is_iec559 || std::numeric_limits<A>::is_integer, "matrix only accepts float or int types");
    }

    template<typename A>
    constexpr mat(mat<4, 4, A> const& m)
        : data{vec<2, T>(m[0]), vec<2, T>(m[1])}
    {
        static_assert(std::numeric_limits<A>::is_iec559 || std::numeric_limits<A>::is_integer, "matrix only accepts float or int types");
    }

    template<typename A>
    constexpr mat(A const& a) 
        : data{vec<2, T>(a, 0), vec<2, T>(0, a)}
    {
        static_assert(std::numeric_limits<A>::is_iec559 || std::numeric_limits<A>::is_integer, "matrix only accepts float or int types");
    }

    template<
        typename X1, typename Y1,
        typename X2, typename Y2>
    constexpr mat(
        X1 const& x1, Y1 const& y1,
        X2 const& x2, Y2 const& y2)
        : data{vec<2, T>(x1, y1), vec<2, T>(x2, y2)}
    {
        static_assert(std::numeric_limits<X1>::is_iec559 || std::numeric_limits<X1>::is_integer, "matrix only accepts float or int types");
        static_assert(std::numeric_limits<Y1>::is_iec559 || std::numeric_limits<Y1>::is_integer, "matrix only accepts float or int types");
        static_assert(std::numeric_limits<X2>::is_iec559 || std::numeric_limits<X2>::is_integer, "matrix only accepts float or int types");
        static_assert(std::numeric_limits<Y2>::is_iec559 || std::numeric_limits<Y2>::is_integer, "matrix only accepts float or int types");
    }

    template<typename A, typename B>
    constexpr mat(vec<2, A> const& v1, vec<2, B> const& v2)
        : data{vec<2, T>(v1), vec<2, T>(v2)}
    {
        static_assert(std::numeric_limits<A>::is_iec559 || std::numeric_limits<A>::is_integer, "matrix only accepts float or int types");
        static_assert(std::numeric_limits<B>::is_iec559 || std::numeric_limits<B>::is_integer, "matrix only accepts float or int types");
    }

    // get and set with []
    constexpr vec<2, T> &operator[](int i) {
        assert(i >= 0 && i < 2);
        return data[i];
    }

    constexpr const vec<2, T> &operator[](int i) const {
        assert(i >= 0 && i < 2);
        return data[i];
    }

    // assignment operator:
    template<typename A>
    mat<2, 2, T> &operator=(mat<2, 2, A> const& m) {
        data[0] = m[0];
        data[1] = m[1];
        return *this;
    }

    // unary math operators:
    // += 
    template<typename A>
    mat<2, 2, T> &operator+=(mat<2, 2, A> const& m) {
        data[0] += m[0];
        data[1] += m[1];
        return *this;
    }

    template<typename A>
    mat<2, 2, T> &operator+=(A scalar) {
        data[0] += scalar;
        data[1] += scalar;
        return *this;
    }

    // -= 
    template<typename A>
    mat<2, 2, T> &operator-=(mat<2, 2, A> const& m) {
        data[0] -= m[0];
        data[1] -= m[1];
        return *this;
    }

    template<typename A>
    mat<2, 2, T> &operator-=(A scalar) {
        data[0] -= scalar;
        data[1] -= scalar;
        return *this;
    }

    // *= 
    template<typename A>
    mat<2, 2, T> &operator*=(mat<2, 2, A> const& m) {
        // do matrix multiplication here
        return (*this = *this * m);
    }

    template<typename A>
    mat<2, 2, T> &operator*=(A scalar) {
        data[0] *= scalar;
        data[1] *= scalar;
        return *this;
    }

    // /= 
    template<typename A>
    mat<2, 2, T> &operator/=(mat<2, 2, A> const& m) {
        // do matrix multiplication with inverse of m
        *this *= inverse(m);
        return *this;
    }

    template<typename A>
    mat<2, 2, T> &operator/=(A scalar) {
        data[0] /= scalar;
        data[1] /= scalar;
        return *this;
    }

    // increment and decrement
    // ++vec , --vec
    mat<2, 2, T> &operator++() {
        ++data[0];
		++data[1];
        return *this;
    }

    mat<2, 2, T> &operator--() {
        --data[0];
		--data[1];
        return *this;
    }

    // vec++ , vec--
    mat<2, 2, T> operator++(int) {
        mat<2, 2, T> out(*this);
        ++(*this);
        return out;
    }

    mat<2, 2, T> operator--(int) {
        mat<2, 2, T> out(*this);
        --(*this);
        return out;
    }

    // + and - signs
    mat<2, 2, T> operator+() {
        return *this;
    }

    mat<2, 2, T> operator-() {
        return mat<2, 2, T>(
            -data[0],
            -data[1]
        );
    }

    // binary math operations
    // addition (+)
    template<typename A>
    mat<2, 2, T> operator+(A a) {
        return mat<2, 2, T>(
			data[0] + a,
			data[1] + a
		);
    }

    template<typename A>
    mat<2, 2, T> operator+(mat<2, 2, A> const& m) {
        return mat<2, 2, T>(
			data[0] + m[0],
			data[1] + m[1]
		);
    }

    // subtraction (-)
    template<typename A>
    mat<2, 2, T> operator-(A a) {
        return mat<2, 2, T>(
			data[0] - a,
			data[1] - a
		);
    }

    template<typename A>
    mat<2, 2, T> operator-(mat<2, 2, A> const& m) {
        return mat<2, 2, T>(
			data[0] - m[0],
			data[1] - m[1]
		);
    }

    // multiplication (*)
    template<typename A>
    mat<2, 2, T> operator*(A a) {
        return mat<2, 2, T>(
			data[0] * a,
			data[1] * a
		);
    }

    template<typename A>
    mat<2, 2, T> operator*(mat<2, 2, A> const& m) {
        vec<2, T> a1 = data[0];
        vec<2, T> a2 = data[1];
        vec<2, T> b1 = m[0];
        vec<2, T> b2 = m[1];

        return mat<2, 2, T>(
			a1 * b1[0] + a2 * b1[1],
            a1 * b2[0] + a2 * b2[1]
		);
    }

    // division (/)
    template<typename A>
    mat<2, 2, T> operator/(A a) {
        return mat<2, 2, T>(
			data[0] / a,
			data[1] / a
		);
    }

    template<typename A>
    mat<2, 2, T> operator/(mat<2, 2, A> const& m) {
        mat<2, 2, T> copy(*this);
        return (copy /= m);
    }

    // boolean operators ==, !=
    template<typename A>
    bool operator==(mat<2, 2, A> const& m) {
        return (data[0] == m[0]) && (data[1] == m[1]);
    }

    template<typename A>
    bool operator!=(mat<2, 2, A> const& m) {
        return (data[0] != m[0]) || (data[1] != m[1]);
    }

};

}
}