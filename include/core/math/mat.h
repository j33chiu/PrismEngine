#pragma once

#include <assert.h>
#include <type_traits>
#include <vector>

#include "prismTypeDef.h"

/**
 * generic matrix class from 1x1 to 4x4 large
 * may have more runtime overhead than other matrix classes specified in prism (mat2, mat3, mat4)
*/

namespace prism {
namespace pml {

template<int C, int R, typename T>
struct mat {
    static_assert(std::is_arithmetic<T>::value, "type parameter of this class must be arithmetic");

private:
    vec<R, T> data[C];

public:
    // constructors
    constexpr mat() 
        : mat(1)
    {}

    template<typename A>
    mat(A scalar) {
        for(int i = 0; i < C; i++) {
            data[i] = vec<R, T>();
            if (i < (C < R ? C : R)) {
                data[i][i] = static_cast<T>(scalar);
            }
            //if (i < std::min(C, R));// data[i][i] = static_cast<T>(scalar);
        }
    }

    template<typename A>
    mat(mat<C, R, A> const& m) {
        for(int i = 0; i < C; i++)
            data[i] = m.data[i];
    }

    constexpr int rows() {
        return R;
    }

    constexpr int cols() {
        return C;
    }

    // get and set with []
    constexpr vec<R, T> &operator[](int i) {
        assert(i >= 0 && i < C);
        return data[i];
    }

    constexpr const vec<R, T> &operator[](int i) const {
        assert(i >= 0 && i < C);
        return data[i];
    }

    // assignment:
    constexpr mat<C, R, T> &operator=(mat const& m) = default;

    template<typename A>
    mat<C, R, T> &operator=(mat<C, R, A> const& m) {
        for (int i = 0; i < R; i++)
            data[i] = m[i];
        return *this;
    }

	template<typename A>
    mat<C, R, T> &operator=(A scalar) {
        for (int i = 0; i < C; i++)
            data[i] = scalar;
        return *this;
    }

    // unary operators (+, -)
    mat<C, R, T> operator+() {
        return mat<C, R, T>(*this);
    }

    mat<C, R, T> operator-() {
        mat<C, R, T> m{};
        for (int i = 0; i < C; i++) {
            m[i] = -data[i];
        }
        return m;
    }

    // increment and decrement
    // ++mat , --mat
    mat<C, R, T> &operator++() {
        for (int i = 0; i < C; i++)
            ++data[i];
        return *this;
    }

    mat<C, R, T> &operator--() {
        for (int i = 0; i < C; i++)
            --data[i];
        return *this;
    }

    // mat++ , mat--
    mat<C, R, T> operator++(int) {
        mat<C, R, T> out(*this);
        ++(*this);
        return out;
    }

    mat<C, R, T> operator--(int) {
        mat<C, R, T> out(*this);
        --(*this);
        return out;
    }

    // unary math operators:
    // += 
    template<typename A>
    mat<C, R, T> &operator+=(mat<C, R, A> const& m) {
        for (int i = 0; i < C; i++)
            data[i] += m[i];
        return *this;
    }

    template<typename A>
    mat<C, R, T> &operator+=(A scalar) {
        for (int i = 0; i < C; i++)
            data[i] += scalar;
        return *this;
    }

    // -= 
    template<typename A>
    mat<C, R, T> &operator-=(mat<C, R, A> const& m) {
        for (int i = 0; i < C; i++)
            data[i] -= m[i];
        return *this;
    }

    template<typename A>
    mat<C, R, T> &operator-=(A scalar) {
        for (int i = 0; i < C; i++)
            data[i] -= scalar;
        return *this;
    }

    // *= 
    template<typename A, int N>
    mat<N, R, T> &operator*=(mat<N, C, A> const& m) {
        // do matrix multiplication here
        return (*this = *this * m);
    }

    template<typename A>
    mat<C, R, T> &operator*=(A scalar) {
        for (int i = 0; i < C; i++)
            data[i] *= scalar;
        return *this;
    }

    // /= 
    template<typename A>
    mat<C, R, T> &operator/=(mat<C, R, A> const& m) {
        // do matrix multiplication with inverse of m
        static_assert(C == R, "trying to divide with non square matrices.");
        *this *= inverse(m);
        return *this;
    }

    template<typename A>
    mat<C, R, T> &operator/=(A scalar) {
        for (int i = 0; i < C; i++)
            data[i] /= scalar;
        return *this;
    }

    // binary math operations
    // addition (+)
    template<typename A>
    mat<C, R, T> operator+(A a) {
        mat<C, R, T> out;
        for (int i = 0; i < C; i++)
            out[i] += a;
        return out;
    }

    template<typename A>
    mat<C, R, T> operator+(mat<C, R, A> const& m) {
        mat<C, R, T> out;
        for (int i = 0; i < C; i++)
            out[i] += m[i];
        return out;
    }

    // subtraction (-)
    template<typename A>
    mat<C, R, T> operator-(A a) {
        mat<C, R, T> out;
        for (int i = 0; i < C; i++)
            out[i] -= a;
        return out;
    }

    template<typename A>
    mat<C, R, T> operator-(mat<C, R, A> const& m) {
        mat<C, R, T> out;
        for (int i = 0; i < C; i++)
            out[i] -= m[i];
        return out;
    }

    // multiplication (*)
    template<typename A>
    mat<C, R, T> operator*(A a) {
        mat<C, R, T> out;
        for (int i = 0; i < C; i++)
            out[i] *= a;
        return out;
    }

    template<typename A, int N>
    mat<N, R, T> operator*(mat<N, C, A> const& m) {
        mat<N, R, T> out;

        for(int i = 0; i < N; i++) {
            vec<R, T> col;
            for(int j = 0; j < C; j++) {
                col += data[j] * m[i][j];
            }
            out[i] = col;
        }

        return out;
    }

    // division (/)
    template<typename A>
    mat<C, R, T> operator/(A a) {
        mat<C, R, T> out;
        for (int i = 0; i < C; i++)
            out[i] /= a;
        return out;
    }

    template<typename A>
    mat<C, R, T> operator/(mat<C, R, A> const& m) {
        static_assert(C == R, "trying to divide with non square matrices.");
        mat<C, R, T> copy(*this);
        return (copy /= m);
    }
    
    // boolean operators ==, !=
    template<typename A>
    bool operator==(mat<C, R, A> const& m) {
        for (int i = 0; i < C; i++)
            if (data[i] != m[i]) return false;
        return true;
    }

    template<typename A>
    bool operator!=(mat<2, 2, A> const& m) {
        return !(*this == m);
    }
    

};

}
}