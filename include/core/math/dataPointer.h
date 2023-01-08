#pragma once

#include "prismTypeDef.h"

namespace prism {
namespace pml {

    template<int L, typename T>
    T const* dataPtr(vec<L, T> const& v) {
        return &(v.x);
    }

    template<int L, typename T>
    T* dataPtr(vec<L, T>& v) {
        return &(v.x);
    }

    template<int C, int R, typename T>
    T const* dataPtr(mat<C, R, T> const& m) {
        return &(m[0].x);
    }

    template<int C, int R, typename T>
    T* dataPtr(mat<C, R, T>& m) {
        return &(m[0].x);
    }


}
}