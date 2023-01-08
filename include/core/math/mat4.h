#pragma once

#include <assert.h>
#include <type_traits>
#include <vector>

#include "prismTypeDef.h"
#include "matFunc.h"

namespace prism {
namespace pml {

/**
 * 4x4 matrix specification
 * data is organized in column-major order, i.e. data[0] is column 1, data[1] is column 2 of the matrix
*/

template<typename T>
struct mat<4, 4, T> {
    static_assert(std::is_arithmetic<T>::value, "type parameter of this class must be arithmetic");

private:
    vec<4, T> data[4];

public:
    // properties:
    static constexpr int rows() {
        return 4;
    }

    static constexpr int cols() {
        return 4;
    }

    // basic constructors
    constexpr mat()
        : data{
            vec<4, T>(1, 0, 0, 0), 
            vec<4, T>(0, 1, 0, 0),
            vec<4, T>(0, 0, 1, 0), 
            vec<4, T>(0, 0, 0, 1)}
    {}

    constexpr mat(mat<2, 2, T> const& m) 
        : data{
            vec<4, T>(m[0]), 
            vec<4, T>(m[1]),
            vec<4, T>(0, 0, 1, 0), 
            vec<4, T>(0, 0, 0, 1)}
    {}

    constexpr mat(mat<3, 3, T> const& m) 
        : data{
            vec<4, T>(m[0]), 
            vec<4, T>(m[1]),
            vec<4, T>(m[2]), 
            vec<4, T>(0, 0, 0, 1)}
    {}

    constexpr mat(mat<4, 4, T> const& m) 
        : data{
            vec<4, T>(m[0]), 
            vec<4, T>(m[1]),
            vec<4, T>(m[2]), 
            vec<4, T>(m[3])}
    {}

    constexpr mat(T const& a) 
        : data{
            vec<4, T>(a, 0, 0, 0), 
            vec<4, T>(0, a, 0, 0),
            vec<4, T>(0, 0, a, 0), 
            vec<4, T>(0, 0, 0, a)}
    {}

    constexpr mat(
        T const& x0, T const& y0, T const& z0, T const& w0,     // column 1
        T const& x1, T const& y1, T const& z1, T const& w1,     // column 2
        T const& x2, T const& y2, T const& z2, T const& w2,     // column 3
        T const& x3, T const& y3, T const& z3, T const& w3)     // column 4
        : data{
            vec<4, T>(x0, y0, z0, w0), 
            vec<4, T>(x1, y1, z1, w1), 
            vec<4, T>(x2, y2, z2, w2), 
            vec<4, T>(x3, y3, z3, w3)}
    {}

    constexpr mat(vec<4, T> const& v1, vec<4, T> const& v2, vec<4, T> const& v3, vec<4, T> const& v4)
        : data{
            vec<4, T>(v1), 
            vec<4, T>(v2),
            vec<4, T>(v3),
            vec<4, T>(v4)}
    {}

    // conversion constructors
    template<typename A>
    constexpr mat(mat<2, 2, A> const& m)
        : data{
            vec<4, T>(m[0]), 
            vec<4, T>(m[1]),
            vec<4, T>(0, 0, 1, 0), 
            vec<4, T>(0, 0, 0, 1)}
    {
        static_assert(std::numeric_limits<A>::is_iec559 || std::numeric_limits<A>::is_integer, "matrix only accepts float or int types");
    }

    template<typename A>
    constexpr mat(mat<3, 3, A> const& m)
        : data{
            vec<4, T>(m[0]), 
            vec<4, T>(m[1]),
            vec<4, T>(m[2]), 
            vec<4, T>(0, 0, 0, 1)}
    {
        static_assert(std::numeric_limits<A>::is_iec559 || std::numeric_limits<A>::is_integer, "matrix only accepts float or int types");
    }

    template<typename A>
    constexpr mat(mat<4, 4, A> const& m)
        : data{
            vec<4, T>(m[0]), 
            vec<4, T>(m[1]),
            vec<4, T>(m[2]), 
            vec<4, T>(m[3])}
    {
        static_assert(std::numeric_limits<A>::is_iec559 || std::numeric_limits<A>::is_integer, "matrix only accepts float or int types");
    }

    template<typename A>
    constexpr mat(A const& a) 
        : data{
            vec<4, T>(a, 0, 0, 0), 
            vec<4, T>(0, a, 0, 0),
            vec<4, T>(0, 0, a, 0), 
            vec<4, T>(0, 0, 0, a)}
    {
        static_assert(std::numeric_limits<A>::is_iec559 || std::numeric_limits<A>::is_integer, "matrix only accepts float or int types");
    }

    template<
        typename X0, typename Y0, typename Z0, typename W0,
        typename X1, typename Y1, typename Z1, typename W1,
        typename X2, typename Y2, typename Z2, typename W2,
        typename X3, typename Y3, typename Z3, typename W3>
    constexpr mat(
        X0 const& x0, Y0 const& y0, Z0 const& z0, W0 const& w0,     // column 1
        X1 const& x1, Y1 const& y1, Z1 const& z1, W1 const& w1,     // column 2
        X2 const& x2, Y2 const& y2, Z2 const& z2, W2 const& w2,     // column 3
        X3 const& x3, Y3 const& y3, Z3 const& z3, W3 const& w3)     // column 4
        : data{
            vec<4, T>(x0, y0, z0, w0), 
            vec<4, T>(x1, y1, z1, w1), 
            vec<4, T>(x2, y2, z2, w2), 
            vec<4, T>(x3, y3, z3, w3)}
    {
        static_assert(std::numeric_limits<X0>::is_iec559 || std::numeric_limits<X0>::is_integer, "matrix only accepts float or int types");
        static_assert(std::numeric_limits<X1>::is_iec559 || std::numeric_limits<X1>::is_integer, "matrix only accepts float or int types");
        static_assert(std::numeric_limits<X2>::is_iec559 || std::numeric_limits<X2>::is_integer, "matrix only accepts float or int types");
        static_assert(std::numeric_limits<X3>::is_iec559 || std::numeric_limits<X3>::is_integer, "matrix only accepts float or int types");
        static_assert(std::numeric_limits<Y0>::is_iec559 || std::numeric_limits<Y0>::is_integer, "matrix only accepts float or int types");
        static_assert(std::numeric_limits<Y1>::is_iec559 || std::numeric_limits<Y1>::is_integer, "matrix only accepts float or int types");
        static_assert(std::numeric_limits<Y2>::is_iec559 || std::numeric_limits<Y2>::is_integer, "matrix only accepts float or int types");
        static_assert(std::numeric_limits<Y3>::is_iec559 || std::numeric_limits<Y3>::is_integer, "matrix only accepts float or int types");
        static_assert(std::numeric_limits<Z0>::is_iec559 || std::numeric_limits<Z0>::is_integer, "matrix only accepts float or int types");
        static_assert(std::numeric_limits<Z1>::is_iec559 || std::numeric_limits<Z1>::is_integer, "matrix only accepts float or int types");
        static_assert(std::numeric_limits<Z2>::is_iec559 || std::numeric_limits<Z2>::is_integer, "matrix only accepts float or int types");
        static_assert(std::numeric_limits<Z3>::is_iec559 || std::numeric_limits<Z3>::is_integer, "matrix only accepts float or int types");
        static_assert(std::numeric_limits<W0>::is_iec559 || std::numeric_limits<W0>::is_integer, "matrix only accepts float or int types");
        static_assert(std::numeric_limits<W1>::is_iec559 || std::numeric_limits<W1>::is_integer, "matrix only accepts float or int types");
        static_assert(std::numeric_limits<W2>::is_iec559 || std::numeric_limits<W2>::is_integer, "matrix only accepts float or int types");
        static_assert(std::numeric_limits<W3>::is_iec559 || std::numeric_limits<W3>::is_integer, "matrix only accepts float or int types");
    }

    template<typename A, typename B, typename C, typename D>
    constexpr mat(vec<4, A> const& v1, vec<4, B> const& v2, vec<4, C> const& v3, vec<4, D> const& v4)
        : data{
            vec<4, A>(v1), 
            vec<4, B>(v2),
            vec<4, C>(v3), 
            vec<4, D>(v4)}
    {
        static_assert(std::numeric_limits<A>::is_iec559 || std::numeric_limits<A>::is_integer, "matrix only accepts float or int types");
        static_assert(std::numeric_limits<B>::is_iec559 || std::numeric_limits<B>::is_integer, "matrix only accepts float or int types");
        static_assert(std::numeric_limits<C>::is_iec559 || std::numeric_limits<C>::is_integer, "matrix only accepts float or int types");
        static_assert(std::numeric_limits<D>::is_iec559 || std::numeric_limits<D>::is_integer, "matrix only accepts float or int types");
    }

    // get and set with []
    constexpr vec<4, T> &operator[](int i) {
        assert(i >= 0 && i < 4);
        return data[i];
    }

    constexpr const vec<4, T> &operator[](int i) const {
        assert(i >= 0 && i < 4);
        return data[i];
    }

    // assignment operator:
    template<typename A>
    mat<4, 4, T> &operator=(mat<4, 4, A> const& m) {
        data[0] = m[0];
        data[1] = m[1];
        data[2] = m[2];
        data[3] = m[3];
        return *this;
    }

    // unary math operators:
    // += 
    template<typename A>
    mat<4, 4, T> &operator+=(mat<4, 4, A> const& m) {
        data[0] += m[0];
        data[1] += m[1];
        data[2] += m[2];
        data[3] += m[3];
        return *this;
    }

    template<typename A>
    mat<4, 4, T> &operator+=(A scalar) {
        data[0] += scalar;
        data[1] += scalar;
        data[2] += scalar;
        data[3] += scalar;
        return *this;
    }

    // -= 
    template<typename A>
    mat<4, 4, T> &operator-=(mat<4, 4, A> const& m) {
        data[0] -= m[0];
        data[1] -= m[1];
        data[2] -= m[2];
        data[3] -= m[3];
        return *this;
    }

    template<typename A>
    mat<4, 4, T> &operator-=(A scalar) {
        data[0] -= scalar;
        data[1] -= scalar;
        data[2] -= scalar;
        data[3] -= scalar;
        return *this;
    }

    // *= 
    template<typename A>
    mat<4, 4, T> &operator*=(mat<4, 4, A> const& m) {
        // do matrix multiplication here
        return (*this = *this * m);
    }

    template<typename A>
    mat<4, 4, T> &operator*=(A scalar) {
        data[0] *= scalar;
        data[1] *= scalar;
        data[2] *= scalar;
        data[3] *= scalar;
        return *this;
    }

    // /= 
    template<typename A>
    mat<4, 4, T> &operator/=(mat<4, 4, A> const& m) {
        // do matrix multiplication with inverse of m
        *this *= inverse(m);
        return *this;
    }

    template<typename A>
    mat<4, 4, T> &operator/=(A scalar) {
        data[0] /= scalar;
        data[1] /= scalar;
        data[2] /= scalar;
        data[3] /= scalar;
        return *this;
    }

    // increment and decrement
    // ++vec , --vec
    mat<4, 4, T> &operator++() {
        ++data[0];
		++data[1];
        ++data[2];
		++data[3];
        return *this;
    }

    mat<4, 4, T> &operator--() {
        --data[0];
		--data[1];
        --data[2];
		--data[3];
        return *this;
    }

    // vec++ , vec--
    mat<4, 4, T> operator++(int) {
        mat<4, 4, T> out(*this);
        ++(*this);
        return out;
    }

    mat<4, 4, T> operator--(int) {
        mat<4, 4, T> out(*this);
        --(*this);
        return out;
    }

    // + and - signs
    mat<4, 4, T> operator+() {
        return *this;
    }

    mat<4, 4, T> operator-() {
        return mat<4, 4, T>(
            -data[0],
            -data[1],
            -data[2],
            -data[3]
        );
    }

    // binary math operations
    // addition (+)
    template<typename A>
    mat<4, 4, T> operator+(A a) {
        return mat<4, 4, T>(
			data[0] + a,
			data[1] + a,
            data[2] + a,
			data[3] + a
		);
    }

    template<typename A>
    mat<4, 4, T> operator+(mat<4, 4, A> const& m) {
        return mat<4, 4, T>(
			data[0] + m[0],
			data[1] + m[1],
            data[2] + m[2],
			data[3] + m[3]
		);
    }

    // subtraction (-)
    template<typename A>
    mat<4, 4, T> operator-(A a) {
        return mat<4, 4, T>(
			data[0] - a,
			data[1] - a,
            data[2] - a,
			data[3] - a
		);
    }

    template<typename A>
    mat<4, 4, T> operator-(mat<4, 4, A> const& m) {
        return mat<4, 4, T>(
			data[0] - m[0],
			data[1] - m[1],
            data[2] - m[2],
			data[3] - m[3]
		);
    }

    // multiplication (*)
    template<typename A>
    mat<4, 4, T> operator*(A a) {
        return mat<4, 4, T>(
			data[0] * a,
			data[1] * a,
            data[2] * a,
			data[3] * a
		);
    }

    template<typename A>
    mat<4, 4, T> operator*(mat<4, 4, A> const& m) {
        // matrix multiplication

        vec<4, T> a0 = data[0];
        vec<4, T> a1 = data[1];
        vec<4, T> a2 = data[2];
        vec<4, T> a3 = data[3];

        vec<4, T> b0 = m[0];
        vec<4, T> b1 = m[1];
        vec<4, T> b2 = m[2];
        vec<4, T> b3 = m[3];

        return mat<4, 4, T>(
			a0 * b0[0] + a1 * b0[1] + a2 * b0[2] + a3 * b0[3],
            a0 * b1[0] + a1 * b1[1] + a2 * b1[2] + a3 * b1[3],
            a0 * b2[0] + a1 * b2[1] + a2 * b2[2] + a3 * b2[3],
            a0 * b3[0] + a1 * b3[1] + a2 * b3[2] + a3 * b3[3]
		);
    }

    // division (/)
    template<typename A>
    mat<4, 4, T> operator/(A a) {
        return mat<4, 4, T>(
			data[0] / a,
			data[1] / a,
            data[2] / a,
			data[3] / a
		);
    }

    template<typename A>
    mat<4, 4, T> operator/(mat<4, 4, A> const& m) {
        mat<4, 4, T> copy(*this);
        return (copy /= m);
    }

    // boolean operators ==, !=
    template<typename A>
    bool operator==(mat<4, 4, A> const& m) {
        return (data[0] == m[0]) && (data[1] == m[1]) && (data[2] == m[2]) && (data[3] == m[3]);
    }

    template<typename A>
    bool operator!=(mat<4, 4, A> const& m) {
        return (data[0] != m[0]) || (data[1] != m[1]) || (data[2] != m[2]) || (data[3] != m[3]);
    }

};

}
}