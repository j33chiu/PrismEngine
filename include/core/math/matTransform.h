#pragma once

/**
 * defines ortho, frustrum, perspective, lookat, rotation, translation and scaling matrices
 * 
 * also defines 4x4 translate, rotate and scale matricies given a single vector
*/
#include <limits>
#include <cmath>

#include "prismTypeDef.h"
#include "vecFunc.h"

namespace prism {
namespace pml {

//TODO: will need to redefine for LH (directx, vulkan, metal)
    // ortho, frustrum, perspective, lookAt
// currently RH for openGL 


template <typename T>
mat<4, 4, T> ortho(T left, T right, T bottom, T top, T zNear, T zFar) {
    mat<4, 4, T> m;
    m[0][0] = static_cast<T>(2) / (right - left);
    m[1][1] = static_cast<T>(2) / (top - bottom);
    m[2][2] = - static_cast<T>(2) / (zFar - zNear);
    m[3][0] = - (right + left) / (right - left);
    m[3][1] = - (top + bottom) / (top - bottom);
    m[3][2] = - (zFar + zNear) / (zFar - zNear);
    return m;
}

/*
template<typename T>
mat<4, 4, T> frustrum(T left, T right, T bottom, T top, T near, T far) {
    mat<4, 4, T> m;
    m[0][0] = (static_cast<T>(2) * near) / (right - left);
    m[1][1] = (static_cast<T>(2) * near) / (top - bottom);
    m[2][0] = (right + left) / (right - left);
    m[2][1] = (top + bottom) / (top - bottom);
    m[2][2] = - (far + near) / (far - near);
    m[2][3] = static_cast<T>(-1);
    m[3][2] = - (static_cast<T>(2) * far * near) / (far - near);
    return m;
}*/

template<typename T>
mat<4, 4, T> perspective(T fov, T aspectRatio, T zNear, T zFar) {
    assert(std::abs(aspectRatio - std::numeric_limits<T>::epsilon()) > static_cast<T>(0));
    T const fov2 = tan(fov / static_cast<T>(2));

    mat<4, 4, T> m(static_cast<T>(0));
    m[0][0] = static_cast<T>(1) / (aspectRatio * fov2);
    m[1][1] = static_cast<T>(1) / (fov2);
    m[2][2] = - (zFar + zNear) / (zFar - zNear);
    m[2][3] = - static_cast<T>(1);
    m[3][2] = - (static_cast<T>(2) * zFar * zNear) / (zFar - zNear);
    return m;
}

template<typename T>
mat<4, 4, T> infinitePerspective(T fov, T aspectRatio, T zNear, T epsilon) {
    // http://www.terathon.com/gdc07_lengyel.pdf

    T const fov2 = tan(fov / static_cast<T>(2)) * zNear;
    T const left = -fov2 * aspectRatio;
    T const right = fov2 * aspectRatio;
    T const bottom = -fov2;
    T const top = fov2;

    mat<4, 4, T> m(static_cast<T>(0));
    m[0][0] = (static_cast<T>(2) * zNear) / (right - left);
    m[1][1] = (static_cast<T>(2) * zNear) / (top - bottom);
    m[2][2] = epsilon - static_cast<T>(1);
    m[2][3] = static_cast<T>(-1);
    m[3][2] = (epsilon - static_cast<T>(2)) * zNear;
    return m;
}

template<typename T>
mat<4, 4, T> lookAt(vec<3, T> const& eye, vec<3, T> const& center, vec<3, T> const& up)
{
    vec<3, T> const f(normalize(center - eye));
    vec<3, T> const s(normalize(cross(f, up)));
    vec<3, T> const u(cross(s, f));

    mat<4, 4, T> m;
    m[0][0] = s.x;
    m[1][0] = s.y;
    m[2][0] = s.z;
    m[0][1] = u.x;
    m[1][1] = u.y;
    m[2][1] = u.z;
    m[0][2] = -f.x;
    m[1][2] = -f.y;
    m[2][2] = -f.z;
    m[3][0] = -dot(s, eye);
    m[3][1] = -dot(u, eye);
    m[3][2] = dot(f, eye);
    return m;
}

template<typename T>
mat<4, 4, T> rotate(mat<4, 4, T> const& m, T angle, vec<3, T> const& v) {
    T const c = cos(angle);
    T const s = sin(angle);

    vec<3, T> axis(normalize(v));
    vec<3, T> t((static_cast<T>(1) - c) * axis);
    mat<4, 4, T> m1;
    m1[0][0] = c + t[0] * axis[0];
    m1[0][1] = t[0] * axis[1] + s * axis[2];
    m1[0][2] = t[0] * axis[2] - s * axis[1];

    m1[1][0] = t[1] * axis[0] - s * axis[2];
    m1[1][1] = c + t[1] * axis[1];
    m1[1][2] = t[1] * axis[2] + s * axis[0];

    m1[2][0] = t[2] * axis[0] + s * axis[1];
    m1[2][1] = t[2] * axis[1] - s * axis[0];
    m1[2][2] = c + t[2] * axis[2];

    mat<4, 4, T> out;
    out[0] = m[0] * m1[0][0] + m[1] * m1[0][1] + m[2] * m1[0][2];
    out[1] = m[0] * m1[1][0] + m[1] * m1[1][1] + m[2] * m1[1][2];
    out[2] = m[0] * m1[2][0] + m[1] * m1[2][1] + m[2] * m1[2][2];
    out[3] = m[3];
    return out;
}

template<typename T>
mat<4, 4, T> translate(mat< 4, 4, T> const& m, vec<3, T> const& v) {
    mat<4, 4, T> out(m);
    out[3] = m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3];
    return out;
}

template<typename T>
mat<4, 4, T> scale(mat< 4, 4, T> const& m, vec<3, T> const& v) {
    mat<4, 4, T> out;
    out[0] = m[0] * v[0];
    out[1] = m[1] * v[1];
    out[2] = m[2] * v[2];
    out[3] = m[3];
    return out;
}
    
template<typename T>
mat<4, 4, T> translate(vec<3, T> const& v) {
    return translate(mat<4, 4, T>(static_cast<T>(1)), v);
}

template<typename T>
mat<4, 4, T> rotate(T angle, vec<3, T> const& v) {
    return rotate(mat<4, 4, T>(static_cast<T>(1)), angle, v);
}

template<typename T>
mat<4, 4, T> scale(vec<3, T> const& v) {
    return scale(mat<4, 4, T>(static_cast<T>(1)), v);
}

}
}