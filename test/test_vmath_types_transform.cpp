#include "vmath_types.h"
#include "vmath.h"

#include <gtest/gtest.h>

#include <cmath>
#include <vector>
#include <numeric>
#include <cstdio>

template <typename T>
void print_tf(const T &tf) {
    printf("p: {%f, %f, %f}\n", tf.p.x, tf.p.y, tf.p.z);
    printf("q: {%f, %f, %f, %f}\n", tf.q.w, tf.q.x, tf.q.y, tf.q.z);
}

// ///////// //
// Transform //
// ///////// //

TEST(Transform, constructors) {
    // default constructor
    math::Transfd t1;
    ASSERT_DOUBLE_EQ(t1.p.x, 0.0);
    ASSERT_DOUBLE_EQ(t1.p.y, 0.0);
    ASSERT_DOUBLE_EQ(t1.p.z, 0.0);
    ASSERT_DOUBLE_EQ(t1.q.w, 1.0);
    ASSERT_DOUBLE_EQ(t1.q.x, 0.0);
    ASSERT_DOUBLE_EQ(t1.q.y, 0.0);
    ASSERT_DOUBLE_EQ(t1.q.z, 0.0);
    // explicit constructors
    math::Transfd t2(math::Vector3d{1.0,2.0,3.0});
    ASSERT_DOUBLE_EQ(t2.p.x, 1.0);
    ASSERT_DOUBLE_EQ(t2.p.y, 2.0);
    ASSERT_DOUBLE_EQ(t2.p.z, 3.0);
    ASSERT_DOUBLE_EQ(t2.q.w, 1.0);
    ASSERT_DOUBLE_EQ(t2.q.x, 0.0);
    ASSERT_DOUBLE_EQ(t2.q.y, 0.0);
    ASSERT_DOUBLE_EQ(t2.q.z, 0.0);
    math::Transfd t3(math::Quatd{1.0,0.1,0.2,0.3});
    ASSERT_DOUBLE_EQ(t3.p.x, 0.0);
    ASSERT_DOUBLE_EQ(t3.p.y, 0.0);
    ASSERT_DOUBLE_EQ(t3.p.z, 0.0);
    ASSERT_DOUBLE_EQ(t3.q.w, 1.0);
    ASSERT_DOUBLE_EQ(t3.q.x, 0.1);
    ASSERT_DOUBLE_EQ(t3.q.y, 0.2);
    ASSERT_DOUBLE_EQ(t3.q.z, 0.3);
    math::Transfd t4(math::Vector3d{1.0,2.0,3.0}, math::Quatd{1.0,0.1,0.2,0.3});
    ASSERT_DOUBLE_EQ(t4.p.x, 1.0);
    ASSERT_DOUBLE_EQ(t4.p.y, 2.0);
    ASSERT_DOUBLE_EQ(t4.p.z, 3.0);
    ASSERT_DOUBLE_EQ(t4.q.w, 1.0);
    ASSERT_DOUBLE_EQ(t4.q.x, 0.1);
    ASSERT_DOUBLE_EQ(t4.q.y, 0.2);
    ASSERT_DOUBLE_EQ(t4.q.z, 0.3);
}

TEST(Transform, assignment_comp) {
    math::Transfd t(math::Vector3d{1.0,2.0,3.0}, math::Quatd{1.0,0.1,0.2,0.3});
    math::Transfd t1;
    t1 = t;
    ASSERT_DOUBLE_EQ(t1.p.x, 1.0);
    ASSERT_DOUBLE_EQ(t1.p.y, 2.0);
    ASSERT_DOUBLE_EQ(t1.p.z, 3.0);
    ASSERT_DOUBLE_EQ(t1.q.w, 1.0);
    ASSERT_DOUBLE_EQ(t1.q.x, 0.1);
    ASSERT_DOUBLE_EQ(t1.q.y, 0.2);
    ASSERT_DOUBLE_EQ(t1.q.z, 0.3);
    // comparison
    ASSERT_TRUE(t1 == t);
    t1.p.x +=0.01;
    ASSERT_FALSE(t1 == t);
}

TEST(Transform, operators) {
    math::Transfd t1(math::Vector3d{1.0,2.0,3.0}, math::quat_from_euler_321(0.0,0.0,M_PI/2));
    math::Transfd t2(math::Vector3d{4.0,5.0,6.0}, math::quat_from_euler_321(0.0,0.0,M_PI/2));
    math::Transfd t = t1*t2;
    math::Transfd res(math::Vector3d(-4,6,9), math::quat_from_euler_321(0.0,0.0,M_PI));
    ASSERT_EQ(t, res);
    t1 *= t2;
    ASSERT_EQ(t1, res);
    // chain transforms
    math::Transfd t4(math::quat_from_euler_321(0.0,0.0,M_PI/2));
    math::Transfd t5(math::quat_from_euler_321(0.0,0.0,M_PI/2));
    math::Transfd t6(math::Vector3d{1.0,2.0,3.0});
    math::Transfd tcomp = t6*t5*t4;
    ASSERT_EQ(tcomp, math::Transfd(math::Vector3d{1,2,3}, math::quat_from_euler_321(0.0,0.0,M_PI)));
}

TEST(Transform, operations) {
    math::Transfd t(math::Vector3d{1.0,2.0,3.0}, math::quat_from_euler_321(0.0,0.0,M_PI/2));
    // inverse
    math::Transfd ti = t.inverse();
    ASSERT_DOUBLE_EQ(ti.p.x, -2.0);
    ASSERT_DOUBLE_EQ(ti.p.y, 1.0);
    ASSERT_DOUBLE_EQ(ti.p.z, -3.0);
    ASSERT_EQ(ti.q, math::quat_from_euler_321(0.0,0.0,-M_PI/2));
    auto t_identity = t * ti;
    ASSERT_NEAR(t_identity.p.x, 0.0, 1e-6);
    ASSERT_NEAR(t_identity.p.y, 0.0, 1e-6);
    ASSERT_NEAR(t_identity.p.z, 0.0, 1e-6);
    ASSERT_NEAR(t_identity.q.w, 1.0, 1e-6);
    ASSERT_NEAR(t_identity.q.x, 0.0, 1e-6);
    ASSERT_NEAR(t_identity.q.y, 0.0, 1e-6);
    ASSERT_NEAR(t_identity.q.z, 0.0, 1e-6);
    // transform
    math::Vector3d p = {5.0,1.0,2.0};
    math::Vector3d pt = t.transform(p);
    ASSERT_EQ(pt, math::Vector3d(0,7,5));
    // transform with the inverse
    pt = t.inv_transform(p);
    ASSERT_EQ(pt, ti.transform(p));
    // rotate
    pt = t.rotate(p);
    ASSERT_EQ(pt, math::Vector3d(-1,5,2));
    // rotate with the inverse
    pt = t.inv_rotate(p);
    ASSERT_EQ(pt, ti.rotate(p));
}
