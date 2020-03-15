#include "vmath.h"

#include <gtest/gtest.h>

#include <cmath>
#include <vector>
#include <numeric>

TEST(Sample, initialization) {
    ASSERT_TRUE(true);
    ASSERT_NEAR(17.0, 17.002, 0.1);
    math::Vector2d v;
    ASSERT_NEAR(0.0, v.x, 0.1);
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
