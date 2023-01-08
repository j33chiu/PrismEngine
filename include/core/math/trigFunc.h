#pragma once

#include <cmath>
#include <limits>

#include "prismTypeDef.h"
#include "pmlFunctor.h"

namespace prism {
namespace pml {

    // convert degrees to radians
    template<typename T>
    constexpr T toRadians(T degrees) {
        static_assert(std::numeric_limits<T>::is_iec559, "toRadians only takes floats");
        return degrees * static_cast<T>(0.01745329251994329576923690768488612713442871889);
    }

    template<int L, typename T>
    constexpr vec<L, T> toRadians(vec<L, T> const& v) {
        static_assert(std::numeric_limits<T>::is_iec559, "toRadians only takes floats");
        return vecFunctor<vec, L, T, T>::execute(toRadians, v);
    }

    // convert radians to degrees
    template<typename T>
    constexpr T toDegrees(T radians) {
        static_assert(std::numeric_limits<T>::is_iec559, "toDegrees only takes floats");
        return radians * static_cast<T>(57.29577951308232087679815481410517033240547247);
    }

    template<int L, typename T>
    constexpr vec<L, T> toDegrees(vec<L, T> const& v) {
        static_assert(std::numeric_limits<T>::is_iec559, "toDegrees only takes floats");
        return vecFunctor<vec, L, T, T>::execute(toDegrees, v);
    }

    // sin
    template<int L, typename T>
    constexpr vec<L, T> sin(vec<L, T> const& v) {
        return vecFunctor<vec, L, T, T>::execute(std::sin, v);
    }

    // cos
    template<int L, typename T>
    constexpr vec<L, T> cos(vec<L, T> const& v) {
        return vecFunctor<vec, L, T, T>::execute(std::cos, v);
    }

    // tan
    template<int L, typename T>
    constexpr vec<L, T> tan(vec<L, T> const& v) {
        return vecFunctor<vec, L, T, T>::execute(std::tan, v);
    }

    // asin
    template<int L, typename T>
    constexpr vec<L, T> asin(vec<L, T> const& v) {
        return vecFunctor<vec, L, T, T>::execute(std::asin, v);
    }

    // acos
    template<int L, typename T>
    constexpr vec<L, T> acos(vec<L, T> const& v) {
        return vecFunctor<vec, L, T, T>::execute(std::acos, v);
    }

    // atan
    template<int L, typename T>
    constexpr vec<L, T> atan(vec<L, T> const& v) {
        return vecFunctor<vec, L, T, T>::execute(std::atan, v);
    }

    // atan2
    template<int L, typename T>
    constexpr vec<L, T> atan2(vec<L, T> const& v1, vec<L, T> const& v2) {
        return vecFunctor2<vec, L, T, T>::execute(std::atan2, v1, v2);
    }

    // sinh
    template<int L, typename T>
    constexpr vec<L, T> sinh(vec<L, T> const& v) {
        return vecFunctor<vec, L, T, T>::execute(std::sinh, v);
    }

    // cosh
    template<int L, typename T>
    constexpr vec<L, T> cosh(vec<L, T> const& v) {
        return vecFunctor<vec, L, T, T>::execute(std::cosh, v);
    }

    // tanh
    template<int L, typename T>
    constexpr vec<L, T> tanh(vec<L, T> const& v) {
        return vecFunctor<vec, L, T, T>::execute(std::tanh, v);
    }

    // asinh
    template<int L, typename T>
    constexpr vec<L, T> asinh(vec<L, T> const& v) {
        return vecFunctor<vec, L, T, T>::execute(std::asinh, v);
    }

    // acosh
    template<int L, typename T>
    constexpr vec<L, T> acosh(vec<L, T> const& v) {
        return vecFunctor<vec, L, T, T>::execute(std::acosh, v);
    }

    // atanh
    template<int L, typename T>
    constexpr vec<L, T> atanh(vec<L, T> const& v) {
        return vecFunctor<vec, L, T, T>::execute(std::atanh, v);
    }

}
}
