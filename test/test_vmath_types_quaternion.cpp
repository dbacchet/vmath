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

// ////////// //
// Quaternion //
// ////////// //

TEST(Quaternion, constructors) {
    // default constructor
    math::Quatd q1;
    ASSERT_DOUBLE_EQ(q1.w, 1.0);
    ASSERT_DOUBLE_EQ(q1.x, 0.0);
    ASSERT_DOUBLE_EQ(q1.y, 0.0);
    ASSERT_DOUBLE_EQ(q1.z, 0.0);
    // explicit constructor
    math::Quatd q2(2.0, 3.1, 4.2, 5.3);
    ASSERT_DOUBLE_EQ(q2.w, 2.0);
    ASSERT_DOUBLE_EQ(q2.x, 3.1);
    ASSERT_DOUBLE_EQ(q2.y, 4.2);
    ASSERT_DOUBLE_EQ(q2.z, 5.3);
    // copy constructor
    math::Quatd q3(q2);
    ASSERT_DOUBLE_EQ(q3.w, 2.0);
    ASSERT_DOUBLE_EQ(q3.x, 3.1);
    ASSERT_DOUBLE_EQ(q3.y, 4.2);
    ASSERT_DOUBLE_EQ(q3.z, 5.3);
    // from a different qector type or size
    math::Quatf qq1(1,2,3,4);
    math::Quatd q4(qq1);
    ASSERT_DOUBLE_EQ(q4.w, 1.0);
    ASSERT_DOUBLE_EQ(q4.x, 2.0);
    ASSERT_DOUBLE_EQ(q4.y, 3.0);
    ASSERT_DOUBLE_EQ(q4.z, 4.0);
    math::Quatd q5(DummyVec{});
    ASSERT_DOUBLE_EQ(q5.w, 13.1);
    ASSERT_DOUBLE_EQ(q5.x, 10.1);
    ASSERT_DOUBLE_EQ(q5.y, 11.1);
    ASSERT_DOUBLE_EQ(q5.z, 12.1);
}

TEST(Quaternion, assignment) {
    math::Quatf q1;
    math::Quatf q2(13.1,15.2,33.1,55.2);
    q1 = q2;
    ASSERT_FLOAT_EQ(q1.w, q2.w);
    ASSERT_FLOAT_EQ(q1.x, q2.x);
    ASSERT_FLOAT_EQ(q1.y, q2.y);
    ASSERT_FLOAT_EQ(q1.z, q2.z);
    q1 = DummyVec{};
    ASSERT_FLOAT_EQ(q1.w, 13.1);
    ASSERT_FLOAT_EQ(q1.x, 10.1);
    ASSERT_FLOAT_EQ(q1.y, 11.1);
    ASSERT_FLOAT_EQ(q1.z, 12.1);
}

TEST(Quaternion, quat_operations) {
    const math::Quatf q1(1.1,2.2,3.3,4.4);
    const math::Quatf q2(3.3,5.4,6.5,7.6);
    math::Quatf q3 = q1+q2;
    math::Quatf q4 = q1-q2;
    ASSERT_FLOAT_EQ(q3.w, 4.4);
    ASSERT_FLOAT_EQ(q3.x, 7.6);
    ASSERT_FLOAT_EQ(q3.y, 9.8);
    ASSERT_FLOAT_EQ(q3.z, 12.0);
    ASSERT_FLOAT_EQ(q4.w, -2.2);
    ASSERT_FLOAT_EQ(q4.x, -3.2);
    ASSERT_FLOAT_EQ(q4.y, -3.2);
    ASSERT_FLOAT_EQ(q4.z, -3.2);
    q3 += q1;
    q4 -= q1;
    ASSERT_FLOAT_EQ(q3.w, 5.5);
    ASSERT_FLOAT_EQ(q3.x, 9.8);
    ASSERT_FLOAT_EQ(q3.y, 13.1);
    ASSERT_FLOAT_EQ(q3.z, 16.4);
    ASSERT_FLOAT_EQ(q4.w, -3.3);
    ASSERT_FLOAT_EQ(q4.x, -5.4);
    ASSERT_FLOAT_EQ(q4.y, -6.5);
    ASSERT_FLOAT_EQ(q4.z, -7.6);
    const math::Quatd q5(0.5,0.1,0.2,0.3);
    const math::Quatd q6(2,6,5,4);
    math::Quatd q7 = q5*q6;
    ASSERT_FLOAT_EQ(q7.w, -1.8);
    ASSERT_FLOAT_EQ(q7.x, 2.5);
    ASSERT_FLOAT_EQ(q7.y, 4.3);
    ASSERT_FLOAT_EQ(q7.z, 1.9);
}

TEST(Quaternion, scalar_operations_internal) {
    math::Quatd q1(1.1,2.2,3.3,4.4);
    q1 += 1.0;
    ASSERT_NEAR(q1.w, 2.1, 1e-8);
    ASSERT_NEAR(q1.x, 3.2, 1e-8);
    ASSERT_NEAR(q1.y, 4.3, 1e-8);
    ASSERT_NEAR(q1.z, 5.4, 1e-8);
    q1 -= 2.0;
    ASSERT_NEAR(q1.w, 0.1, 1e-8);
    ASSERT_NEAR(q1.x, 1.2, 1e-8);
    ASSERT_NEAR(q1.y, 2.3, 1e-8);
    ASSERT_NEAR(q1.z, 3.4, 1e-8);
    q1 *= 2.0;
    ASSERT_NEAR(q1.w, 0.2, 1e-8);
    ASSERT_NEAR(q1.x, 2.4, 1e-8);
    ASSERT_NEAR(q1.y, 4.6, 1e-8);
    ASSERT_NEAR(q1.z, 6.8, 1e-8);
}

TEST(Quaternion, scalar_operations_external) {
    math::Quatd q0(1.1,2.2,3.3,4.4);
    math::Quatd q1 = q0 + 1.0;
    ASSERT_NEAR(q1.w, 2.1, 1e-8);
    ASSERT_NEAR(q1.x, 3.2, 1e-8);
    ASSERT_NEAR(q1.y, 4.3, 1e-8);
    ASSERT_NEAR(q1.z, 5.4, 1e-8);
    q1 = 11.0 + q0;
    ASSERT_NEAR(q1.w, 12.1, 1e-8);
    ASSERT_NEAR(q1.x, 13.2, 1e-8);
    ASSERT_NEAR(q1.y, 14.3, 1e-8);
    ASSERT_NEAR(q1.z, 15.4, 1e-8);
    q1  = q0 - 1.0;
    ASSERT_NEAR(q1.w, 0.1, 1e-8);
    ASSERT_NEAR(q1.x, 1.2, 1e-8);
    ASSERT_NEAR(q1.y, 2.3, 1e-8);
    ASSERT_NEAR(q1.z, 3.4, 1e-8);
    q1  = 11.0 - q0;
    ASSERT_NEAR(q1.w, 9.9, 1e-8);
    ASSERT_NEAR(q1.x, 8.8, 1e-8);
    ASSERT_NEAR(q1.y, 7.7, 1e-8);
    ASSERT_NEAR(q1.z, 6.6, 1e-8);
    q1 = q0 * 2.0;
    ASSERT_NEAR(q1.w, 2.2, 1e-8);
    ASSERT_NEAR(q1.x, 4.4, 1e-8);
    ASSERT_NEAR(q1.y, 6.6, 1e-8);
    ASSERT_NEAR(q1.z, 8.8, 1e-8);
    q1 = 20.0 * q0;
    ASSERT_NEAR(q1.w, 22.0, 1e-8);
    ASSERT_NEAR(q1.x, 44.0, 1e-8);
    ASSERT_NEAR(q1.y, 66.0, 1e-8);
    ASSERT_NEAR(q1.z, 88.0, 1e-8);
    q1 = q0 / 2.0;
    ASSERT_NEAR(q1.w, 0.55, 1e-8);
    ASSERT_NEAR(q1.x, 1.1, 1e-8);
    ASSERT_NEAR(q1.y, 1.65, 1e-8);
    ASSERT_NEAR(q1.z, 2.2, 1e-8);
}

TEST(Quaternion, other_operators) {
    // sign inversion
    math::Quatd q1(1.1,2.2,3.3,4.4);
    math::Quatd q2 = -q1;
    ASSERT_DOUBLE_EQ(q2.w, -q1.w);
    ASSERT_DOUBLE_EQ(q2.x, -q1.x);
    ASSERT_DOUBLE_EQ(q2.y, -q1.y);
    ASSERT_DOUBLE_EQ(q2.z, -q1.z);
    // conjugate
    q2 = ~q1;
    ASSERT_DOUBLE_EQ(q2.w, q1.w);
    ASSERT_DOUBLE_EQ(q2.x, -q1.x);
    ASSERT_DOUBLE_EQ(q2.y, -q1.y);
    ASSERT_DOUBLE_EQ(q2.z, -q1.z);
}

TEST(Quaternion, comparison) {
    math::Quatd q1(1.1,2.2,3.3,4.4);
    math::Quatd q2 = q1;
    math::Quatd q3a(1.11,2.2,3.3,4.4);
    math::Quatd q3b(1.1,2.21,3.3,4.4);
    math::Quatd q3c(1.1,2.2,3.31,4.4);
    math::Quatd q3d(1.1,2.2,3.3,4.41);
    ASSERT_TRUE(q1 == q2);
    ASSERT_FALSE(q1 != q2);
    ASSERT_FALSE(q1 == q3a);
    ASSERT_TRUE(q1 != q3a);
    ASSERT_FALSE(q1 == q3b);
    ASSERT_TRUE(q1 != q3b);
    ASSERT_FALSE(q1 == q3c);
    ASSERT_TRUE(q1 != q3c);
    ASSERT_FALSE(q1 == q3d);
    ASSERT_TRUE(q1 != q3d);
}


TEST(Quaternion, vector_operators) {
    math::Quatd q1(0.5,0.1,0.2,0.3);
    // vector3
    math::Vector3d v1(6,5,4);
    math::Vector3d v2 = q1*v1;
    ASSERT_DOUBLE_EQ(v2.x, 0.52);
    ASSERT_DOUBLE_EQ(v2.y, 3.07);
    ASSERT_DOUBLE_EQ(v2.z, 1.42);
    // vector4
    math::Vector4d v3(6,5,4,2.34);
    math::Vector4d v4 = q1*v3;
    ASSERT_DOUBLE_EQ(v4.x, 0.52);
    ASSERT_DOUBLE_EQ(v4.y, 3.07);
    ASSERT_DOUBLE_EQ(v4.z, 1.42);
    ASSERT_DOUBLE_EQ(v4.w, 2.34);
}

