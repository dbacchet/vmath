#include "vmath_types.h"

#include <gtest/gtest.h>

#include <cmath>
#include <vector>
#include <numeric>

namespace {
struct DummyVec {
    double x = 10.1;
    double y = 11.1;
    double z = 12.1;
    double w = 13.1;
};
} // namespace

// /////// //
// Vector2 //
// /////// //

TEST(Vector2, constructors) {
    // default constructor
    math::Vector2d v1;
    ASSERT_DOUBLE_EQ(v1.x, 0.0);
    ASSERT_DOUBLE_EQ(v1.y, 0.0);
    // explicit constructor
    math::Vector2d v2(3.1, 4.2);
    ASSERT_DOUBLE_EQ(v2.x, 3.1);
    ASSERT_DOUBLE_EQ(v2.y, 4.2);
    // copy constructor
    math::Vector2d v3(v2);
    ASSERT_DOUBLE_EQ(v3.x, 3.1);
    ASSERT_DOUBLE_EQ(v3.y, 4.2);
    // from a different vector type or size
    math::Vector2i vv1(6, 7);
    math::Vector2d v4(vv1);
    ASSERT_DOUBLE_EQ(v4.x, 6.0);
    ASSERT_DOUBLE_EQ(v4.y, 7.0);
    math::Vector2d v5(DummyVec{});
    ASSERT_DOUBLE_EQ(v5.x, 10.1);
    ASSERT_DOUBLE_EQ(v5.y, 11.1);
}

TEST(Vector2, assignment) {
    math::Vector2f v1;
    math::Vector2f v2(13.1,15.2);
    v1 = v2;
    ASSERT_DOUBLE_EQ(v1.x, v2.x);
    ASSERT_DOUBLE_EQ(v1.y, v2.y);
}

TEST(Vector2, access) {
    const math::Vector2f v1(11.1,22.2);
    double x = v1[0];
    double y = v1[1];
    ASSERT_FLOAT_EQ(x, 11.1);
    ASSERT_FLOAT_EQ(y, 22.2);
    math::Vector2f v2(13.1,15.2);
    v2[0] = 4.1;
    v2[1] = 4.2;
    ASSERT_FLOAT_EQ(v2.x, 4.1);
    ASSERT_FLOAT_EQ(v2.y, 4.2);
}

TEST(Vector2, vector_operations_internal) {
    const math::Vector2f v1(1.1,2.2);
    const math::Vector2f v2(3.3,5.4);
    math::Vector2f v3 = v1+v2;
    math::Vector2f v4 = v1-v2;
    ASSERT_FLOAT_EQ(v3.x, 4.4);
    ASSERT_FLOAT_EQ(v3.y, 7.6);
    ASSERT_FLOAT_EQ(v4.x, -2.2);
    ASSERT_FLOAT_EQ(v4.y, -3.2);
    v3 += v1;
    v4 -= v1;
    ASSERT_FLOAT_EQ(v3.x, 5.5);
    ASSERT_FLOAT_EQ(v3.y, 9.8);
    ASSERT_FLOAT_EQ(v4.x, -3.3);
    ASSERT_FLOAT_EQ(v4.y, -5.4);
    // dot product
    math::Vector2f v5(1.1,-2.0);
    math::Vector2f v6(2.0,1.0);
    double cp = v5.dot(v6);
    ASSERT_NEAR(cp, 1.1*2.0 - 2.0*1.0, 1e-6);
    ASSERT_NEAR(v5.dot(v6), v6.dot(v5), 1e-6);
}

TEST(Vector2, scalar_operations_internal) {
    math::Vector2d v1(1.1,2.2);
    v1 += 1.0;
    ASSERT_NEAR(v1.x, 2.1, 1e-8);
    ASSERT_NEAR(v1.y, 3.2, 1e-8);
    v1 -= 2.0;
    ASSERT_NEAR(v1.x, 0.1, 1e-8);
    ASSERT_NEAR(v1.y, 1.2, 1e-8);
    v1 *= 2.0;
    ASSERT_NEAR(v1.x, 0.2, 1e-8);
    ASSERT_NEAR(v1.y, 2.4, 1e-8);
    v1 /= 2.0;
    ASSERT_NEAR(v1.x, 0.1, 1e-8);
    ASSERT_NEAR(v1.y, 1.2, 1e-8);
}

TEST(Vector2, scalar_operations_external) {
    math::Vector2d v0(1.1,2.2);
    math::Vector2d v1 = v0 + 1.0;
    ASSERT_NEAR(v1.x, 2.1, 1e-8);
    ASSERT_NEAR(v1.y, 3.2, 1e-8);
    v1 = 11.0 + v0;
    ASSERT_NEAR(v1.x, 12.1, 1e-8);
    ASSERT_NEAR(v1.y, 13.2, 1e-8);
    v1  = v0 - 1.0;
    ASSERT_NEAR(v1.x, 0.1, 1e-8);
    ASSERT_NEAR(v1.y, 1.2, 1e-8);
    v1  = 11.0 - v0;
    ASSERT_NEAR(v1.x, 9.9, 1e-8);
    ASSERT_NEAR(v1.y, 8.8, 1e-8);
    v1 = v0 * 2.0;
    ASSERT_NEAR(v1.x, 2.2, 1e-8);
    ASSERT_NEAR(v1.y, 4.4, 1e-8);
    v1 = 20.0 * v0;
    ASSERT_NEAR(v1.x, 22.0, 1e-8);
    ASSERT_NEAR(v1.y, 44.0, 1e-8);
    v1 = v0 / 2.0;
    ASSERT_NEAR(v1.x, 0.55, 1e-8);
    ASSERT_NEAR(v1.y, 1.1, 1e-8);
}

TEST(Vector2, other_operators) {
    // sign inversion
    math::Vector2d v1(1.1,2.2);
    math::Vector2d v2 = -v1;
    ASSERT_DOUBLE_EQ(v2.x, -v1.x);
    ASSERT_DOUBLE_EQ(v2.y, -v1.y);
    // conversion to pointer to array
    const math::Vector2d vconst(6.6,7.7);
    const double *p = vconst;
    ASSERT_DOUBLE_EQ(p[0], vconst.x);
    ASSERT_DOUBLE_EQ(p[1], vconst.y);
    double *vp = v1;
    vp[0] = 3.3;
    vp[1] = 4.4;
    ASSERT_DOUBLE_EQ(v1.x, 3.3);
    ASSERT_DOUBLE_EQ(v1.y, 4.4);
}

TEST(Vector2, comparison) {
    math::Vector2d v1(1.1,2.2);
    math::Vector2d v2 = v1;
    math::Vector2d v3(1.11, 2.2);
    ASSERT_TRUE(v1 == v2);
    ASSERT_FALSE(v1 != v2);
    ASSERT_FALSE(v1 == v3);
    ASSERT_TRUE(v1 != v3);
}

