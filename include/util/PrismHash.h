#pragma once

#include <string>
#include <algorithm>

#include "core/math/pml.h"

namespace {

// override hash for pml::vec objects
template<int L, typename T>
struct std::hash<prism::pml::vec<L, T>> {
    size_t operator()(const prism::pml::vec<L, T>& v) const {
        std::hash<T> hasher;
        std::size_t seed = 0u;
        for(int i = 0; i < L; i++) {
            seed ^= hasher(v[i]) + 0x9e3779b97f4a7c55 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

/**
 * NOTE: combineHash does not give the same results for combineHash(a, b, c) and combineHash(v),
 * where v = vec<3, float>{a, b, c};
*/
// hash based on boost::hash_combine
template<typename First, typename... Rest> 
void combineHash(std::size_t& seed, const First& first, const Rest&... rest) {
    std::hash<First> hasher;
    seed ^= hasher(first) + 0x9e3779b97f4a7c55 + (seed << 6) + (seed >> 2);
    (combineHash(seed, rest), ...);
}

}

namespace prism {

template <class... Args>
std::size_t hash(Args... args) {
    std::size_t seed = 0u;
    combineHash(seed, args...);
    return seed;
}



}