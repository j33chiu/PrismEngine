#pragma once

#include <assert.h>
#include <type_traits>
#include <vector>

#include "prismTypeDef.h"
#include "matFunc.h"

namespace prism {
namespace pml {

/**
 * 3x3 matrix specification
 * data is organized in column-major order, i.e. data[0] is column 1, data[1] is column 2 of the matrix
*/

template<typename T>
struct mat<3, 3, T> {
    static_assert(std::is_arithmetic<T>::value, "type parameter of this class must be arithmetic");

private:
    vec<3, T> data[3];

public:
    // properties:
    static constexpr int rows() {
        return 3;
    }

    static constexpr int cols() {
        return 3;
    }

    // basic constructors
    constexpr mat()
        : data{
            vec<3, T>(1, 0, 0), 
            vec<3, T>(0, 1, 0),
            vec<3, T>(0, 0, 1)}
    {}

    constexpr mat(mat<2, 2, T> const& m) 
        : data{
            vec<3, T>(m[0]), 
            vec<3, T>(m[1]),
            vec<3, T>(0, 0, 1)}
    {}

    constexpr mat(mat<3, 3, T> const& m) 
        : data{
            vec<3, T>(m[0]), 
            vec<3, T>(m[1]),
            vec<3, T>(m[2])}
    {}

    constexpr mat(mat<4, 4, T> const& m) 
        : data{
            vec<3, T>(m[0]), 
            vec<3, T>(m[1]),
            vec<3, T>(m[2])}
    {}

    constexpr mat(T const& a) 
        : data{
            vec<3, T>(a, 0, 0), 
            vec<3, T>(0, a, 0),
            vec<3, T>(0, 0, a)}
    {}

    constexpr mat(
        T const& x0, T const& y0, T const& z0,      // column 1
        T const& x1, T const& y1, T const& z1,      // column 2
        T const& x2, T const& y2, T const& z2)      // column 3
        : data{
            vec<3, T>(x0, y0, z0), 
            vec<3, T>(x1, y1, z1), 
            vec<3, T>(x2, y2, z2)}
    {}

    constexpr mat(vec<3, T> const& v1, vec<3, T> const& v2, vec<3, T> const& v3)
        : data{
            vec<3, T>(v1), 
            vec<3, T>(v2),
            vec<3, T>(v3)}
    {}

    // conversion constructors
    template<typename A>
    constexpr mat(mat<2, 2, A> const& m)
        : data{
            vec<3, T>(m[0]), 
            vec<3, T>(m[1]),
            vec<3, T>(0, 0, 1)}
    {
        static_assert(std::numeric_limits<A>::is_iec559 || std::numeric_limits<A>::is_integer, "matrix only accepts float or int types");
    }

    template<typename A>
    constexpr mat(mat<3, 3, A> const& m)
        : data{
            vec<3, T>(m[0]), 
            vec<3, T>(m[1]),
            vec<3, T>(m[2])}
    {
        static_assert(std::numeric_limits<A>::is_iec559 || std::numeric_limits<A>::is_integer, "matrix only accepts float or int types");
    }

    template<typename A>
    constexpr mat(mat<4, 4, A> const& m)
        : data{
            vec<3, T>(m[0]), 
            vec<3, T>(m[1]),
            vec<3, T>(m[2])}
    {
        static_assert(std::numeric_limits<A>::is_iec559 || std::numeric_limits<A>::is_integer, "matrix only accepts float or int types");
    }

    template<typename A>
    constexpr mat(A const& a) 
        : data{
            vec<3, T>(a, 0, 0), 
            vec<3, T>(0, a, 0),
            vec<3, T>(0, 0, a)}
    {
        static_assert(std::numeric_limits<A>::is_iec559 || std::numeric_limits<A>::is_integer, "matrix only accepts float or int types");
    }

    template<
        typename X0, typename Y0, typename Z0,
        typename X1, typename Y1, typename Z1,
        typename X2, typename Y2, typename Z2>
    constexpr mat(
        X0 const& x0, Y0 const& y0, Z0 const& z0,       // column 1
        X1 const& x1, Y1 const& y1, Z1 const& z1,       // column 2
        X2 const& x2, Y2 const& y2, Z2 const& z2)       // column 3
        : data{
            vec<3, T>(x0, y0, z0), 
            vec<3, T>(x1, y1, z1), 
            vec<3, T>(x2, y2, z2)}
    {
        static_assert(std::numeric_limits<X0>::is_iec559 || std::numeric_limits<X0>::is_integer, "matrix only accepts float or int types");
        static_assert(std::numeric_limits<X1>::is_iec559 || std::numeric_limits<X1>::is_integer, "matrix only accepts float or int types");
        static_assert(std::numeric_limits<X2>::is_iec559 || std::numeric_limits<X2>::is_integer, "matrix only accepts float or int types");
        static_assert(std::numeric_limits<Y0>::is_iec559 || std::numeric_limits<Y0>::is_integer, "matrix only accepts float or int types");
        static_assert(std::numeric_limits<Y1>::is_iec559 || std::numeric_limits<Y1>::is_integer, "matrix only accepts float or int types");
        static_assert(std::numeric_limits<Y2>::is_iec559 || std::numeric_limits<Y2>::is_integer, "matrix only accepts float or int types");
        static_assert(std::numeric_limits<Z0>::is_iec559 || std::numeric_limits<Z0>::is_integer, "matrix only accepts float or int types");
        static_assert(std::numeric_limits<Z1>::is_iec559 || std::numeric_limits<Z1>::is_integer, "matrix only accepts float or int types");
        static_assert(std::numeric_limits<Z2>::is_iec559 || std::numeric_limits<Z2>::is_integer, "matrix only accepts float or int types");
    }

    template<typename A, typename B, typename C>
    constexpr mat(vec<3, A> const& v1, vec<3, B> const& v2, vec<3, C> const& v3)
        : data{
            vec<3, A>(v1), 
            vec<3, B>(v2),
            vec<3, C>(v3)}
    {
        static_assert(std::numeric_limits<A>::is_iec559 || std::numeric_limits<A>::is_integer, "matrix only accepts float or int types");
        static_assert(std::numeric_limits<B>::is_iec559 || std::numeric_limits<B>::is_integer, "matrix only accepts float or int types");
        static_assert(std::numeric_limits<C>::is_iec559 || std::numeric_limits<C>::is_integer, "matrix only accepts float or int types");
    }

    // get and set with []
    constexpr vec<3, T> &operator[](int i) {
        assert(i >= 0 && i < 3);
        return data[i];
    }

    constexpr const vec<3, T> &operator[](int i) const {
        assert(i >= 0 && i < 3);
        return data[i];
    }

    // assignment operator:
    template<typename A>
    mat<3, 3, T> &operator=(mat<3, 3, A> const& m) {
        data[0] = m[0];
        data[1] = m[1];
        data[2] = m[2];
        return *this;
    }

    // unary math operators:
    // += 
    template<typename A>
    mat<3, 3, T> &operator+=(mat<3, 3, A> const& m) {
        data[0] += m[0];
        data[1] += m[1];
        data[2] += m[2];
        return *this;
    }

    template<typename A>
    mat<3, 3, T> &operator+=(A scalar) {
        data[0] += scalar;
        data[1] += scalar;
        data[2] += scalar;
        return *this;
    }

    // -= 
    template<typename A>
    mat<3, 3, T> &operator-=(mat<3, 3, A> const& m) {
        data[0] -= m[0];
        data[1] -= m[1];
        data[2] -= m[2];
        return *this;
    }

    template<typename A>
    mat<3, 3, T> &operator-=(A scalar) {
        data[0] -= scalar;
        data[1] -= scalar;
        data[2] -= scalar;
        return *this;
    }

    // *= 
    template<typename A>
    mat<3, 3, T> &operator*=(mat<3, 3, A> const& m) {
        // do matrix multiplication here
        return (*this = *this * m);
    }

    template<typename A>
    mat<3, 3, T> &operator*=(A scalar) {
        data[0] *= scalar;
        data[1] *= scalar;
        data[2] *= scalar;
        return *this;
    }

    // /= 
    template<typename A>
    mat<3, 3, T> &operator/=(mat<3, 3, A> const& m) {
        // do matrix multiplication with inverse of m
        *this *= inverse(m);
        return *this;
    }

    template<typename A>
    mat<3, 3, T> &operator/=(A scalar) {
        data[0] /= scalar;
        data[1] /= scalar;
        data[2] /= scalar;
        return *this;
    }

    // increment and decrement
    // ++vec , --vec
    mat<3, 3, T> &operator++() {
        ++data[0];
		++data[1];
        ++data[2];
        return *this;
    }

    mat<3, 3, T> &operator--() {
        --data[0];
		--data[1];
        --data[2];
        return *this;
    }

    // vec++ , vec--
    mat<3, 3, T> operator++(int) {
        mat<3, 3, T> out(*this);
        ++(*this);
        return out;
    }

    mat<3, 3, T> operator--(int) {
        mat<3, 3, T> out(*this);
        --(*this);
        return out;
    }

    // + and - signs
    mat<3, 3, T> operator+() {
        return *this;
    }

    mat<3, 3, T> operator-() {
        return mat<3, 3, T>(
            -data[0],
            -data[1],
            -data[2]
        );
    }

    // binary math operations
    // addition (+)
    template<typename A>
    mat<3, 3, T> operator+(A a) {
        return mat<3, 3, T>(
			data[0] + a,
			data[1] + a,
            data[2] + a
		);
    }

    template<typename A>
    mat<3, 3, T> operator+(mat<3, 3, A> const& m) {
        return mat<3, 3, T>(
			data[0] + m[0],
			data[1] + m[1],
            data[2] + m[2]
		);
    }

    // subtraction (-)
    template<typename A>
    mat<3, 3, T> operator-(A a) {
        return mat<3, 3, T>(
			data[0] - a,
			data[1] - a,
            data[2] - a
		);
    }

    template<typename A>
    mat<3, 3, T> operator-(mat<3, 3, A> const& m) {
        return mat<3, 3, T>(
			data[0] - m[0],
			data[1] - m[1],
            data[2] - m[2]
		);
    }

    // multiplication (*)
    template<typename A>
    mat<3, 3, T> operator*(A a) {
        return mat<3, 3, T>(
			data[0] * a,
			data[1] * a,
            data[2] * a
		);
    }

    template<typename A>
    mat<3, 3, T> operator*(mat<3, 3, A> const& m) {
        // matrix multiplication

        vec<3, T> a0 = data[0];
        vec<3, T> a1 = data[1];
        vec<3, T> a2 = data[2];

        vec<3, T> b0 = m[0];
        vec<3, T> b1 = m[1];
        vec<3, T> b2 = m[2];

        return mat<3, 3, T>(
			a0 * b0[0] + a1 * b0[1] + a2 * b0[2],
            a0 * b1[0] + a1 * b1[1] + a2 * b1[2],
            a0 * b2[0] + a1 * b2[1] + a2 * b2[2]
		);
    }

    // division (/)
    template<typename A>
    mat<3, 3, T> operator/(A a) {
        return mat<3, 3, T>(
			data[0] / a,
			data[1] / a,
            data[2] / a
		);
    }

    template<typename A>
    mat<3, 3, T> operator/(mat<3, 3, A> const& m) {
        mat<3, 3, T> copy(*this);
        return (copy /= m);
    }

    // boolean operators ==, !=
    template<typename A>
    bool operator==(mat<3, 3, A> const& m) {
        return (data[0] == m[0]) && (data[1] == m[1]) && (data[2] == m[2]);
    }

    template<typename A>
    bool operator!=(mat<3, 3, A> const& m) {
        return (data[0] != m[0]) || (data[1] != m[1]) || (data[2] != m[2]);
    }

};

}
}