#pragma once

#include <limits>

#include "prismTypeDef.h"

namespace prism {
namespace pml {

// returns absolute angle between two vectors in radians
template<int L, typename T>
T angle(vec<L, T> const& normalizedV1, vec<L, T> const& normalizedV2) {
    static_assert(std::numeric_limits<T>::is_iec559, "angle only takes floats");

    T a = dot(normalizedV1, normalizedV2);
    T a1 = a > T(-1) ? a : T(-1);
    T a2 = a1 < T(1) ? a1 : T(1);

    return acos(a2);
}

// returns oriented angle between two 2d vectors in radians
template<typename T>
T orientedAngle(vec<2, T> const& normalizedV1, vec<2, T> const& normalizedV2) {
    static_assert(std::numeric_limits<T>::is_iec559, "angle only takes floats");

    T a = dot(normalizedV1, normalizedV2);
    T a1 = a > T(-1) ? a : T(-1);
    T a2 = a1 < T(1) ? a1 : T(1);

    T const a3(acos(a2));
    if (rotate(normalizedV1, a3) == normalizedV2) 
        return a3;
    return -a3;
}

// returns oriented angle between two 3d vectors in radians
template<typename T>
T orientedAngle(vec<3, T> const& normalizedV1, vec<3, T> const& normalizedV2, vec<3, T> const& reference) {
    static_assert(std::numeric_limits<T>::is_iec559, "angle only takes floats");

    T a = dot(normalizedV1, normalizedV2);
    T a1 = a > T(-1) ? a : T(-1);
    T a2 = a1 < T(1) ? a1 : T(1);

    T const a3(acos(a2));
    if (dot(reference, cross(normalizedV1, normalizedV2)) < T(0))
        return -a3;
    return a3;
}



}
}