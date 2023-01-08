#include <gtest/gtest.h>

#include "core/math/pml.h"

namespace prismTest {

TEST(mathTests, trigAndExpTests) {
    // trigFunc.h tests:
    {
        float rad = prism::pml::toRadians(123.0f);
        float deg = prism::pml::toDegrees(rad);
        ASSERT_FLOAT_EQ(deg, 123.0f);

        prism::pml::vec3 v1(12, 34, 56);
        prism::pml::vec3 v2 = prism::pml::toRadians(v1);
        prism::pml::vec3 v3(0.209439f, 0.593412f, 0.977384f);
        ASSERT_TRUE(v2 == v3);
        prism::pml::vec3 v4 = prism::pml::toDegrees(v2);
        ASSERT_TRUE(v1 == v4);

        prism::pml::vec3 v5(12, 34, 56);
        prism::pml::vec3 v6 = prism::pml::sin(v5);
        prism::pml::vec3 v7(std::sin(12), std::sin(34), std::sin(56));
        ASSERT_TRUE(v6 == v7);
        ASSERT_FALSE(v6 == v5);
        ASSERT_FLOAT_EQ(v6.y, v7.y);

        v6 = prism::pml::cos(v5);
        v7 = prism::pml::vec3(std::cos(12), std::cos(34), std::cos(56));
        ASSERT_TRUE(v6 == v7);
        ASSERT_FALSE(v6 == v5);
        ASSERT_FLOAT_EQ(v6.y, v7.y);

        v6 = prism::pml::tan(v5);
        v7 = prism::pml::vec3(std::tan(12), std::tan(34), std::tan(56));
        ASSERT_TRUE(v6 == v7);
        ASSERT_FALSE(v6 == v5);
        ASSERT_FLOAT_EQ(v6.y, v7.y);

        v5 = prism::pml::vec3(0.12f, 0.34f, 0.56f);
        v6 = prism::pml::asin(v5);
        v7 = prism::pml::vec3(std::asin(0.12f), std::asin(0.34f), std::asin(0.56f));
        ASSERT_TRUE(v6 == v7);
        ASSERT_FALSE(v6 == v5);
        ASSERT_FLOAT_EQ(v6.y, v7.y);

        v6 = prism::pml::acos(v5);
        v7 = prism::pml::vec3(std::acos(0.12f), std::acos(0.34f), std::acos(0.56f));
        ASSERT_TRUE(v6 == v7);
        ASSERT_FALSE(v6 == v5);
        ASSERT_FLOAT_EQ(v6.y, v7.y);

        v6 = prism::pml::atan(v5);
        v7 = prism::pml::vec3(std::atan(0.12f), std::atan(0.34f), std::atan(0.56f));
        ASSERT_TRUE(v6 == v7);
        ASSERT_FALSE(v6 == v5);
        ASSERT_FLOAT_EQ(v6.y, v7.y);

        v5 = prism::pml::vec3(12.0f, -34.0f, 56.0f);
        v6 = prism::pml::atan2(v5, -v5);
        v7 = prism::pml::vec3(std::atan2(12.0f, -12.0f), std::atan2(-34.0f, 34.0f), std::atan2(56.0f, -56.0f));
        ASSERT_TRUE(v6 == v7);
        ASSERT_FALSE(v6 == v5);
        ASSERT_FLOAT_EQ(v6.y, v7.y);

        v5 = prism::pml::vec3(0.98f, 0.76f, 0.54f);
        v6 = prism::pml::sinh(v5);
        v7 = prism::pml::vec3(std::sinh(0.98f), std::sinh(0.76f), std::sinh(0.54f));
        ASSERT_TRUE(v6 == v7);
        ASSERT_FALSE(v6 == v5);
        ASSERT_FLOAT_EQ(v6.y, v7.y);

        v6 = prism::pml::cosh(v5);
        v7 = prism::pml::vec3(std::cosh(0.98f), std::cosh(0.76f), std::cosh(0.54f));
        ASSERT_TRUE(v6 == v7);
        ASSERT_FALSE(v6 == v5);
        ASSERT_FLOAT_EQ(v6.y, v7.y);

        v6 = prism::pml::tanh(v5);
        v7 = prism::pml::vec3(std::tanh(0.98f), std::tanh(0.76f), std::tanh(0.54f));
        ASSERT_TRUE(v6 == v7);
        ASSERT_FALSE(v6 == v5);
        ASSERT_FLOAT_EQ(v6.y, v7.y);

        v5 = prism::pml::vec3(1.23f, 4.56f, 7.89f);
        v6 = prism::pml::asinh(v5);
        v7 = prism::pml::vec3(std::asinh(1.23f), std::asinh(4.56f), std::asinh(7.89f));
        ASSERT_TRUE(v6 == v7);
        ASSERT_FALSE(v6 == v5);
        ASSERT_FLOAT_EQ(v6.y, v7.y);

        v6 = prism::pml::acosh(v5);
        v7 = prism::pml::vec3(std::acosh(1.23f), std::acosh(4.56f), std::acosh(7.89f));
        ASSERT_TRUE(v6 == v7);
        ASSERT_FALSE(v6 == v5);
        ASSERT_FLOAT_EQ(v6.y, v7.y);

        v6 = prism::pml::atanh(v5 / 10);
        v7 = prism::pml::vec3(std::atanh(0.123f), std::atanh(0.456f), std::atanh(0.789f));
        ASSERT_TRUE(v6 == v7);
        ASSERT_FALSE(v6 == v5);
        ASSERT_FLOAT_EQ(v6.y, v7.y);
    }

    // expFunc.h tests:
    {
        float sq = prism::pml::sqrt(16.0f);
        ASSERT_FLOAT_EQ(sq, 4.0f);

        prism::pml::vec3 v1(12.0f, 34.0f, 56.0f);
        prism::pml::vec3 v2 = prism::pml::sqrt(v1);
        prism::pml::vec3 v3(std::sqrt(v1.x), std::sqrt(v1.y), std::sqrt(v1.z));
        ASSERT_TRUE(v2 == v3);
        ASSERT_FALSE(v1 == v2);
        ASSERT_FLOAT_EQ(v2.z, v3.z);

        v2 = prism::pml::inverseSqrt(v1);
        v3 = prism::pml::vec3(1.0f / std::sqrt(v1.x), 1.0f / std::sqrt(v1.y), 1.0f / std::sqrt(v1.z));
        ASSERT_TRUE(v2 == v3);
        ASSERT_FALSE(v1 == v2);
        ASSERT_FLOAT_EQ(v2.z, v3.z);

        v2 = prism::pml::log(v1);
        v3 = prism::pml::vec3(std::log(v1.x), std::log(v1.y), std::log(v1.z));
        ASSERT_TRUE(v2 == v3);
        ASSERT_FALSE(v1 == v2);
        ASSERT_FLOAT_EQ(v2.z, v3.z);

        v2 = prism::pml::log2(v1);
        v3 = prism::pml::vec3(std::log2(v1.x), std::log2(v1.y), std::log2(v1.z));
        ASSERT_TRUE(v2 == v3);
        ASSERT_FALSE(v1 == v2);
        ASSERT_FLOAT_EQ(v2.z, v3.z);

        v2 = prism::pml::exp(v1);
        v3 = prism::pml::vec3(std::exp(v1.x), std::exp(v1.y), std::exp(v1.z));
        ASSERT_TRUE(v2 == v3);
        ASSERT_FALSE(v1 == v2);
        ASSERT_FLOAT_EQ(v2.z, v3.z);

        v2 = prism::pml::exp2(v1);
        v3 = prism::pml::vec3(std::exp2(v1.x), std::exp2(v1.y), std::exp2(v1.z));
        ASSERT_TRUE(v2 == v3);
        ASSERT_FALSE(v1 == v2);
        ASSERT_FLOAT_EQ(v2.z, v3.z);

        v2 = prism::pml::pow(v1, v1 * 0.1f);
        v3 = prism::pml::vec3(std::pow(v1.x, v1.x * 0.1f), std::pow(v1.y, v1.y * 0.1f), std::pow(v1.z, v1.z * 0.1f));
        ASSERT_TRUE(v2 == v3);
        ASSERT_FALSE(v1 == v2);
        ASSERT_FLOAT_EQ(v2.z, v3.z);
    }

}

TEST(mathTests, vec1Tests) {
    // basic tests:
    prism::pml::vec1 v;
    ASSERT_EQ(v.x, 0);

    v = prism::pml::vec1();
    ASSERT_EQ(v.x, 0);
    v[0] = 1000.0f;
    ASSERT_EQ(v.x, 1000.0f);
    v[0] = -12345;
    ASSERT_EQ(v.x, -12345);
    v.x = -1111;
    ASSERT_EQ(v[0], -1111);

    prism::pml::vec1 v0(-111);
    ASSERT_EQ(v0.x, v0.r);
    ASSERT_EQ(v0.x, -111);
    ASSERT_EQ(v0[0], v0.x);
    ASSERT_EQ(v0[0], -111);

    ASSERT_EQ(v0.size(), 1);

    // constructor tests
    prism::pml::vec1 v1(33);
    prism::pml::vec1 v2 = prism::pml::vec1(1);
    prism::pml::vec1 v3(prism::pml::dvec1(90));
    prism::pml::vec1 v4(6.9f);
    prism::pml::vec1 v5 = +v4;
    prism::pml::vec1 v6 = -v4;
    prism::pml::vec1 v7 = v4;
    v7.x = 3000;
    prism::pml::vec1 v8(v7);
    prism::pml::vec1 v9 = prism::pml::dvec1(91);


    ASSERT_EQ(v1[0], 33);
    ASSERT_EQ(v2[0], 1);
    ASSERT_EQ(v3[0], 90);
    ASSERT_EQ(v4[0], 6.9f);
    ASSERT_EQ(v5[0], 6.9f);
    ASSERT_EQ(v6[0], -6.9f);
    ASSERT_EQ(v7[0], 3000);
    ASSERT_NE(&v4, &v7);
    ASSERT_EQ(v8[0], 3000);
    ASSERT_NE(&v7, &v8);
    ASSERT_EQ(v9[0], 91);

    // assignment tests:
    v9 = v4;
    ASSERT_EQ(v9[0], 6.9f);
    v9 = prism::pml::u8vec1(9.5f);
    ASSERT_EQ(v9[0], 9); 

    // math operations
    prism::pml::vec1 v10;
    ++v10;
    ASSERT_EQ(v10.x, 1);
    prism::pml::vec1 v11(v10--);
    ASSERT_EQ(v11[0], 1);
    ASSERT_EQ(v10[0], 0);
    prism::pml::vec1 v12(--v10);
    ASSERT_EQ(v12[0], -1);
    ASSERT_EQ(v10++[0], -1);
    prism::pml::vec1 v13(100);
    v10 += 9.5f;
    ASSERT_FLOAT_EQ(v10[0], 9.5f);
    v10 += 99;
    ASSERT_FLOAT_EQ(v10[0], 108.5f);
    v10 += v13;
    ASSERT_FLOAT_EQ(v10[0], 208.5f);
    v10 -= 8.1f;
    ASSERT_FLOAT_EQ(v10.x, 200.4f);
    v10 -= 20;
    ASSERT_FLOAT_EQ(v10.x, 180.4f);
    v10 -= v13;
    ASSERT_FLOAT_EQ(v10[0], 80.4f);

    // binary math operations
    prism::pml::vec1 v14 = v10 + v13;
    ASSERT_FLOAT_EQ(v14[0], 180.4f);
    ASSERT_FLOAT_EQ(v10[0], 80.4f);
    ASSERT_EQ(v13[0], 100);
    prism::pml::i64vec1 v15(1000);
    prism::pml::vec1 v16 = v10 + v15;
    ASSERT_FLOAT_EQ(v16[0], 1080.4f);
    v16 = v15 - v10; // v15 is i64, so v10 would be rounded before subtraction
    ASSERT_EQ(v16[0], 920);
    v16 = v10 * v15;
    ASSERT_FLOAT_EQ(v16[0], 80400.0f);
    v16 = v16 / v10;
    ASSERT_FLOAT_EQ(v16[0], 1000.0f);
    ASSERT_TRUE(v16[0] == 1000.0f);
    ASSERT_TRUE(v16[0] != 99.0f);
    v16 = 10 + v16;
    ASSERT_FLOAT_EQ(v16[0], 1010.0f);
    v16 = 2020 - v16;
    ASSERT_FLOAT_EQ(v16[0], 1010.0f);
    v16 = 69.420f;
    ASSERT_FLOAT_EQ(v16[0], 69.420f);
    v16 = 1.5f * v16;
    ASSERT_FLOAT_EQ(v16[0], 104.13f);
    v16 = 104.13f / v16;
    ASSERT_FLOAT_EQ(v16[0], 1.0f);

    prism::pml::bvec1 v17(true);
    ASSERT_TRUE(v17[0]);
    v17 = v17 && false;
    ASSERT_FALSE(v17[0]);
    v17 = v17 || true;
    ASSERT_TRUE(v17[0]);
    v17 = false && v17;
    ASSERT_FALSE(v17[0]);
    v17 = true || v17;
    ASSERT_TRUE(v17[0]);
    v17 = false;
    ASSERT_FALSE(v17[0]);

    // cast other sized vec to vec1
    prism::pml::vec1 v18 = prism::pml::vec2(100.0f, 100.0f);
    ASSERT_FLOAT_EQ(v18[0], 100.0f);

}

TEST(mathTests, vec2Tests) {
    using namespace prism::pml;
    vec2 v1;
    ASSERT_FLOAT_EQ(v1.x, 0.0f);
    ASSERT_FLOAT_EQ(v1.y, 0.0f);
    v1[1] = 1.5f;
    v1.x = -0.9f;
    ASSERT_FLOAT_EQ(v1[0], -0.9f);
    ASSERT_FLOAT_EQ(v1.y, 1.5f);

    vec2 v2 = v1 * 5;
    ASSERT_FLOAT_EQ(v2[0], -4.5f);
    ASSERT_FLOAT_EQ(v2.y, 7.5f);

    v1 *= 5;
    ASSERT_TRUE(v1 == v2);
    v2 = 5;
    ASSERT_FALSE(v1 == v2);
    v2 = v1;
    ASSERT_TRUE(v1 == v2);
    ASSERT_FLOAT_EQ(v1.x, -4.5f);
    ASSERT_FLOAT_EQ(v1[1], 7.5f);
    v2 = v1++;
    ASSERT_TRUE(v1 != v2);
    ASSERT_TRUE(v2 == (v1 - 1));
    v2 = ++v1;
    ASSERT_TRUE(v1 == v2);
    ASSERT_FLOAT_EQ(v1.x, -2.5f);
    ASSERT_FLOAT_EQ(v1[1], 9.5f);

    vec2 v3 = -v1;
    ASSERT_FLOAT_EQ(v3.x, 2.5f);
    ASSERT_FLOAT_EQ(v3[1], -9.5f);
    vec2 v4 = +v3;
    ASSERT_TRUE(v3 == v4);
}

TEST(mathTests, vec3Tests) {
    using namespace prism::pml;
    vec3 v1;
    ASSERT_FLOAT_EQ(v1.x, 0.0f);
    ASSERT_FLOAT_EQ(v1.y, 0.0f);
    ASSERT_FLOAT_EQ(v1.z, 0.0f);
    v1[1] = 1.5f;
    v1.x = -0.9f;
    v1[2] = 555;
    ASSERT_FLOAT_EQ(v1[0], -0.9f);
    ASSERT_FLOAT_EQ(v1.y, 1.5f);
    ASSERT_FLOAT_EQ(v1.z, 555.0f);

    vec3 v2 = v1 * 5;
    ASSERT_FLOAT_EQ(v2[0], -4.5f);
    ASSERT_FLOAT_EQ(v2.y, 7.5f);
    ASSERT_FLOAT_EQ(v2.z, 2775.0f);

    v1 *= 5;
    ASSERT_TRUE(v1 == v2);
    v2 = 5;
    ASSERT_FALSE(v1 == v2);
    v2 = v1;
    ASSERT_TRUE(v1 == v2);
    ASSERT_FLOAT_EQ(v1.x, -4.5f);
    ASSERT_FLOAT_EQ(v1[1], 7.5f);
    ASSERT_FLOAT_EQ(v1.z, 2775.0f);
    v2 = v1++;
    ASSERT_TRUE(v1 != v2);
    ASSERT_TRUE(v2 == (v1 - 1));
    v2 = ++v1;
    ASSERT_TRUE(v1 == v2);
    ASSERT_FLOAT_EQ(v1.x, -2.5f);
    ASSERT_FLOAT_EQ(v1[1], 9.5f);
    ASSERT_FLOAT_EQ(v1.z, 2777.0f);

    vec3 v3 = -v1;
    ASSERT_FLOAT_EQ(v3.x, 2.5f);
    ASSERT_FLOAT_EQ(v3[1], -9.5f);
    ASSERT_FLOAT_EQ(v3.z, -2777.0f);
    vec3 v4 = +v3;
    ASSERT_TRUE(v3 == v4);
}

TEST(mathTests, vec4Tests) {
    using namespace prism::pml;
    vec4 v1;
    ASSERT_FLOAT_EQ(v1.x, 0.0f);
    ASSERT_FLOAT_EQ(v1.y, 0.0f);
    ASSERT_FLOAT_EQ(v1.z, 0.0f);
    ASSERT_FLOAT_EQ(v1.w, 0.0f);
    v1[1] = 1.5f;
    v1.x = -0.9f;
    v1[2] = 555;
    v1.w = -1234;
    ASSERT_FLOAT_EQ(v1[0], -0.9f);
    ASSERT_FLOAT_EQ(v1.y, 1.5f);
    ASSERT_FLOAT_EQ(v1.z, 555.0f);
    ASSERT_FLOAT_EQ(v1[3], -1234.0f);

    vec4 v2 = v1 * 5;
    ASSERT_FLOAT_EQ(v2[0], -4.5f);
    ASSERT_FLOAT_EQ(v2.y, 7.5f);
    ASSERT_FLOAT_EQ(v2.z, 2775.0f);
    ASSERT_FLOAT_EQ(v2[3], -6170.0f);

    v1 *= 5;
    ASSERT_TRUE(v1 == v2);
    v2 = 5;
    ASSERT_FALSE(v1 == v2);
    v2 = v1;
    ASSERT_TRUE(v1 == v2);
    ASSERT_FLOAT_EQ(v1.x, -4.5f);
    ASSERT_FLOAT_EQ(v1[1], 7.5f);
    ASSERT_FLOAT_EQ(v1.z, 2775.0f);
    ASSERT_FLOAT_EQ(v1[3], -6170.0f);
    v2 = v1++;
    ASSERT_TRUE(v1 != v2);
    ASSERT_TRUE(v2 == (v1 - 1));
    v2 = ++v1;
    ASSERT_TRUE(v1 == v2);
    ASSERT_FLOAT_EQ(v1.x, -2.5f);
    ASSERT_FLOAT_EQ(v1[1], 9.5f);
    ASSERT_FLOAT_EQ(v1.z, 2777.0f);
    ASSERT_FLOAT_EQ(v1[3], -6168.0f);

    vec4 v3 = -v1;
    ASSERT_FLOAT_EQ(v3.x, 2.5f);
    ASSERT_FLOAT_EQ(v3[1], -9.5f);
    ASSERT_FLOAT_EQ(v3.z, -2777.0f);
    ASSERT_FLOAT_EQ(v3[3], 6168.0f);
    vec4 v4 = +v3;
    ASSERT_TRUE(v3 == v4);
}

TEST(mathTests, vecAngleTests) {
    // abs angle is tested in vecFuncAndRotateTests
    // test oriented angle
    using namespace prism::pml;
    vec2 v1(1.0f, 0.0f);
    vec2 v2 = normalize(vec2(1.0f, 1.0f));
    FLOAT a1 = angle(v1, v2);
    FLOAT a2 = angle(v2, v1);
    ASSERT_FLOAT_EQ(a1, a2);

    a1 = orientedAngle(v1, v2);
    a2 = orientedAngle(v2, v1);
    ASSERT_FLOAT_EQ(a1, -a2);

    vec3 v3(1.0f, 0.0f, 0.0f);
    vec3 v4 = normalize(vec3(1.0f, 1.0f, 0.0f));
    a1 = angle(v3, v4);
    a2 = angle(v4, v3);
    ASSERT_FLOAT_EQ(a1, a2);

    a1 = orientedAngle(v3, v4, vec3(0.0f, 0.0f, 1.0f));
    a2 = orientedAngle(v4, v3, vec3(0.0f, 0.0f, 1.0f));
    ASSERT_FLOAT_EQ(a1, -a2);
}

TEST(mathTests, vecFuncAndRotateTests) {
    using namespace prism::pml;

    // dot product tests
    vec1 v1 = 5;
    vec2 v2(4, 6);
    vec3 v3(2.5f, 1.3f, 5.6f);
    vec4 v4 = prism::pml::vec4(12.0f, 34, 56, 78.0f);

    float v1d = dot(v1, v1 + 3);
    ASSERT_FLOAT_EQ(v1d, 40.0f);
    float v2d = dot(v2, v2 - 3);
    ASSERT_FLOAT_EQ(v2d, 22.0f);
    float v3d = dot(v3, v3 * 1.5);
    ASSERT_FLOAT_EQ(v3d, 58.95f);
    float v4d = dot(v4, v4 / 0.66f);
    ASSERT_FLOAT_EQ(v4d, 15939.39394f);

    // cross product tests
    
    vec3 c1(2.4f, -4.9f, 12.999f);
    vec3 c2(v3 * -2);
    vec3 c3 = cross(c1, c2);
    vec3 c4 = c3 / 100; // accurate to 6 significant figures, convert to 0.______ for comparison
    vec3 c5 = vec3(0.886774f, -0.38115f, -0.3074f);
    ASSERT_TRUE(c4 == c5);

    // vector normalization tests
    vec1 v1n = normalize(v1);
    vec1 v1n2(1.0f);
    ASSERT_TRUE(v1n == v1n2);
    vec2 v2n = normalize(v2);
    vec2 v2n2(2.0f / std::sqrt(13.0f), 3.0f / std::sqrt(13.0f));
    ASSERT_TRUE(v2n == v2n2);
    vec3 v3n = normalize(v3);
    vec3 v3n2(0.39879f, 0.207371f, 0.893289f);
    ASSERT_TRUE(v3n == v3n2);
    vec4 v4n = normalize(v4);
    vec4 v4n2(0.116997f, 0.33149f, 0.545984f, 0.760478f);
    ASSERT_TRUE(v4n == v4n2);

    // vector length tests
    FLOAT c3l = length(c3);
    ASSERT_FLOAT_EQ(c3l, 101.298480f);
    FLOAT v1l = length(-v1);
    ASSERT_FLOAT_EQ(v1l, 5.0f);

    // faceforward tests
    vec3 ff(51.0f, 23.24f, 0.1112f);
    vec3 ff1(12.34f, 56.78f, 90.12f);
    vec3 ff2(13.0f, 23, 14);
    vec3 ff3 = faceForward(ff, ff1, ff2);
    FLOAT ffDot = dot(ff1, ff2);
    ASSERT_FLOAT_EQ(ffDot, 2728.04f);
    ASSERT_TRUE(-ff == ff3);

    ff1 = -ff1;
    ff3 = faceForward(ff, ff1, ff2);
    ffDot = dot(ff1, ff2);
    ASSERT_FLOAT_EQ(ffDot, -2728.04f);
    ASSERT_TRUE(ff == ff3);

    // vector reflection tests
    // reflection surface has normal in y direction, so only y component should reflect
    vec3 reflInc(-10.0f, -10.0f, 123.456f);
    vec3 reflNorm(0.0f, 1.0f, 0.0f);
    vec3 reflResult = reflect(reflInc, reflNorm);
    vec3 reflExpected(-10.0f, 10.0f, 123.456f);
    ASSERT_TRUE(reflResult == reflExpected);

    // vector refraction tests
    // example from https://www.physicsclassroom.com/class/refrn/Lesson-2/Snell-s-Law
    // 2d example:
    FLOAT n1air = 1.00f;
    FLOAT n2water = 1.33f;
    vec2 refrInc(10.0f, -10.0f);
    vec2 refrNormInc(normalize(refrInc));
    vec2 refrNorm(0.0f, 1.0f);
    vec2 refrResult = refract(refrNormInc, refrNorm, n1air, n2water);
    ASSERT_FLOAT_EQ(length(refrResult), 1.0f);
    FLOAT resultDeg = toDegrees(angle(vec2(0.0f, -1.0f), refrResult));
    ASSERT_FLOAT_EQ(32.11763f, resultDeg);

    // 3d example:
    vec3 refrInc2(11.0f, -22.0f, 33.0f);
    vec3 refrNormInc2(normalize(refrInc2));
    vec3 refrNorm2(0.0f, 1.0f, 0.0f);
    FLOAT refr3dAngle1 = toDegrees(angle(refrNorm2, refrNormInc2));
    ASSERT_FLOAT_EQ(refr3dAngle1, 122.31153f);
    vec3 refrResult2 = refract(refrNormInc2, refrNorm2, n1air, n2water);
    ASSERT_FLOAT_EQ(length(refrResult), 1.0f);
    FLOAT resultDeg2 = toDegrees(angle(vec3(0.0f, -1.0f, 0.0f), refrResult2));
    // sin^-1 (sin(180 - 122.31153) / 1.33) = 39.45369 deg
    ASSERT_FLOAT_EQ(resultDeg2, 39.45369f);
}

TEST(mathTests, matTests) {
    prism::pml::mat4 m0;
    ASSERT_EQ(m0.cols(), 4);
    ASSERT_EQ(m0.rows(), 4);
    ASSERT_FLOAT_EQ(m0[0][0], 1.0f);

    prism::pml::mat4 m1(3000);
    ASSERT_EQ(m1.cols(), 4);
    ASSERT_EQ(m1.rows(), 4);
    ASSERT_FLOAT_EQ(m1[0][0], 3000.0f);

    m1[0][1] = 4;
    ASSERT_FLOAT_EQ(m1[0][1], 4.0f);

    prism::pml::mat4 m2(m1);
    ASSERT_FLOAT_EQ(m2[3][3], 3000.0f);
    ASSERT_FLOAT_EQ(m2[0][1], 4.0f);
    m2[0][1] = -69.42f;
    ASSERT_FLOAT_EQ(m2[0][1], -69.42f);
    ASSERT_FLOAT_EQ(m1[0][1], 4.0f);

    prism::pml::mat<2, 3, int> m3(30);
    ASSERT_EQ(m3[0][2], 0);
    ASSERT_EQ(m3[1][1], 30);

    prism::pml::mat4 m4 = m0;
    m4[0][1] = 20;
    ASSERT_EQ(m4.cols(), 4);
    ASSERT_EQ(m4.rows(), 4);
    ASSERT_FLOAT_EQ(m4[0][1], 20.0f);
    ASSERT_FLOAT_EQ(m0[0][1], 0.0f);

    prism::pml::mat4 m5{};
    
    ASSERT_EQ(m5.cols(), 4);
    ASSERT_EQ(m5.rows(), 4);
    ASSERT_FLOAT_EQ(m5[0][0], 1.0f);

    prism::pml::mat4 m6 = m4;
    ASSERT_DEATH({m6[5][0] = 10;}, ""); // failure from mat
    ASSERT_DEATH({m6[0][-1] = 10;}, ""); // failure from vec
    m6[0] = prism::pml::vec4(-400.5f);
    ASSERT_FLOAT_EQ(m6[0][0], -400.5f);
    ASSERT_FLOAT_EQ(m6[0][1], -400.5f);
    ASSERT_FLOAT_EQ(m6[0][2], -400.5f);
    ASSERT_FLOAT_EQ(m6[0][3], -400.5f);
    ASSERT_FLOAT_EQ(m6[1][1], 1.0f);
    m6[0] = 20;
    ASSERT_EQ(m6[0][0], 20);
    ASSERT_EQ(m6[0][1], 20);
    ASSERT_EQ(m6[0][2], 20);
    ASSERT_EQ(m6[0][3], 20);
    ASSERT_FLOAT_EQ(m6[1][1], 1.0f);

    prism::pml::mat4 m7 = -m6;
    ASSERT_EQ(m7[0][0], -20);
    ASSERT_EQ(m7[0][1], -20);
    ASSERT_EQ(m7[0][2], -20);
    ASSERT_EQ(m7[0][3], -20);
    ASSERT_FLOAT_EQ(m7[1][1], -1.0f);

}

TEST(mathTests, mat2Tests) {
    prism::pml::mat2 m0;
    ASSERT_FLOAT_EQ(m0[0][0], 1.0f);
    ASSERT_FLOAT_EQ(m0[0][1], 0.0f);
    ASSERT_FLOAT_EQ(m0[1][0], 0.0f);
    ASSERT_FLOAT_EQ(m0[1][1], 1.0f);

    prism::pml::mat2 m1(1, 3, 2, 4);
    prism::pml::mat2 m2(5, 7, 6, 8);
    prism::pml::mat2 m3 = m1;
    m3 *= m2;
    ASSERT_FLOAT_EQ(m3[0][0], 19.0f);
    ASSERT_FLOAT_EQ(m3[0][1], 43.0f);
    ASSERT_FLOAT_EQ(m3[1][0], 22.0f);
    ASSERT_FLOAT_EQ(m3[1][1], 50.0f);

    prism::pml::mat2 m4 = m1 * m2;
    ASSERT_FLOAT_EQ(m4[0][0], 19.0f);
    ASSERT_FLOAT_EQ(m4[0][1], 43.0f);
    ASSERT_FLOAT_EQ(m4[1][0], 22.0f);
    ASSERT_FLOAT_EQ(m4[1][1], 50.0f);

    m3 /= m1;
    ASSERT_FLOAT_EQ(m3[0][0], -5);
    ASSERT_FLOAT_EQ(m3[0][1], -11);
    ASSERT_FLOAT_EQ(m3[1][0], 8);
    ASSERT_FLOAT_EQ(m3[1][1], 18);

    prism::pml::mat2 m5 = m1 / m2;
    ASSERT_FLOAT_EQ(m5[0][0], 3);
    ASSERT_FLOAT_EQ(m5[0][1], 2);
    ASSERT_FLOAT_EQ(m5[1][0], -2);
    ASSERT_FLOAT_EQ(m5[1][1], -1);

    prism::pml::mat2 m6 = prism::pml::mat2(6);
    ASSERT_FLOAT_EQ(m6[0][0], 6.0f);
    ASSERT_FLOAT_EQ(m6[0][1], 0.0f);
    ASSERT_FLOAT_EQ(m6[1][0], 0.0f);
    ASSERT_FLOAT_EQ(m6[1][1], 6.0f);

    m6 += m5;
    ASSERT_FLOAT_EQ(m6[0][0], 9.0f);
    ASSERT_FLOAT_EQ(m6[0][1], 2.0f);
    ASSERT_FLOAT_EQ(m6[1][0], -2.0f);
    ASSERT_FLOAT_EQ(m6[1][1], 5.0f);

    prism::pml::mat2 m7 = m6 + m6;
    ASSERT_FLOAT_EQ(m7[0][0], 18.0f);
    ASSERT_FLOAT_EQ(m7[0][1], 4.0f);
    ASSERT_FLOAT_EQ(m7[1][0], -4.0f);
    ASSERT_FLOAT_EQ(m7[1][1], 10.0f);

    prism::pml::mat2 m8 = m7 - m6;
    ASSERT_FLOAT_EQ(m8[0][0], 9.0f);
    ASSERT_FLOAT_EQ(m8[0][1], 2.0f);
    ASSERT_FLOAT_EQ(m8[1][0], -2.0f);
    ASSERT_FLOAT_EQ(m8[1][1], 5.0f);

    m8 -= m8;
    ASSERT_FLOAT_EQ(m8[0][0], 0.0f);
    ASSERT_FLOAT_EQ(m8[0][1], 0.0f);
    ASSERT_FLOAT_EQ(m8[1][0], 0.0f);
    ASSERT_FLOAT_EQ(m8[1][1], 0.0f);

    prism::pml::mat2 m9 = m8++;
    ASSERT_FLOAT_EQ(m9[0][0], 0.0f);
    ASSERT_FLOAT_EQ(m9[0][1], 0.0f);
    ASSERT_FLOAT_EQ(m9[1][0], 0.0f);
    ASSERT_FLOAT_EQ(m9[1][1], 0.0f);

    ASSERT_FLOAT_EQ(m8[0][0], 1.0f);
    ASSERT_FLOAT_EQ(m8[0][1], 1.0f);
    ASSERT_FLOAT_EQ(m8[1][0], 1.0f);
    ASSERT_FLOAT_EQ(m8[1][1], 1.0f);

    prism::pml::mat2 m10 = --m8;
    ASSERT_FLOAT_EQ(m10[0][0], 0.0f);
    ASSERT_FLOAT_EQ(m10[0][1], 0.0f);
    ASSERT_FLOAT_EQ(m10[1][0], 0.0f);
    ASSERT_FLOAT_EQ(m10[1][1], 0.0f);

    ASSERT_FLOAT_EQ(m8[0][0], 0.0f);
    ASSERT_FLOAT_EQ(m8[0][1], 0.0f);
    ASSERT_FLOAT_EQ(m8[1][0], 0.0f);
    ASSERT_FLOAT_EQ(m8[1][1], 0.0f);

    ASSERT_TRUE(m8 == m10);
    ASSERT_FALSE(m8 != m10);
    ASSERT_FALSE(m1 == m2);
    ASSERT_TRUE(m1 != m2);

}

TEST(mathTests, mat3Tests) {
    using namespace prism::pml;
    mat3 m1;
    mat3 m2(m1 * 2);
    mat3 m3 = m1 - mat3();
    ASSERT_FLOAT_EQ(m1[1][1], 1.0f);
    ASSERT_FLOAT_EQ(m2[1][1], 2.0f);
    ASSERT_FLOAT_EQ(m3[1][1], 0.0f);
    mat3 m4(1, 0, 0,
            0, 1, 0,
            0, 0, 1);
    mat3 m5(2, 0, 0,
            0, 2, 0,
            0, 0, 2);
    mat3 m6(0, 0, 0,
            0, 0, 0,
            0, 0, 0);
    ASSERT_TRUE(m1 == m4);
    ASSERT_TRUE(m2 == m5);
    ASSERT_TRUE(m3 == m6);

    m1[1] = vec3(3, 3, 3);
    m1[1][2] = 4.5f;
    mat3 m7(1, 0, 0,
            3, 3, 4.5f,
            0, 0, 1);
    ASSERT_TRUE(m1 == m7);

    mat3 m8(m7);
    mat3 m9 = m7++;
    mat3 m10(2, 1, 1,
             4, 4, 5.5f,
             1, 1, 2);
    ASSERT_TRUE(m8 == m9);
    ASSERT_TRUE(m7 == m10);
    m10 = --m7;
    ASSERT_TRUE(m7 == m10);
    ASSERT_TRUE(m7 == m9);
    mat3 m11(2, 0, 0,
             3, 3, 4.5f,
             0, 0, 1);
    ASSERT_FALSE(m7 == m11);
    m11 *= 3.1f;
    mat3 m12(6.2f, 0, 0,
             9.3f, 9.3f, 13.95f,
             0, 0, 3.1f);
    ASSERT_TRUE(m11 == m12);
    ASSERT_FLOAT_EQ(m11[0][0], m12[0][0]);
    ASSERT_FLOAT_EQ(m11[1][1], m12[1][1]);
    ASSERT_FLOAT_EQ(m11[2][2], m12[2][2]);
    ASSERT_TRUE(m11[0] == m12[0]);
    ASSERT_TRUE(m11[1] == m12[1]);
    ASSERT_TRUE(m11[2] == m12[2]);
}

TEST(mathTests, mat4Tests) {
    using namespace prism::pml;
    mat4 m1;
    mat4 m2(m1 * 2);
    mat4 m3 = m1 - mat4();
    ASSERT_FLOAT_EQ(m1[1][1], 1.0f);
    ASSERT_FLOAT_EQ(m2[1][1], 2.0f);
    ASSERT_FLOAT_EQ(m3[1][1], 0.0f);
    mat4 m4(1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1);
    mat4 m5(2, 0, 0, 0,
            0, 2, 0, 0,
            0, 0, 2, 0,
            0, 0, 0, 2);
    mat4 m6(0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0);
    ASSERT_TRUE(m1 == m4);
    ASSERT_TRUE(m2 == m5);
    ASSERT_TRUE(m3 == m6);

    m1[1] = vec4(3, 3, 3, 3);
    m1[1][2] = 4.5f;
    m1[3][2] = -0.14f;
    mat4 m7(1, 0, 0, 0,
            3, 3, 4.5f, 3,
            0, 0, 1, 0,
            0, 0, -0.14f, 1);
    ASSERT_TRUE(m1 == m7);

    mat4 m8(m7);
    mat4 m9 = m7++;
    mat4 m10(2, 1, 1, 1,
             4, 4, 5.5f, 4,
             1, 1, 2, 1,
             1, 1, 0.86f, 2);
    ASSERT_TRUE(m8 == m9);
    ASSERT_TRUE(m7 == m10);
    m10 = --m7;
    ASSERT_TRUE(m7 == m10);
    ASSERT_TRUE(m7 == m9);
    mat4 m11(2, 0, 0, 0,
             3, 3, 4.5f, 3,
             0, 0, 1, 0,
             0, 0, -0.14f, 1);
    ASSERT_FALSE(m7 == m11);
    m11 *= 3.1f;
    mat4 m12(6.2, 0, 0, 0,
             9.3, 9.3, 13.95f, 9.3,
             0, 0, 3.1, 0,
             0, 0, -0.434f, 3.1);
    ASSERT_TRUE(m11 == m12);
    ASSERT_FLOAT_EQ(m11[0][0], m12[0][0]);
    ASSERT_FLOAT_EQ(m11[1][1], m12[1][1]);
    ASSERT_FLOAT_EQ(m11[2][2], m12[2][2]);
    ASSERT_FLOAT_EQ(m11[3][3], m12[3][3]);
    ASSERT_TRUE(m11[0] == m12[0]);
    ASSERT_TRUE(m11[1] == m12[1]);
    ASSERT_TRUE(m11[2] == m12[2]);
    ASSERT_TRUE(m11[3] == m12[3]);
}

TEST(mathTests, matrixMultiplicationTests) {
    using namespace prism::pml;

    // 2x2 * 2x2
    mat2 m1(61, 454, 
            2, -3);
    mat2 m2(12, 34, 
            -2, 53);
    mat2 m1m2 = m1 * -m2;
    mat2 m1m2Res(-800, -5346, 
                 16, 1067);
    ASSERT_TRUE(m1m2 == m1m2Res);

    // 3x3 * 3x3
    mat3 m3(12, -453, -2, 
            -62, 685, -62,
            9, -1, 2);
    mat3 m4(61, -62, 3, 
            2, -3, -653, 
            -34, 54, 2);
    mat3 m3m4 = -m3 * m4;
    mat3 m3m4Res(-4603, 70106, -3728, 
                 5667, 2308, 1124, 
                 3738, -52390, 3276);
    ASSERT_TRUE(m3m4 == m3m4Res);

    // 4x4 * 4x4
    mat4 m5(67, 37, 7, -8, 
            27, -372, -2, 45, 
            -4, -347, -2437, 327, 
            5, 425, -2, 939);
    mat4 m6(89, 73, -4, 5, 
            -54, -12, -73, 26, 
            12, 2, -3, -3425, 
            -25, -1356, 71, -51);
    mat4 m5m6 = m5 * m6;
    mat4 m5m6Res(7975, -20350, 10215, 5960, 
                 -3520, 38847, 177495, 435, 
                 -16255, -1454884, 14241, -3217062, 
                 -38826, 457195, -170388, -85492);
    ASSERT_TRUE(m5m6 == m5m6Res);
}

TEST(mathTests, matFuncTests) {
    // determinant tests
    prism::pml::mat4 m0;
    m0[0] = prism::pml::vec4(34, 89, -66, 56);
    m0[1] = prism::pml::vec4(23, 46, -89, 28);
    m0[2] = prism::pml::vec4(12, -88, 67, 44);
    m0[3] = prism::pml::vec4(42, -24, 21, 19);
    ASSERT_FLOAT_EQ(prism::pml::determinant(m0), 17369125.0f);

    prism::pml::mat3 m1;
    m1[0] = prism::pml::vec3(34, 89, -66);
    m1[1] = prism::pml::vec3(23, 46, -89);
    m1[2] = prism::pml::vec3(12, -88, 67);
    ASSERT_FLOAT_EQ(prism::pml::determinant(m1), -223685.0f);

    prism::pml::mat2 m2;
    m2[0] = prism::pml::vec2(34, 89);
    m2[1] = prism::pml::vec2(23, 46);
    ASSERT_FLOAT_EQ(prism::pml::determinant(m2), -483.0f);

    // transpose tests
    prism::pml::mat2 m3;
    m3[0] = prism::pml::vec2(34, 89);
    m3[1] = prism::pml::vec2(23, 46);
    prism::pml::mat2 m4;
    m4[0] = prism::pml::vec2(34, 23);
    m4[1] = prism::pml::vec2(89, 46);
    ASSERT_TRUE(prism::pml::transpose(m3) == m4);

    prism::pml::mat<4, 3, prism::pml::FLOAT> m5;
    m5[0] = prism::pml::vec3(34, 89, -66);
    m5[1] = prism::pml::vec3(23, 46, -89);
    m5[2] = prism::pml::vec3(12, -88, 67);
    m5[3] = prism::pml::vec3(55, -90, 18);
    prism::pml::mat<3, 4, prism::pml::FLOAT> m6;
    m6[0] = prism::pml::vec4(34, 23, 12, 55);
    m6[1] = prism::pml::vec4(89, 46, -88, -90);
    m6[2] = prism::pml::vec4(-66, -89, 67, 18);
    ASSERT_TRUE(prism::pml::transpose(m5) == m6);

    // inverse tests
    prism::pml::mat4 m7;
    m7[0] = prism::pml::vec4(6, 9, -9, 6);
    m7[1] = prism::pml::vec4(1, -8, 1, 2);
    m7[2] = prism::pml::vec4(2, 6, -3, -5);
    m7[3] = prism::pml::vec4(-4, 5, 2, 7);
    m7 = prism::pml::inverse(m7);
    prism::pml::mat4 m8;
    m8[0] = prism::pml::vec4(-25.0f/42.0f, 37.0f/7.0f, 11.0f/2.0f, 41.0f/14.0f);
    m8[1] = prism::pml::vec4(-1.0f/6.0f, 4.0f/3.0f, 3.0f/2.0f, 5.0f/6.0f);
    m8[2] = prism::pml::vec4(-29.0f/42.0f, 110.0f/21.0f, 11.0f/2.0f, 127.0f/42.0f);
    m8[3] = prism::pml::vec4(-1.0f/42.0f, 4.0f/7.0f, 0.5f, 5.0f/14.0f);
    ASSERT_TRUE(m7 == m8);

    // element mult tests
    using namespace prism::pml;
    // 4x4 * 4x4
    mat4 m9(67, 37, 7, -8, 
            27, -372, -2, 45, 
            -4, -347, -2437, 327, 
            5, 425, -2, 939);
    mat4 m10(89, 73, -4, 5, 
             -54, -12, -73, 26, 
             12, 2, -3, -3425, 
             -25, -1356, 71, -51);
    mat4 m11 = elementMult(m9, m10);
    mat4 m12(5963, 2701, -28, -40,
             -1458, 4464, 146, 1170,
             -48, -694, 7311, -1119975,
             -125, -576300, -142, -47889);
    ASSERT_TRUE(m11 == m12);

    // outer product tests
    vec2 v1(-3.5, 4);
    vec4 v2(3, -7, -8, 8);
    mat<4, 2, FLOAT> m13 = outerProduct(v1, v2);
    mat<4, 2, FLOAT> m14;
    m14[0] = vec2(-10.5, 12);
    m14[1] = vec2(24.5, -28);
    m14[2] = vec2(28, -32);
    m14[3] = vec2(-28, 32);
    ASSERT_TRUE(m13 == m14);
}

TEST(mathTests, matTransformTests) {

}

TEST(mathTests, sizeofTests) {
    prism::pml::vec<3, prism::pml::INT8> v0;
    ASSERT_EQ(sizeof(v0), 3);
    prism::pml::vec<3, prism::pml::INT16> v1;
    ASSERT_EQ(sizeof(v1), 6);
    prism::pml::vec<3, prism::pml::INT32> v2;
    ASSERT_EQ(sizeof(v2), 12);
    prism::pml::vec<3, prism::pml::INT64> v3;
    ASSERT_EQ(sizeof(v3), 24);

    prism::pml::vec<3, prism::pml::FLOAT> v4;
    ASSERT_EQ(sizeof(v4), 12);
    prism::pml::vec<3, prism::pml::DOUBLE> v5;
    ASSERT_EQ(sizeof(v5), 24);

}

TEST(mathTests, dataPointerTests) {
    using namespace prism::pml;
    mat4 m1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    //mat4* m1Ptr0 = std::addressof(m1);
    FLOAT* m1Ptr = dataPtr(m1);
    //ASSERT_EQ(m1Ptr0, m1Ptr);
    ASSERT_FLOAT_EQ(*m1Ptr, 1.0f);
    m1Ptr += 7;
    ASSERT_FLOAT_EQ(*m1Ptr, 8.0f);
    m1Ptr -= 7;
    ASSERT_FLOAT_EQ(*m1Ptr, 1.0f);
    ASSERT_FLOAT_EQ(m1Ptr[15], 16.0f);
    m1[3][3] = -123.45678f;
    ASSERT_FLOAT_EQ(m1Ptr[15], -123.45678f);

    vec4 v1(4, 3, 2, 1);
    FLOAT* v1Ptr = dataPtr(v1);
    ASSERT_FLOAT_EQ(*v1Ptr, 4.0f);
    v1Ptr++;
    ASSERT_FLOAT_EQ(*v1Ptr, 3.0f);
    v1Ptr--;
    ASSERT_FLOAT_EQ(*v1Ptr, 4.0f);
    ASSERT_FLOAT_EQ(v1Ptr[3], 1.0f);
    v1[3] = -123.45678f;
    ASSERT_FLOAT_EQ(v1Ptr[3], -123.45678f);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

}