#pragma once

/** 
 * defines the transpose, inverse and determinant functions for matrices
 * also has element-wise matrix multiplication and the outer product of 2 vectors
*/

#include "prismTypeDef.h"

namespace prism {
namespace pml {
namespace impl {

    /** 
     * struct for calculating determinants of matrices
    */
    template<int C, int R, typename T>
    struct detCalc{};

    template<typename T>
    struct detCalc<2, 2, T>{
        static T calc(mat<2, 2, T> const& m) {
            return m[0][0] * m[1][1] - m[1][0] * m[0][1];
        }
    };

    template<typename T>
    struct detCalc<3, 3, T>{
        static T calc(mat<3, 3, T> const& m) {
            return
                + m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2])
                - m[1][0] * (m[0][1] * m[2][2] - m[2][1] * m[0][2])
                + m[2][0] * (m[0][1] * m[1][2] - m[1][1] * m[0][2]);
        }
    };

    template<typename T>
    struct detCalc<4, 4, T>{
        static T calc(mat<4, 4, T> const& m) {
            // from formula at https://semath.info/src/determinant-four-by-four.html
            T a = m[1][1] * m[2][2] - m[2][1] * m[1][2];
            T b = m[2][1] * m[3][2] - m[3][1] * m[2][2];
            T c = m[3][1] * m[1][2] - m[1][1] * m[3][2];

            T d = m[1][0] * m[3][3] - m[3][0] * m[1][3];
            T e = m[3][0] * m[2][3] - m[2][0] * m[3][3];
            T f = m[2][0] * m[1][3] - m[1][0] * m[2][3];

            vec<4, T> v(
                m[3][3] * a + m[1][3] * b + m[2][3] * c,
                m[2][2] * d + m[1][2] * e + m[3][2] * f,
                m[2][1] * d + m[1][1] * e + m[3][1] * f,
                m[3][0] * a + m[1][0] * b + m[2][0] * c
            );

            return m[0][0] * v[0]
                - m[0][1] * v[1]
                + m[0][2] * v[2]
                - m[0][3] * v[3];
        }
    };

    /**
     * struct for calculating transposes of matrices
    */
    template<int C, int R, typename T>
    struct transposeCalc{};

    template<typename T>
    struct transposeCalc<2, 2, T> {
        static mat<2, 2, T> calc(mat<2, 2, T> const& m) {
            mat<2, 2, T> transpose;
            transpose[0][0] = m[0][0];
            transpose[0][1] = m[1][0];
            transpose[1][0] = m[0][1];
            transpose[1][1] = m[1][1];
            return transpose;
        }
    };

    template<typename T>
    struct transposeCalc<2, 3, T> {
        static mat<3, 2, T> calc(mat<2, 3, T> const& m) {
            mat<3,2, T> transpose;
            transpose[0][0] = m[0][0];
            transpose[0][1] = m[1][0];
            transpose[1][0] = m[0][1];
            transpose[1][1] = m[1][1];
            transpose[2][0] = m[0][2];
            transpose[2][1] = m[1][2];
            return transpose;
        }
    };

    template<typename T>
    struct transposeCalc<2, 4, T> {
        static mat<4, 2, T> calc(mat<2, 4, T> const& m) {
            mat<4, 2, T> transpose;
            transpose[0][0] = m[0][0];
            transpose[0][1] = m[1][0];
            transpose[1][0] = m[0][1];
            transpose[1][1] = m[1][1];
            transpose[2][0] = m[0][2];
            transpose[2][1] = m[1][2];
            transpose[3][0] = m[0][3];
            transpose[3][1] = m[1][3];
            return transpose;
        }
    };

    template<typename T>
    struct transposeCalc<3, 2, T> {
        static mat<2, 3, T> calc(mat<3, 2, T> const& m) {
            mat<2, 3, T> transpose;
            transpose[0][0] = m[0][0];
            transpose[0][1] = m[1][0];
            transpose[0][2] = m[2][0];
            transpose[1][0] = m[0][1];
            transpose[1][1] = m[1][1];
            transpose[1][2] = m[2][1];
            return transpose;
        }
    };

    template<typename T>
    struct transposeCalc<3, 3, T> {
        static mat<3, 3, T> calc(mat<3, 3, T> const& m) {
            mat<3, 3, T> transpose;
            transpose[0][0] = m[0][0];
            transpose[0][1] = m[1][0];
            transpose[0][2] = m[2][0];
            transpose[1][0] = m[0][1];
            transpose[1][1] = m[1][1];
            transpose[1][2] = m[2][1];
            transpose[2][0] = m[0][2];
            transpose[2][1] = m[1][2];
            transpose[2][2] = m[2][2];
            return transpose;
        }
    };

    template<typename T>
    struct transposeCalc<3, 4, T> {
        static mat<4, 3, T> calc(mat<3, 4, T> const& m) {
            mat<4, 3, T> transpose;
            transpose[0][0] = m[0][0];
            transpose[0][1] = m[1][0];
            transpose[0][2] = m[2][0];
            transpose[1][0] = m[0][1];
            transpose[1][1] = m[1][1];
            transpose[1][2] = m[2][1];
            transpose[2][0] = m[0][2];
            transpose[2][1] = m[1][2];
            transpose[2][2] = m[2][2];
            transpose[3][0] = m[0][3];
            transpose[3][1] = m[1][3];
            transpose[3][2] = m[2][3];
            return transpose;
        }
    };

    template<typename T>
    struct transposeCalc<4, 2, T> {
        static mat<2, 4, T> calc(mat<4, 2, T> const& m) {
            mat<2, 4, T> transpose;
            transpose[0][0] = m[0][0];
            transpose[0][1] = m[1][0];
            transpose[0][2] = m[2][0];
            transpose[0][3] = m[3][0];
            transpose[1][0] = m[0][1];
            transpose[1][1] = m[1][1];
            transpose[1][2] = m[2][1];
            transpose[1][3] = m[3][1];
            return transpose;
        }
    };

    template<typename T>
    struct transposeCalc<4, 3, T> {
        static mat<3, 4, T> calc(mat<4, 3, T> const& m) {
            mat<3, 4, T> transpose;
            transpose[0][0] = m[0][0];
            transpose[0][1] = m[1][0];
            transpose[0][2] = m[2][0];
            transpose[0][3] = m[3][0];
            transpose[1][0] = m[0][1];
            transpose[1][1] = m[1][1];
            transpose[1][2] = m[2][1];
            transpose[1][3] = m[3][1];
            transpose[2][0] = m[0][2];
            transpose[2][1] = m[1][2];
            transpose[2][2] = m[2][2];
            transpose[2][3] = m[3][2];
            return transpose;
        }
    };

    template<typename T>
    struct transposeCalc<4, 4, T> {
        static mat<4, 4, T> calc(mat<4, 4, T> const& m) {
            mat<4, 4, T> transpose;
            transpose[0][0] = m[0][0];
            transpose[0][1] = m[1][0];
            transpose[0][2] = m[2][0];
            transpose[0][3] = m[3][0];
            transpose[1][0] = m[0][1];
            transpose[1][1] = m[1][1];
            transpose[1][2] = m[2][1];
            transpose[1][3] = m[3][1];
            transpose[2][0] = m[0][2];
            transpose[2][1] = m[1][2];
            transpose[2][2] = m[2][2];
            transpose[2][3] = m[3][2];
            transpose[3][0] = m[0][3];
            transpose[3][1] = m[1][3];
            transpose[3][2] = m[2][3];
            transpose[3][3] = m[3][3];
            return transpose;
        }
    };

    /**
     * struct for calculating inverse of matrix
    */
    template<int C, int R, typename T>
    struct inverseCalc{};

    // 2x2 matrices
    template<typename T>
    struct inverseCalc<2, 2, T> {
        static mat<2, 2, T> calc(mat<2, 2, T> const& m) {
            T coeff = static_cast<T>(1) / (m[0][0] * m[1][1] - m[1][0] * m[0][1]); // = 1/det(m)
            return mat<2, 2, T>(
                +(m[1][1] * coeff),
                -(m[0][1] * coeff),
                -(m[1][0] * coeff),
                +(m[0][0] * coeff)
            );
        }
    };

    // 3x3 matrices
    template<typename T>
    struct inverseCalc<3, 3, T> {
        static mat<3, 3, T> calc(mat<3, 3, T> const& m) {
            // | a b c |
            // | d e f |
            // | g h i |
            vec<3, T> c0 = m[0];
            vec<3, T> c1 = m[1];
            vec<3, T> c2 = m[2];
            T a = c0[0];
            T b = c1[0];
            T c = c2[0];
            T d = c0[1];
            T e = c1[1];
            T f = c2[1];
            T g = c0[2];
            T h = c1[2];
            T i = c2[2];

            T coeff = static_cast<T>(1) / (
                + a * (e * i - f * h)
                - b * (d * i - f * g)
                + c * (d * h - e * g)
            );

            mat<3, 3, T> inv;
            inv[0][0] = + (e * i - f * h) * coeff;
            inv[1][0] = - (b * i - c * h) * coeff;
            inv[2][0] = + (b * f - c * e) * coeff;
            inv[0][1] = - (d * i - f * g) * coeff;
            inv[1][1] = + (a * i - c * g) * coeff;
            inv[2][1] = - (a * f - c * d) * coeff;
            inv[0][2] = + (d * h - e * g) * coeff;
            inv[1][2] = - (a * h - b * g) * coeff;
            inv[2][2] = + (a * e - b * d) * coeff;

            return inv;
        }
    };

    // 4x4 matrices
    template<typename T>
    struct inverseCalc<4, 4, T> {
        static mat<4, 4, T> calc(mat<4, 4, T> const& m) {
            // | a b c d |
            // | e f g h |
            // | i j k l |
            // | m n o p |

            // laplace expansion theorem
            // https://www.geometrictools.com/Documentation/LaplaceExpansionTheorem.pdf
            T s0 = m[0][0] * m[1][1] - m[0][1] * m[1][0];
            T s1 = m[0][0] * m[2][1] - m[0][1] * m[2][0];
            T s2 = m[0][0] * m[3][1] - m[0][1] * m[3][0];
            T s3 = m[1][0] * m[2][1] - m[1][1] * m[2][0];
            T s4 = m[1][0] * m[3][1] - m[1][1] * m[3][0];
            T s5 = m[2][0] * m[3][1] - m[2][1] * m[3][0];

            T c5 = m[2][2] * m[3][3] - m[2][3] * m[3][2];
            T c4 = m[1][2] * m[3][3] - m[1][3] * m[3][2];
            T c3 = m[1][2] * m[2][3] - m[1][3] * m[2][2];
            T c2 = m[0][2] * m[3][3] - m[0][3] * m[3][2];
            T c1 = m[0][2] * m[2][3] - m[0][3] * m[2][2];
            T c0 = m[0][2] * m[1][3] - m[0][3] * m[1][2];

            T det = s0 * c5 - s1 * c4 + s2 * c3 + s3 * c2 - s4 * c1 + s5 * c0;
            det = static_cast<T>(1) / det;

            mat<4, 4, T> inv(
                // column 1
                + m[1][1] * c5 - m[2][1] * c4 + m[3][1] * c3,
                - m[0][1] * c5 + m[2][1] * c2 - m[3][1] * c1,
                + m[0][1] * c4 - m[1][1] * c2 + m[3][1] * c0,
                - m[0][1] * c3 + m[1][1] * c1 - m[2][1] * c0,
                // column 2
                - m[1][0] * c5 + m[2][0] * c4 - m[3][0] * c3,
                + m[0][0] * c5 - m[2][0] * c2 + m[3][0] * c1,
                - m[0][0] * c4 + m[1][0] * c2 - m[3][0] * c0,
                + m[0][0] * c3 - m[1][0] * c1 + m[2][0] * c0,
                // column 3
                + m[1][3] * s5 - m[2][3] * s4 + m[3][3] * s3,
                - m[0][3] * s5 + m[2][3] * s2 - m[3][3] * s1,
                + m[0][3] * s4 - m[1][3] * s2 + m[3][3] * s0,
                - m[0][3] * s3 + m[1][3] * s1 - m[2][3] * s0,
                // column 4
                - m[1][2] * s5 + m[2][2] * s4 - m[3][2] * s3,
                + m[0][2] * s5 - m[2][2] * s2 + m[3][2] * s1,
                - m[0][2] * s4 + m[1][2] * s2 - m[3][2] * s0,
                + m[0][2] * s3 - m[1][2] * s1 + m[2][2] * s0
            );
            return inv * det;
        }
    };

}

template<int C, int R, typename T>
T determinant(mat<C, R, T> const& m) {
    return impl::detCalc<C, R, T>::calc(m);
}

template<int C, int R, typename T>
mat<R, C, T> transpose(mat<C, R, T> const& m) {
    return impl::transposeCalc<C, R, T>::calc(m);
}

template<int C, int R, typename T>
mat<C, R, T> inverse(mat<C, R, T> const& m) {
    static_assert(std::numeric_limits<T>::is_iec559, "inverse only accepts float inputs");
    return impl::inverseCalc<C, R, T>::calc(m);
}

template<int C, int R, typename T>
mat<C, R, T> elementMult(mat<C, R, T> const& m1, mat<C, R, T> const& m2) {
    mat<C, R, T> product;
    for (int i = 0; i < C; i++) {
        product[i] = m1[i] * m2[i];
    }
    return product;
}

template<int A, int B, typename T1, typename T2>
mat<B, A, T1> outerProduct(vec<A, T1> const& v1, vec<B, T2> const& v2) {
    mat<B, A, T1> result;
    for(int i = 0; i < B; i++)
		result[i] = v1 * v2[i];
	return result;
}

}
}