#pragma once

#include <limits>

#include "prismTypeDef.h"
#include "expFunc.h"

/**
 * defines vector functions:
 * dot product, cross product, normalizing, length, face forward, reflect, refract
 * angle between, distance between, 
*/

namespace prism {
namespace pml {
namespace impl {

    template<int L, typename T>
    struct dotCalc{};

    template<typename T>
    struct dotCalc<1, T> {
        static T calc(vec<1, T> const& v1, vec<1, T> const& v2) {
            return v1.x * v2.x;
        }
    };

    template<typename T>
    struct dotCalc<2, T> {
        static T calc(vec<2, T> const& v1, vec<2, T> const& v2) {
            vec<2, T> a(v1 * v2);
            return a.x + a.y;
        }
    };

    template<typename T>
    struct dotCalc<3, T> {
        static T calc(vec<3, T> const& v1, vec<3, T> const& v2) {
            vec<3, T> a(v1 * v2);
            return a.x + a.y + a.z;
        }
    };

    template<typename T>
    struct dotCalc<4, T> {
        static T calc(vec<4, T> const& v1, vec<4, T> const& v2) {
            vec<4, T> a(v1 * v2);
            return a.x + a.y + a.z + a.w;
        }
    };
}

template<int L, typename T, typename A>
T dot(vec<L, T> const& v1, vec<L, A> const& v2) {
    static_assert(std::numeric_limits<T>::is_iec559, "dot only takes floats");
    return impl::dotCalc<L, T>::calc(v1, v2);
}

template<typename T, typename A>
vec<3, T> cross(vec<3, T> const& v1, vec<3, A> const& v2) {
    static_assert(std::numeric_limits<T>::is_iec559, "cross only takes floats");
    return vec<3, T>(
        (v1.y * static_cast<T>(v2.z)) - (v1.z * static_cast<T>(v2.y)),
        (v1.z * static_cast<T>(v2.x)) - (v1.x * static_cast<T>(v2.z)),
        (v1.x * static_cast<T>(v2.y)) - (v1.y * static_cast<T>(v2.x))
    );
}

template<int L, typename T>
vec<L, T> normalize(vec<L, T> const& v) {
    static_assert(std::numeric_limits<T>::is_iec559, "normalize only takes floats");
    return v * inverseSqrt(dot(v, v));
}

template<typename T>
T length(T x) {
    static_assert(std::numeric_limits<T>::is_iec559, "length only takes floats");
    return abs(x);
}

template<int L, typename T>
T length(vec<L, T> const& v) {
    static_assert(std::numeric_limits<T>::is_iec559, "length only takes floats");
    return sqrt(dot(v, v));
}

template<typename T>
T faceForward(T const& v, T const& incident, T const& reference) {
    return dot(reference, incident) < static_cast<T>(0) ? v : -v;
}

template<int L, typename T>
vec<L, T> faceForward(vec<L, T> const& v, vec<L, T> const& incident, vec<L, T> const& reference) {
    static_assert(std::numeric_limits<T>::is_iec559, "faceForward only takes floats");
    return dot(reference, incident) < static_cast<T>(0) ? v : -v;
}

template<typename T>
T reflect(T const& incident, T const& normalizedNorm) {
    return incident - normalizedNorm * dot(normalizedNorm, incident) * T(2);
}

template<int L, typename T>
vec<L, T> reflect(vec<L, T> const& incident, vec<L, T> const& normalizedNorm) {
    return incident - normalizedNorm * dot(normalizedNorm, incident) * T(2);
}

template<typename T>
T refract(T const& normalizedIncident, T const& normalizedNorm, T n1ByN2) {
    static_assert(std::numeric_limits<T>::is_iec559, "refract only takes floats");
    T const cosI(-dot(normalizedNorm, normalizedIncident));
    T const a(static_cast<T>(1) - (n1ByN2 * n1ByN2 * (static_cast<T>(1) - cosI * cosI)));
    return (n1ByN2 * normalizedIncident + (n1ByN2 * cosI - std::sqrt(a)) * normalizedNorm) * static_cast<T>(a >= static_cast<T>(0));
}

template<typename T>
T refract(T const& normalizedIncident, T const& normalizedNorm, T n1, T n2) {
    return refract(normalizedIncident, normalizedNorm, n1/n2);
}

template<int L, typename T>
vec<L, T> refract(vec<L, T> const& normalizedIncident, vec<L, T> const& normalizedNorm, T n1ByN2) {
    static_assert(std::numeric_limits<T>::is_iec559, "refract only takes floats");
    T const cosI(-dot(normalizedNorm, normalizedIncident));
    T const a(static_cast<T>(1) - (n1ByN2 * n1ByN2 * (static_cast<T>(1) - cosI * cosI)));
    return (a >= static_cast<T>(0)) ? (n1ByN2 * normalizedIncident + (n1ByN2 * cosI - std::sqrt(a)) * normalizedNorm) : vec<L, T>(0);
}

template<int L, typename T>
vec<L, T> refract(vec<L, T> const& normalizedIncident, vec<L, T> const& normalizedNorm, T n1, T n2) {
    return refract(normalizedIncident, normalizedNorm, n1/n2);
}


}
}