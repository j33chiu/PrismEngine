#pragma once

#include <cstdint>

namespace prism {
namespace pml {

// int scalar:
typedef std::int8_t             INT8;
typedef std::int16_t            INT16;
typedef std::int32_t            INT32;
typedef std::int64_t            INT64;

typedef std::int_fast8_t        FAST_INT8;
typedef std::int_fast16_t       FAST_INT16;
typedef std::int_fast32_t       FAST_INT32;
typedef std::int_fast64_t       FAST_INT64;

// uint scalar
typedef std::uint8_t            UINT8;
typedef std::uint16_t           UINT16;
typedef std::uint32_t           UINT32;
typedef std::uint64_t           UINT64;

typedef std::uint_fast8_t       FAST_UINT8;
typedef std::uint_fast16_t      FAST_UINT16;
typedef std::uint_fast32_t      FAST_UINT32;
typedef std::uint_fast64_t      FAST_UINT64;

// floats
typedef float                   FLOAT;
typedef double                  DOUBLE;

// vectors:
template<int L, typename T> struct vec;

// matrices:
template<int C, int R, typename T> struct mat;

// quaternion
template<typename T> struct qua;

// vector (bool)
typedef vec<1, bool>            bvec1;
typedef vec<2, bool>            bvec2;
typedef vec<3, bool>            bvec3;
typedef vec<4, bool>            bvec4;

// vector (int)
typedef vec<1, INT8>            i8vec1;
typedef vec<2, INT8>            i8vec2;
typedef vec<3, INT8>            i8vec3;
typedef vec<4, INT8>            i8vec4;

typedef vec<1, FAST_INT8>       fast_i8vec1;
typedef vec<2, FAST_INT8>       fast_i8vec2;
typedef vec<3, FAST_INT8>       fast_i8vec3;
typedef vec<4, FAST_INT8>       fast_i8vec4;

typedef vec<1, INT16>           i16vec1;
typedef vec<2, INT16>           i16vec2;
typedef vec<3, INT16>           i16vec3;
typedef vec<4, INT16>           i16vec4;

typedef vec<1, FAST_INT16>      fast_i16vec1;
typedef vec<2, FAST_INT16>      fast_i16vec2;
typedef vec<3, FAST_INT16>      fast_i16vec3;
typedef vec<4, FAST_INT16>      fast_i16vec4;

typedef vec<1, INT32>           i32vec1;
typedef vec<2, INT32>           i32vec2;
typedef vec<3, INT32>           i32vec3;
typedef vec<4, INT32>           i32vec4;

typedef vec<1, FAST_INT32>      fast_i32vec1;
typedef vec<2, FAST_INT32>      fast_i32vec2;
typedef vec<3, FAST_INT32>      fast_i32vec3;
typedef vec<4, FAST_INT32>      fast_i32vec4;

typedef vec<1, INT64>           i64vec1;
typedef vec<2, INT64>           i64vec2;
typedef vec<3, INT64>           i64vec3;
typedef vec<4, INT64>           i64vec4;

typedef vec<1, FAST_INT64>      fast_i64vec1;
typedef vec<2, FAST_INT64>      fast_i64vec2;
typedef vec<3, FAST_INT64>      fast_i64vec3;
typedef vec<4, FAST_INT64>      fast_i64vec4;

// vector (uint)
typedef vec<1, UINT8>           u8vec1;
typedef vec<2, UINT8>           u8vec2;
typedef vec<3, UINT8>           u8vec3;
typedef vec<4, UINT8>           u8vec4;

typedef vec<1, FAST_UINT8>      fast_u8vec1;
typedef vec<2, FAST_UINT8>      fast_u8vec2;
typedef vec<3, FAST_UINT8>      fast_u8vec3;
typedef vec<4, FAST_UINT8>      fast_u8vec4;

typedef vec<1, UINT16>          u16vec1;
typedef vec<2, UINT16>          u16vec2;
typedef vec<3, UINT16>          u16vec3;
typedef vec<4, UINT16>          u16vec4;

typedef vec<1, FAST_UINT16>     fast_u16vec1;
typedef vec<2, FAST_UINT16>     fast_u16vec2;
typedef vec<3, FAST_UINT16>     fast_u16vec3;
typedef vec<4, FAST_UINT16>     fast_u16vec4;

typedef vec<1, UINT32>          u32vec1;
typedef vec<2, UINT32>          u32vec2;
typedef vec<3, UINT32>          u32vec3;
typedef vec<4, UINT32>          u32vec4;

typedef vec<1, FAST_UINT32>     fast_u32vec1;
typedef vec<2, FAST_UINT32>     fast_u32vec2;
typedef vec<3, FAST_UINT32>     fast_u32vec3;
typedef vec<4, FAST_UINT32>     fast_u32vec4;

typedef vec<1, UINT64>          u64vec1;
typedef vec<2, UINT64>          u64vec2;
typedef vec<3, UINT64>          u64vec3;
typedef vec<4, UINT64>          u64vec4;

typedef vec<1, FAST_UINT64>     fast_u64vec1;
typedef vec<2, FAST_UINT64>     fast_u64vec2;
typedef vec<3, FAST_UINT64>     fast_u64vec3;
typedef vec<4, FAST_UINT64>     fast_u64vec4;

// vector (float)
typedef vec<1, FLOAT>           fvec1;
typedef vec<2, FLOAT>           fvec2;
typedef vec<3, FLOAT>           fvec3;
typedef vec<4, FLOAT>           fvec4;

typedef vec<1, DOUBLE>          dvec1;
typedef vec<2, DOUBLE>          dvec2;
typedef vec<3, DOUBLE>          dvec3;
typedef vec<4, DOUBLE>          dvec4;

// vector defaults to FLOAT
typedef vec<1, FLOAT>           vec1;
typedef vec<2, FLOAT>           vec2;
typedef vec<3, FLOAT>           vec3;
typedef vec<4, FLOAT>           vec4;

// matrices (up to 2x2 up to 4x4)
typedef mat<2, 2, FLOAT>        fmat2x2;
typedef mat<2, 3, FLOAT>        fmat2x3;
typedef mat<2, 4, FLOAT>        fmat2x4;

typedef mat<3, 2, FLOAT>        fmat3x2;
typedef mat<3, 3, FLOAT>        fmat3x3;
typedef mat<3, 4, FLOAT>        fmat3x4;

typedef mat<4, 2, FLOAT>        fmat4x2;
typedef mat<4, 3, FLOAT>        fmat4x3;
typedef mat<4, 4, FLOAT>        fmat4x4;

typedef mat<2, 2, DOUBLE>       dmat2x2;
typedef mat<2, 3, DOUBLE>       dmat2x3;
typedef mat<2, 4, DOUBLE>       dmat2x4;

typedef mat<3, 2, DOUBLE>       dmat3x2;
typedef mat<3, 3, DOUBLE>       dmat3x3;
typedef mat<3, 4, DOUBLE>       dmat3x4;

typedef mat<4, 2, DOUBLE>       dmat4x2;
typedef mat<4, 3, DOUBLE>       dmat4x3;
typedef mat<4, 4, DOUBLE>       dmat4x4;

typedef mat<2, 2, FLOAT>        fmat2;
typedef mat<3, 3, FLOAT>        fmat3;
typedef mat<4, 4, FLOAT>        fmat4;

typedef mat<2, 2, DOUBLE>       dmat2;
typedef mat<3, 3, DOUBLE>       dmat3;
typedef mat<4, 4, DOUBLE>       dmat4;

// matrix defaults to FLOAT
typedef mat<2, 2, FLOAT>        mat2;
typedef mat<2, 2, FLOAT>        mat2x2;
typedef mat<3, 3, FLOAT>        mat3;
typedef mat<3, 3, FLOAT>        mat3x3;
typedef mat<4, 4, FLOAT>        mat4;
typedef mat<4, 4, FLOAT>        mat4x4;

// quaternion
typedef qua<FLOAT>              fquat;
typedef qua<FLOAT>              f32quat;

typedef qua<FLOAT>              dquat;
typedef qua<FLOAT>              f64quat;

typedef qua<FLOAT>              quat;

}
}