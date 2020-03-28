#include "vmath.h"

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

TEST(FunVector2, constructors) {
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


