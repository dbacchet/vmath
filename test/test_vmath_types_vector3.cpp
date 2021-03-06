#include "vmath_types.h"

#include <gtest/gtest.h>

#include <cmath>
#include <vector>
#include <numeric>


// /////// //
// Vector3 //
// /////// //

TEST(Vector3, constructors) {
    // default constructor
    math::Vector3d v1;
    ASSERT_DOUBLE_EQ(v1.x, 0.0);
    ASSERT_DOUBLE_EQ(v1.y, 0.0);
    ASSERT_DOUBLE_EQ(v1.z, 0.0);
    // explicit constructor
    math::Vector3d v2(3.1, 4.2, 5.3);
    ASSERT_DOUBLE_EQ(v2.x, 3.1);
    ASSERT_DOUBLE_EQ(v2.y, 4.2);
    ASSERT_DOUBLE_EQ(v2.z, 5.3);
    // copy constructor
    math::Vector3d v3(v2);
    ASSERT_DOUBLE_EQ(v3.x, 3.1);
    ASSERT_DOUBLE_EQ(v3.y, 4.2);
    ASSERT_DOUBLE_EQ(v3.z, 5.3);
    // from a different vector type or size
    math::Vector3i vv1(6, 7, 8);
    math::Vector3d v4(vv1);
    ASSERT_DOUBLE_EQ(v4.x, 6.0);
    ASSERT_DOUBLE_EQ(v4.y, 7.0);
    ASSERT_DOUBLE_EQ(v4.z, 8.0);
    math::Vector3i v5(math::Vector3d(13.2, 14.5, 15.8));
    ASSERT_EQ(v5.x, 13);
    ASSERT_EQ(v5.y, 14);
    ASSERT_EQ(v5.z, 15);
}

TEST(Vector3, assignment) {
    math::Vector3f v1;
    math::Vector3f v2(13.1,15.2,16.3);
    v1 = v2;
    ASSERT_DOUBLE_EQ(v1.x, v2.x);
    ASSERT_DOUBLE_EQ(v1.y, v2.y);
    ASSERT_DOUBLE_EQ(v1.z, v2.z);
}

TEST(Vector3, access) {
    const math::Vector3f v1(11.1,22.2,33.3);
    double x = v1[0];
    double y = v1[1];
    double z = v1[2];
    ASSERT_FLOAT_EQ(x, 11.1);
    ASSERT_FLOAT_EQ(y, 22.2);
    ASSERT_FLOAT_EQ(z, 33.3);
    math::Vector3f v2(13.1,15.2,17.3);
    v2[0] = 4.1;
    v2[1] = 4.2;
    v2[2] = 4.3;
    ASSERT_FLOAT_EQ(v2.x, 4.1);
    ASSERT_FLOAT_EQ(v2.y, 4.2);
    ASSERT_FLOAT_EQ(v2.z, 4.3);
}

TEST(Vector3, vector_operations_internal) {
    const math::Vector3f v1(1.1,2.2,3.3);
    const math::Vector3f v2(3.3,5.4,6.6);
    math::Vector3f v3 = v1+v2;
    math::Vector3f v4 = v1-v2;
    ASSERT_FLOAT_EQ(v3.x, 4.4);
    ASSERT_FLOAT_EQ(v3.y, 7.6);
    ASSERT_FLOAT_EQ(v3.z, 9.9);
    ASSERT_FLOAT_EQ(v4.x, -2.2);
    ASSERT_FLOAT_EQ(v4.y, -3.2);
    ASSERT_FLOAT_EQ(v4.z, -3.3);
    v3 += v1;
    v4 -= v1;
    ASSERT_FLOAT_EQ(v3.x, 5.5);
    ASSERT_FLOAT_EQ(v3.y, 9.8);
    ASSERT_FLOAT_EQ(v3.z, 13.2);
    ASSERT_FLOAT_EQ(v4.x, -3.3);
    ASSERT_FLOAT_EQ(v4.y, -5.4);
    ASSERT_FLOAT_EQ(v4.z, -6.6);
    // dot product
    math::Vector3f v5(1.1,-2.0,0.5);
    math::Vector3f v6(2.0,1.0,0.8);
    double dp = v5.dot(v6);
    ASSERT_NEAR(dp, 1.1*2.0 - 2.0*1.0 + 0.5*0.8, 1e-6);
    ASSERT_NEAR(v5.dot(v6), v6.dot(v5), 1e-6);
    // cross product
    math::Vector3i vc1(1,2,3);
    math::Vector3i vc2(4,2,7);
    math::Vector3i cp = vc1.cross(vc2);
    ASSERT_EQ(cp.x, 8);
    ASSERT_EQ(cp.y, 5);
    ASSERT_EQ(cp.z, -6);
    math::Vector3i cpi = vc2.cross(vc1);
    ASSERT_TRUE(cpi == -cp);
    math::Vector3d vc3(1.1,0,0);
    math::Vector3d vc4(0,2.2,0);
    math::Vector3d cp2 = vc3.cross(vc4);
    ASSERT_DOUBLE_EQ(cp2.x, 0);
    ASSERT_DOUBLE_EQ(cp2.y, 0);
    ASSERT_DOUBLE_EQ(cp2.z, 2.42);
}

TEST(Vector3, scalar_operations_internal) {
    math::Vector3d v1(1.1,2.2,3.3);
    v1 += 1.0;
    ASSERT_NEAR(v1.x, 2.1, 1e-8);
    ASSERT_NEAR(v1.y, 3.2, 1e-8);
    ASSERT_NEAR(v1.z, 4.3, 1e-8);
    v1 -= 2.0;
    ASSERT_NEAR(v1.x, 0.1, 1e-8);
    ASSERT_NEAR(v1.y, 1.2, 1e-8);
    ASSERT_NEAR(v1.z, 2.3, 1e-8);
    v1 *= 2.0;
    ASSERT_NEAR(v1.x, 0.2, 1e-8);
    ASSERT_NEAR(v1.y, 2.4, 1e-8);
    ASSERT_NEAR(v1.z, 4.6, 1e-8);
    v1 /= 2.0;
    ASSERT_NEAR(v1.x, 0.1, 1e-8);
    ASSERT_NEAR(v1.y, 1.2, 1e-8);
    ASSERT_NEAR(v1.z, 2.3, 1e-8);
}

TEST(Vector3, scalar_operations_external) {
    math::Vector3d v0(1.1,2.2,3.3);
    math::Vector3d v1 = v0 + 1.0;
    ASSERT_NEAR(v1.x, 2.1, 1e-8);
    ASSERT_NEAR(v1.y, 3.2, 1e-8);
    ASSERT_NEAR(v1.z, 4.3, 1e-8);
    v1 = 11.0 + v0;
    ASSERT_NEAR(v1.x, 12.1, 1e-8);
    ASSERT_NEAR(v1.y, 13.2, 1e-8);
    ASSERT_NEAR(v1.z, 14.3, 1e-8);
    v1  = v0 - 1.0;
    ASSERT_NEAR(v1.x, 0.1, 1e-8);
    ASSERT_NEAR(v1.y, 1.2, 1e-8);
    ASSERT_NEAR(v1.z, 2.3, 1e-8);
    v1  = 10.0 - v0;
    ASSERT_NEAR(v1.x, 8.9, 1e-8);
    ASSERT_NEAR(v1.y, 7.8, 1e-8);
    ASSERT_NEAR(v1.z, 6.7, 1e-8);
    v1 = v0 * 2.0;
    ASSERT_NEAR(v1.x, 2.2, 1e-8);
    ASSERT_NEAR(v1.y, 4.4, 1e-8);
    ASSERT_NEAR(v1.z, 6.6, 1e-8);
    v1 = 20.0 * v0;
    ASSERT_NEAR(v1.x, 22.0, 1e-8);
    ASSERT_NEAR(v1.y, 44.0, 1e-8);
    ASSERT_NEAR(v1.z, 66.0, 1e-8);
    v1 = v0 / 2.0;
    ASSERT_NEAR(v1.x, 0.55, 1e-8);
    ASSERT_NEAR(v1.y, 1.1, 1e-8);
    ASSERT_NEAR(v1.z, 1.65, 1e-8);
}

TEST(Vector3, other_operators) {
    // sign inversion
    math::Vector3d v1(1.1,2.2,3.3);
    math::Vector3d v2 = -v1;
    ASSERT_DOUBLE_EQ(v2.x, -v1.x);
    ASSERT_DOUBLE_EQ(v2.y, -v1.y);
    ASSERT_DOUBLE_EQ(v2.z, -v1.z);
    // conversion to pointer to array
    const math::Vector3d vconst(6.6,7.7,8.8);
    const double *p = vconst;
    ASSERT_DOUBLE_EQ(p[0], vconst.x);
    ASSERT_DOUBLE_EQ(p[1], vconst.y);
    ASSERT_DOUBLE_EQ(p[2], vconst.z);
    double *vp = v1;
    vp[0] = 3.3;
    vp[1] = 4.4;
    vp[2] = 5.5;
    ASSERT_DOUBLE_EQ(v1.x, 3.3);
    ASSERT_DOUBLE_EQ(v1.y, 4.4);
    ASSERT_DOUBLE_EQ(v1.z, 5.5);
}

TEST(Vector3, comparison) {
    math::Vector3d v1(1.1,2.2,3.3);
    math::Vector3d v2 = v1;
    math::Vector3d v3a(1.11, 2.2, 3.3);
    math::Vector3d v3b(1.1, 2.21, 3.3);
    math::Vector3d v3c(1.1, 2.2, 3.31);
    ASSERT_TRUE(v1 == v2);
    ASSERT_FALSE(v1 != v2);
    ASSERT_FALSE(v1 == v3a);
    ASSERT_TRUE(v1 != v3a);
    ASSERT_FALSE(v1 == v3b);
    ASSERT_TRUE(v1 != v3b);
    ASSERT_FALSE(v1 == v3c);
    ASSERT_TRUE(v1 != v3c);
}



