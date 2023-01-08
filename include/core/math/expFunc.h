#pragma once

#include <limits>

#include "prismTypeDef.h"

namespace prism {
namespace pml {

/**
 * contains vector sqrt, inverseSqrt, log, log2, exp, exp2, pow functions
*/

template<typename T>
T sqrt(T const& x) {
    static_assert(std::numeric_limits<T>::is_iec559, "sqrt only takes floats");
    return std::sqrt(x);
}

template<int L, typename T>
vec<L, T> sqrt(vec<L, T> const& v) {
    static_assert(std::numeric_limits<T>::is_iec559, "sqrt only takes floats");
    return vecFunctor<vec, L, T, T>::execute(std::sqrt, v);
}

template<typename T>
T inverseSqrt(T const& x) {
    static_assert(std::numeric_limits<T>::is_iec559, "inverseSqrt only takes floats");
    return static_cast<T>(1) / sqrt(x);
}

template<int L, typename T>
vec<L, T> inverseSqrt(vec<L, T> const& v) {
    static_assert(std::numeric_limits<T>::is_iec559, "inverseSqrt only takes floats");
    return static_cast<T>(1) / sqrt(v);
}

template<int L, typename T>
vec<L, T> fastInverseSqrt(vec<L, T> const& v) {
    vec<L, float> tmp(v);
    vec<L, float> vhalf(tmp * 0.5f);
    vec<L, unsigned int>* p = reinterpret_cast<vec<L, unsigned int>*>(const_cast<vec<L, float>*>(&v));
    vec<L, unsigned int> i = vec<L, unsigned int>(0x5f375a86) - (*p >> vec<L, unsigned int>(1));
    vec<L, float>* ptmp = reinterpret_cast<vec<L, float>*>(&i);
    tmp = *ptmp;
    tmp = tmp * (1.5f - vhalf * tmp * tmp);
    return tmp;
}


template<int L, typename T>
vec<L, T> log(vec<L, T> const& v) {
    return vecFunctor<vec, L, T, T>::execute(std::log, v);
}

template<int L, typename T>
vec<L, T> log2(vec<L, T> const& v) {
    static_assert(std::numeric_limits<T>::is_iec559, "log2 only takes floats");
    return vecFunctor<vec, L, T, T>::execute(std::log2, v);
}

template<int L, typename T>
vec<L, T> exp(vec<L, T> const& v) {
    return vecFunctor<vec, L, T, T>::execute(std::exp, v);
}

template<int L, typename T>
vec<L, T> exp2(vec<L, T> const& v) {
    return vecFunctor<vec, L, T, T>::execute(std::exp2, v);
}

template<int L, typename T>
vec<L, T> pow(vec<L, T> const& base, vec<L, T> const& exponent) {
    return vecFunctor2<vec, L, T, T>::execute(std::pow, base, exponent);
}

}
}