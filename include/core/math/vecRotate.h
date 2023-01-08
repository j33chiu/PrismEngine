#pragma once

#include "prismTypeDef.h"
#include "matTransform.h"

namespace prism {
namespace pml {
namespace impl {

    enum rotationAxis {
        NONE, X, Y, Z
    };

    template<int L, typename T, rotationAxis AXIS>
    struct rotationCalc{};

    template<typename T>
    struct rotationCalc<2, T, rotationAxis::NONE> {
        static vec<2, T> calc(vec<2, T> const& v, T const& angle) {
            vec<2, T> out;
            T const c(cos(angle));
            T const s(sin(angle));

            out.x = v.x * c - v.y * s;
            out.y = v.x * s + v.y * c;
            return out;
        }
    };

    template<typename T>
    struct rotationCalc<3, T, rotationAxis::NONE> {
        static vec<3, T> calc(vec<3, T> const& v, T const& angle, vec<3, T> const& norm) {
            return mat<3, 3, T>(rotate(angle, norm)) * v;
        }
    };

    template<typename T>
    struct rotationCalc<4, T, rotationAxis::NONE> {
        static vec<4, T> calc(vec<4, T> const& v, T const& angle, vec<3, T> const& norm) {
            return rotate(angle, norm) * v;
        }
    };

    template<typename T>
    struct rotationCalc<3, T, rotationAxis::X> {
        static vec<3, T> calc(vec<3, T> const& v, T const& angle) {
            vec<3, T> out(v);
            T const c(cos(angle));
            T const s(sin(angle));
            out.y = v.y * c - v.z * s;
            out.z = v.y * s + v.z * c;
            return out;
        }  
    };

    template<typename T>
    struct rotationCalc<3, T, rotationAxis::Y> {
        static vec<3, T> calc(vec<3, T> const& v, T const& angle) {
            vec<3, T> out(v);
            T const c(cos(angle));
            T const s(sin(angle));
            out.x = v.x * c + v.z * s;
		    out.z = -v.x * s + v.z * c;
            return out;
        }  
    };


    template<typename T>
    struct rotationCalc<3, T, rotationAxis::Z> {
        static vec<3, T> calc(vec<3, T> const& v, T const& angle) {
            vec<3, T> out(v);
            T const c(cos(angle));
            T const s(sin(angle));
            out.x = v.x * c - v.y * s;
		    out.y = v.x * s + v.y * c;
            return out;
        }  
    };

    template<typename T>
    struct rotationCalc<4, T, rotationAxis::X> {
        static vec<4, T> calc(vec<4, T> const& v, T const& angle) {
            vec<4, T> out(v);
            T const c(cos(angle));
            T const s(sin(angle));
            out.y = v.y * c - v.z * s;
            out.z = v.y * s + v.z * c;
            return out;
        }  
    };

    template<typename T>
    struct rotationCalc<4, T, rotationAxis::Y> {
        static vec<4, T> calc(vec<4, T> const& v, T const& angle) {
            vec<4, T> out(v);
            T const c(cos(angle));
            T const s(sin(angle));
            out.x = v.x * c + v.z * s;
		    out.z = -v.x * s + v.z * c;
            return out;
        }  
    };


    template<typename T>
    struct rotationCalc<4, T, rotationAxis::Z> {
        static vec<4, T> calc(vec<4, T> const& v, T const& angle) {
            vec<4, T> out(v);
            T const c(cos(angle));
            T const s(sin(angle));
            out.x = v.x * c - v.y * s;
		    out.y = v.x * s + v.y * c;
            return out;
        }  
    };
}

template<typename T>
vec<2, T> rotate(vec<2, T> const& v, T const& angle) {
    return impl::rotationCalc<2, T, impl::rotationAxis::NONE>::calc(v, angle);
}

template<typename T>
vec<3, T> rotate(vec<3, T> const& v, T const& angle, vec<3, T> const& norm) {
    return impl::rotationCalc<3, T, impl::rotationAxis::NONE>::calc(v, angle, norm);
}

template<typename T>
vec<4, T> rotate(vec<4, T> const& v, T const& angle, vec<3, T> const& norm) {
    return impl::rotationCalc<4, T, impl::rotationAxis::NONE>::calc(v, angle, norm);
}

template<typename T>
vec<3, T> rotateX(vec<3, T> const& v, T const& angle) {
    return impl::rotationCalc<3, T, impl::rotationAxis::X>::calc(v, angle);
}

template<typename T>
vec<3, T> rotateY(vec<3, T> const& v, T const& angle) {
    return impl::rotationCalc<3, T, impl::rotationAxis::Y>::calc(v, angle);
}

template<typename T>
vec<3, T> rotateZ(vec<3, T> const& v, T const& angle) {
    return impl::rotationCalc<3, T, impl::rotationAxis::Z>::calc(v, angle);
}

template<typename T>
vec<4, T> rotateX(vec<4, T> const& v, T const& angle) {
    return impl::rotationCalc<4, T, impl::rotationAxis::X>::calc(v, angle);
}

template<typename T>
vec<4, T> rotateY(vec<4, T> const& v, T const& angle) {
    return impl::rotationCalc<4, T, impl::rotationAxis::Y>::calc(v, angle);
}

template<typename T>
vec<4, T> rotateZ(vec<4, T> const& v, T const& angle) {
    return impl::rotationCalc<4, T, impl::rotationAxis::Z>::calc(v, angle);
}

}
}