#include "vmath.h"

#include <gtest/gtest.h>

#include <cmath>
#include <type_traits>
#include <vector>
#include <numeric>

TEST(Sample, initialization) {
    ASSERT_TRUE(true);
    ASSERT_NEAR(17.0, 17.002, 0.1);
    math::Vector2d v;
    ASSERT_NEAR(0.0, v.x, 0.1);
}

// The core types are plain aggregates and must stay trivially copyable so they
// can be memcpy'd, stored in POD buffers and passed to graphics APIs cheaply.
template <typename T> void assert_trivially_copyable() {
    static_assert(std::is_trivially_copyable<T>::value, "type must be trivially copyable");
    static_assert(std::is_standard_layout<T>::value, "type must be standard layout");
}

TEST(Types, trivially_copyable_and_standard_layout) {
    assert_trivially_copyable<math::Vector2f>();
    assert_trivially_copyable<math::Vector3f>();
    assert_trivially_copyable<math::Vector4f>();
    assert_trivially_copyable<math::Vector2d>();
    assert_trivially_copyable<math::Vector3d>();
    assert_trivially_copyable<math::Vector4d>();
    assert_trivially_copyable<math::Matrix3f>();
    assert_trivially_copyable<math::Matrix4f>();
    assert_trivially_copyable<math::Matrix3d>();
    assert_trivially_copyable<math::Matrix4d>();
    assert_trivially_copyable<math::Quatf>();
    assert_trivially_copyable<math::Quatd>();
    assert_trivially_copyable<math::Transff>();
    assert_trivially_copyable<math::Transfd>();
    SUCCEED();
}

// The ptr() accessor exposes the components as a contiguous array, replacing the
// old implicit `operator T*()`.
TEST(Types, ptr_accessor) {
    math::Vector3d v(1.0, 2.0, 3.0);
    double *p = v.ptr();
    ASSERT_DOUBLE_EQ(p[0], 1.0);
    ASSERT_DOUBLE_EQ(p[1], 2.0);
    ASSERT_DOUBLE_EQ(p[2], 3.0);
    p[1] = 9.0;
    ASSERT_DOUBLE_EQ(v.y, 9.0);

    const math::Matrix4f m = math::matrix4_identity<float>();
    const float *mp = m.ptr();
    ASSERT_FLOAT_EQ(mp[0], 1.0f);
    ASSERT_FLOAT_EQ(mp[5], 1.0f);
}

// namespace ciccio {
//
// void my_test() {
//     math::Vector2d v2;
//     v2.x = 10.0;
//     v2.y = 11.4;
// }
//
// } // namespace ciccio
