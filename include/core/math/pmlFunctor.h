#pragma once

#include "prismTypeDef.h"

namespace prism {
namespace pml {

template<template<int L, typename T> class vec, int L, typename U, typename T>
struct vecFunctor{};

template<template<int L, typename T> class vec, typename U, typename T>
struct vecFunctor<vec, 1, U, T> {
    constexpr static vec<1, T> execute(U (*f) (T x), vec<1, T> const& v) {
        return vec<1, T>(f(v.x));
    }
};

template<template<int L, typename T> class vec, typename U, typename T>
struct vecFunctor<vec, 2, U, T> {
    constexpr static vec<2, T> execute(U (*f) (T x), vec<2, T> const& v) {
        return vec<2, T>(f(v.x), f(v.y));
    }
};

template<template<int L, typename T> class vec, typename U, typename T>
struct vecFunctor<vec, 3, U, T> {
    constexpr static vec<3, T> execute(U (*f) (T x), vec<3, T> const& v) {
        return vec<3, T>(f(v.x), f(v.y), f(v.z));
    }
};

template<template<int L, typename T> class vec, typename U, typename T>
struct vecFunctor<vec, 4, U, T> {
    constexpr static vec<4, T> execute(U (*f) (T x), vec<4, T> const& v) {
        return vec<4, T>(f(v.x), f(v.y), f(v.z), f(v.w));
    }
};

template<template<int L, typename T> class vec, int L, typename U, typename T>
struct vecFunctor2{};

template<template<int L, typename T> class vec, typename U, typename T>
struct vecFunctor2<vec, 1, U, T> {
    constexpr static vec<1, T> execute(U (*f) (T x, T y), vec<1, T> const& v1, vec<1, T> const& v2) {
        return vec<1, T>(f(v1.x, v2.x));
    }
};

template<template<int L, typename T> class vec, typename U, typename T>
struct vecFunctor2<vec, 2, U, T> {
    constexpr static vec<2, T> execute(U (*f) (T x, T y), vec<2, T> const& v1, vec<2, T> const& v2) {
        return vec<2, T>(f(v1.x, v2.x), f(v1.y, v2.y));
    }
};

template<template<int L, typename T> class vec, typename U, typename T>
struct vecFunctor2<vec, 3, U, T> {
    constexpr static vec<3, T> execute(U (*f) (T x, T y), vec<3, T> const& v1, vec<3, T> const& v2) {
        return vec<3, T>(f(v1.x, v2.x), f(v1.y, v2.y), f(v1.z, v2.z));
    }
};

template<template<int L, typename T> class vec, typename U, typename T>
struct vecFunctor2<vec, 4, U, T> {
    constexpr static vec<4, T> execute(U (*f) (T x, T y), vec<4, T> const& v1, vec<4, T> const& v2) {
        return vec<4, T>(f(v1.x, v2.x), f(v1.y, v2.y), f(v1.z, v2.z), f(v1.w, v2.w));
    }
};

}
}