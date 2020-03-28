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

TEST(Fununctions, vector2) {
    math::Vector2d v1(3,4);
    ASSERT_DOUBLE_EQ(length(v1), 5.0);
    ASSERT_DOUBLE_EQ(length2(v1), 25.0);
    // normalization
    math::Vector2d v2 = normalized(v1);
    ASSERT_DOUBLE_EQ(v2.x, 3.0/5.0);
    ASSERT_DOUBLE_EQ(v2.y, 4.0/5.0);
    normalize(v1);
    ASSERT_DOUBLE_EQ(v1.x, v2.x);
    ASSERT_DOUBLE_EQ(v1.y, v2.y);
    // lerp
    math::Vector2d v3(1,2);
    math::Vector2d v4(2,4);
    ASSERT_EQ(lerp(v3,v4,0.0), v3);
    ASSERT_EQ(lerp(v3,v4,1.0), v4);
    ASSERT_EQ(lerp(v3,v4,0.5), (v3+v4)/2.0);
}

TEST(Fununctions, vector3) {
    math::Vector3d v1(3,4,5);
    double l2 = v1.x*v1.x + v1.y*v1.y + v1.z*v1.z;
    double l = std::sqrt(l2);
    ASSERT_DOUBLE_EQ(length(v1), l);
    ASSERT_DOUBLE_EQ(length2(v1), l2);
    // normalization
    math::Vector3d v2 = normalized(v1);
    ASSERT_DOUBLE_EQ(v2.x, 3.0/l);
    ASSERT_DOUBLE_EQ(v2.y, 4.0/l);
    ASSERT_DOUBLE_EQ(v2.z, 5.0/l);
    normalize(v1);
    ASSERT_DOUBLE_EQ(v1.x, v2.x);
    ASSERT_DOUBLE_EQ(v1.y, v2.y);
    ASSERT_DOUBLE_EQ(v1.z, v2.z);
    // lerp
    math::Vector3d v3(1,2,3);
    math::Vector3d v4(2,4,6);
    ASSERT_EQ(lerp(v3,v4,0.0), v3);
    ASSERT_EQ(lerp(v3,v4,1.0), v4);
    ASSERT_EQ(lerp(v3,v4,0.5), (v3+v4)/2.0);
}

TEST(Fununctions, vector4) {
    math::Vector4f v1(3,4,5,6);
    float l2 = v1.x*v1.x + v1.y*v1.y + v1.z*v1.z + v1.w*v1.w;
    float l = std::sqrt(l2);
    ASSERT_FLOAT_EQ(length(v1), l);
    ASSERT_FLOAT_EQ(length2(v1), l2);
    // normalization
    math::Vector4f v2 = normalized(v1);
    ASSERT_FLOAT_EQ(v2.x, 3.0/l);
    ASSERT_FLOAT_EQ(v2.y, 4.0/l);
    ASSERT_FLOAT_EQ(v2.z, 5.0/l);
    ASSERT_FLOAT_EQ(v2.w, 6.0/l);
    normalize(v1);
    ASSERT_FLOAT_EQ(v1.x, v2.x);
    ASSERT_FLOAT_EQ(v1.y, v2.y);
    ASSERT_FLOAT_EQ(v1.z, v2.z);
    ASSERT_FLOAT_EQ(v1.w, v2.w);
    // lerp
    math::Vector4f v3(1,2,3,4);
    math::Vector4f v4(2,4,6,8);
    ASSERT_EQ(lerp(v3,v4,0.0f), v3);
    ASSERT_EQ(lerp(v3,v4,1.0f), v4);
    ASSERT_EQ(lerp(v3,v4,0.5f), (v3+v4)/2.0f);
}

