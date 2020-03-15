#include "vmath_types.h"

#include <gtest/gtest.h>

#include <cmath>
#include <vector>
#include <numeric>

TEST(Sample2, initialization) {
    ASSERT_TRUE(true);
    ASSERT_NEAR(17.0, 17.002, 0.1);
    math::Vector2d v;
    math::Vector3d v2;
    math::Matrix3d m1;
    ASSERT_NEAR(m1(1,1),1,1e-5);
    ASSERT_NEAR(m1(1,2),0,1e-5);
}

