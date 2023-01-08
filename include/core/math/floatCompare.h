#pragma once

#include <cmath>
#include <type_traits>

#include "prismTypeDef.h"

namespace prism {
namespace pml {

#ifndef PRISM_FLOAT_COMPARE_EPSILON
#define PRISM_FLOAT_COMPARE_EPSILON 1e-6
#endif

#ifndef PRISM_DOUBLE_COMPARE_EPSILON
#define PRISM_DOUBLE_COMPARE_EPSILON 1e-9
#endif

#ifndef PRISM_LONG_DOUBLE_COMPARE_EPSILON
#define PRISM_LONG_DOUBLE_COMPARE_EPSILON 1e-12
#endif

template<typename T>
bool equal(FLOAT value, T othervalue) {
    static_assert(std::is_arithmetic<T>::value, "type parameter of othervalue must be arithmetic");
    if (std::abs(value - othervalue) < PRISM_FLOAT_COMPARE_EPSILON) return true;
    return false;
}

template<typename T>
bool equal(DOUBLE value, T othervalue) {
    static_assert(std::is_arithmetic<T>::value, "type parameter of othervalue must be arithmetic");
    if (std::abs(value - othervalue) < PRISM_DOUBLE_COMPARE_EPSILON) return true;
    return false;
}

// for non float types
template<typename T>
bool equal(int value, T othervalue) {
    static_assert(std::is_arithmetic<T>::value, "type parameter of othervalue must be arithmetic");
    return value == othervalue;
}

template<typename T>
bool equal(long value, T othervalue) {
    static_assert(std::is_arithmetic<T>::value, "type parameter of othervalue must be arithmetic");
    return value == othervalue;
}

template<typename T>
bool equal(long long value, T othervalue) {
    static_assert(std::is_arithmetic<T>::value, "type parameter of othervalue must be arithmetic");
    return value == othervalue;
}

template<typename T>
bool equal(bool value, T othervalue) {
    static_assert(std::is_arithmetic<T>::value, "type parameter of othervalue must be arithmetic");
    return value == othervalue;
}



}
}