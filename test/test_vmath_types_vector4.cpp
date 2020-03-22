#include "vmath_types.h"

#include <gtest/gtest.h>

#include <cmath>
#include <vector>
#include <numeric>

namespace {
struct DummyVec {
    double s = 9.1;
    double x = 10.1;
    double y = 11.1;
    double z = 12.1;
    double w = 13.1;
};
} // namespace

// /////// //
// Vector4 //
// /////// //

TEST(Vector4, constructors) {
    // default constructor
    math::Vector4d v1;
    ASSERT_DOUBLE_EQ(v1.x, 0.0);
    ASSERT_DOUBLE_EQ(v1.y, 0.0);
    ASSERT_DOUBLE_EQ(v1.z, 0.0);
    ASSERT_DOUBLE_EQ(v1.w, 0.0);
    ASSERT_DOUBLE_EQ(v1.r, 0.0);
    ASSERT_DOUBLE_EQ(v1.g, 0.0);
    ASSERT_DOUBLE_EQ(v1.b, 0.0);
    ASSERT_DOUBLE_EQ(v1.a, 0.0);
    // explicit constructor
    math::Vector4d v2(3.1, 4.2, 5.3, 6.4);
    ASSERT_DOUBLE_EQ(v2.x, 3.1);
    ASSERT_DOUBLE_EQ(v2.y, 4.2);
    ASSERT_DOUBLE_EQ(v2.z, 5.3);
    ASSERT_DOUBLE_EQ(v2.w, 6.4);
    // copy constructor
    math::Vector4d v3(v2);
    ASSERT_DOUBLE_EQ(v3.x, 3.1);
    ASSERT_DOUBLE_EQ(v3.y, 4.2);
    ASSERT_DOUBLE_EQ(v3.z, 5.3);
    ASSERT_DOUBLE_EQ(v3.w, 6.4);
    // from a different vector type or size
    math::Vector4i vv1(6, 7, 8, 9);
    math::Vector4d v4(vv1);
    ASSERT_DOUBLE_EQ(v4.x, 6.0);
    ASSERT_DOUBLE_EQ(v4.y, 7.0);
    ASSERT_DOUBLE_EQ(v4.z, 8.0);
    ASSERT_DOUBLE_EQ(v4.w, 9.0);
    math::Vector4d v5(DummyVec{});
    ASSERT_DOUBLE_EQ(v5.x, 10.1);
    ASSERT_DOUBLE_EQ(v5.y, 11.1);
    ASSERT_DOUBLE_EQ(v5.z, 12.1);
    ASSERT_DOUBLE_EQ(v5.w, 13.1);
}

TEST(Vector4, assignment) {
    math::Vector4f v1;
    math::Vector4f v2(13.1,15.2,16.3,17.4);
    v1 = v2;
    ASSERT_DOUBLE_EQ(v1.x, v2.x);
    ASSERT_DOUBLE_EQ(v1.y, v2.y);
    ASSERT_DOUBLE_EQ(v1.z, v2.z);
    ASSERT_DOUBLE_EQ(v1.w, v2.w);
}

TEST(Vector4, access) {
    const math::Vector4f v1(11.1,22.2,33.3,44.4);
    double x = v1[0];
    double y = v1[1];
    double z = v1[2];
    double w = v1[3];
    ASSERT_FLOAT_EQ(x, 11.1);
    ASSERT_FLOAT_EQ(y, 22.2);
    ASSERT_FLOAT_EQ(z, 33.3);
    ASSERT_FLOAT_EQ(w, 44.4);
    math::Vector4f v2(13.1,15.2,17.3,19.4);
    v2[0] = 4.1;
    v2[1] = 4.2;
    v2[2] = 4.3;
    v2[3] = 4.4;
    ASSERT_FLOAT_EQ(v2.x, 4.1);
    ASSERT_FLOAT_EQ(v2.y, 4.2);
    ASSERT_FLOAT_EQ(v2.z, 4.3);
    ASSERT_FLOAT_EQ(v2.w, 4.4);
}

TEST(Vector4, vector_operations_internal) {
    const math::Vector4f v1(1.1,2.2,3.3,4.4);
    const math::Vector4f v2(3.3,5.4,6.6,7.9);
    math::Vector4f v3 = v1+v2;
    math::Vector4f v4 = v1-v2;
    ASSERT_FLOAT_EQ(v3.x, 4.4);
    ASSERT_FLOAT_EQ(v3.y, 7.6);
    ASSERT_FLOAT_EQ(v3.z, 9.9);
    ASSERT_FLOAT_EQ(v3.w, 12.3);
    ASSERT_FLOAT_EQ(v4.x, -2.2);
    ASSERT_FLOAT_EQ(v4.y, -3.2);
    ASSERT_FLOAT_EQ(v4.z, -3.3);
    ASSERT_FLOAT_EQ(v4.w, -3.5);
    v3 += v1;
    v4 -= v1;
    ASSERT_FLOAT_EQ(v3.x, 5.5);
    ASSERT_FLOAT_EQ(v3.y, 9.8);
    ASSERT_FLOAT_EQ(v3.z, 13.2);
    ASSERT_FLOAT_EQ(v3.w, 16.7);
    ASSERT_FLOAT_EQ(v4.x, -3.3);
    ASSERT_FLOAT_EQ(v4.y, -5.4);
    ASSERT_FLOAT_EQ(v4.z, -6.6);
    ASSERT_FLOAT_EQ(v4.w, -7.9);
    // dot product
    math::Vector4f v5(1.1,-2.0,0.5,3.0);
    math::Vector4f v6(2.0,1.0,0.8,5.1);
    double dp = v5.dot(v6);
    ASSERT_NEAR(dp, 1.1*2.0 - 2.0*1.0 + 0.5*0.8 + 3.0*5.1, 1e-6);
    ASSERT_NEAR(v5.dot(v6), v6.dot(v5), 1e-6);
}

TEST(Vector4, scalar_operations_internal) {
    math::Vector4d v1(1.1,2.2,3.3,4.4);
    v1 += 1.0;
    ASSERT_NEAR(v1.x, 2.1, 1e-8);
    ASSERT_NEAR(v1.y, 3.2, 1e-8);
    ASSERT_NEAR(v1.z, 4.3, 1e-8);
    ASSERT_NEAR(v1.w, 5.4, 1e-8);
    v1 -= 2.0;
    ASSERT_NEAR(v1.x, 0.1, 1e-8);
    ASSERT_NEAR(v1.y, 1.2, 1e-8);
    ASSERT_NEAR(v1.z, 2.3, 1e-8);
    ASSERT_NEAR(v1.w, 3.4, 1e-8);
    v1 *= 2.0;
    ASSERT_NEAR(v1.x, 0.2, 1e-8);
    ASSERT_NEAR(v1.y, 2.4, 1e-8);
    ASSERT_NEAR(v1.z, 4.6, 1e-8);
    ASSERT_NEAR(v1.w, 6.8, 1e-8);
    v1 /= 2.0;
    ASSERT_NEAR(v1.x, 0.1, 1e-8);
    ASSERT_NEAR(v1.y, 1.2, 1e-8);
    ASSERT_NEAR(v1.z, 2.3, 1e-8);
    ASSERT_NEAR(v1.w, 3.4, 1e-8);
}

TEST(Vector4, scalar_operations_external) {
    math::Vector4d v0(1.1,2.2,3.3,4.4);
    math::Vector4d v1 = v0 + 1.0;
    ASSERT_NEAR(v1.x, 2.1, 1e-8);
    ASSERT_NEAR(v1.y, 3.2, 1e-8);
    ASSERT_NEAR(v1.z, 4.3, 1e-8);
    ASSERT_NEAR(v1.w, 5.4, 1e-8);
    v1 = 11.0 + v0;
    ASSERT_NEAR(v1.x, 12.1, 1e-8);
    ASSERT_NEAR(v1.y, 13.2, 1e-8);
    ASSERT_NEAR(v1.z, 14.3, 1e-8);
    ASSERT_NEAR(v1.w, 15.4, 1e-8);
    v1  = v0 - 1.0;
    ASSERT_NEAR(v1.x, 0.1, 1e-8);
    ASSERT_NEAR(v1.y, 1.2, 1e-8);
    ASSERT_NEAR(v1.z, 2.3, 1e-8);
    ASSERT_NEAR(v1.w, 3.4, 1e-8);
    v1  = 10.0 - v0;
    ASSERT_NEAR(v1.x, 8.9, 1e-8);
    ASSERT_NEAR(v1.y, 7.8, 1e-8);
    ASSERT_NEAR(v1.z, 6.7, 1e-8);
    ASSERT_NEAR(v1.w, 5.6, 1e-8);
    v1 = v0 * 2.0;
    ASSERT_NEAR(v1.x, 2.2, 1e-8);
    ASSERT_NEAR(v1.y, 4.4, 1e-8);
    ASSERT_NEAR(v1.z, 6.6, 1e-8);
    ASSERT_NEAR(v1.w, 8.8, 1e-8);
    v1 = 20.0 * v0;
    ASSERT_NEAR(v1.x, 22.0, 1e-8);
    ASSERT_NEAR(v1.y, 44.0, 1e-8);
    ASSERT_NEAR(v1.z, 66.0, 1e-8);
    ASSERT_NEAR(v1.w, 88.0, 1e-8);
    v1 = v0 / 2.0;
    ASSERT_NEAR(v1.x, 0.55, 1e-8);
    ASSERT_NEAR(v1.y, 1.1, 1e-8);
    ASSERT_NEAR(v1.z, 1.65, 1e-8);
    ASSERT_NEAR(v1.w, 2.2, 1e-8);
}

TEST(Vector4, other_operators) {
    // sign inversion
    math::Vector4d v1(1.1,2.2,3.3,4.4);
    math::Vector4d v2 = -v1;
    ASSERT_DOUBLE_EQ(v2.x, -v1.x);
    ASSERT_DOUBLE_EQ(v2.y, -v1.y);
    ASSERT_DOUBLE_EQ(v2.z, -v1.z);
    ASSERT_DOUBLE_EQ(v2.w, -v1.w);
    // conversion to pointer to array
    const math::Vector4d vconst(6.6,7.7,8.8,9.9);
    const double *p = vconst;
    ASSERT_DOUBLE_EQ(p[0], vconst.x);
    ASSERT_DOUBLE_EQ(p[1], vconst.y);
    ASSERT_DOUBLE_EQ(p[2], vconst.z);
    ASSERT_DOUBLE_EQ(p[3], vconst.w);
    double *vp = v1;
    vp[0] = 3.3;
    vp[1] = 4.4;
    vp[2] = 5.5;
    vp[3] = 6.6;
    ASSERT_DOUBLE_EQ(v1.x, 3.3);
    ASSERT_DOUBLE_EQ(v1.y, 4.4);
    ASSERT_DOUBLE_EQ(v1.z, 5.5);
    ASSERT_DOUBLE_EQ(v1.w, 6.6);
}

TEST(Vector4, comparison) {
    math::Vector4d v1(1.1,2.2,3.3,4.4);
    math::Vector4d v2 = v1;
    math::Vector4d v3a(1.11, 2.2, 3.3, 4.4);
    math::Vector4d v3b(1.1, 2.21, 3.3, 4.4);
    math::Vector4d v3c(1.1, 2.2, 3.31, 4.4);
    math::Vector4d v3d(1.1, 2.2, 3.3, 4.41);
    ASSERT_TRUE(v1 == v2);
    ASSERT_FALSE(v1 != v2);
    ASSERT_FALSE(v1 == v3a);
    ASSERT_TRUE(v1 != v3a);
    ASSERT_FALSE(v1 == v3b);
    ASSERT_TRUE(v1 != v3b);
    ASSERT_FALSE(v1 == v3c);
    ASSERT_TRUE(v1 != v3c);
    ASSERT_FALSE(v1 == v3d);
    ASSERT_TRUE(v1 != v3d);
}


