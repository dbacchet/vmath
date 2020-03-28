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

template <typename T>
void print_matrix(const math::Matrix4<T> &m) {
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            printf("%9.7f ", (double)m(i,j));
        }
        printf("\n");
    }
}
} // namespace

// /////// //
// Vector2 //
// /////// //

TEST(Functions, vector2) {
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

TEST(Functions, vector3) {
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

TEST(Functions, vector4) {
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

TEST(Functions, matrix3) {
    math::Matrix3d m1 {1,2,3,
                       4,5,6,
                       7,8,9};
    math::transpose(m1);
    ASSERT_EQ(m1, math::Matrix3d({1,4,7,
                                  2,5,8,
                                  3,6,9}));
    math::set_identity(m1);
    ASSERT_EQ(m1, math::Matrix3d({1,0,0,
                                  0,1,0,
                                  0,0,1}));
    math::set_zero(m1);
    ASSERT_EQ(m1, math::Matrix3d({0,0,0,
                                  0,0,0,
                                  0,0,0}));
    math::Matrix3d m2 {1,2,3,
                       4,5,6,
                       7,8,9};
    math::Matrix3d m3 {11,12,13,
                       14,15,16,
                       17,18,19};
    ASSERT_EQ(lerp(m2,m3,0.0), m2);
    ASSERT_EQ(lerp(m2,m3,1.0), m3);
    ASSERT_EQ(lerp(m2,m3,0.5), (m2+m3)/2.0);
    math::Matrix3d m4 {1,2,3,
                       6,5,4,
                       3,8,5};
    ASSERT_DOUBLE_EQ(det(m4), 56.0);
    ASSERT_EQ(inverse(m4), math::Matrix3d({-0.125,     0.25,     -0.125,
                                           -0.321429, -0.071429,  0.25,
                                            0.589286, -0.035714, -0.125}));
    // inverse for singular matrix
    ASSERT_EQ(inverse(m2), math::Matrix3d({0, 0, 0,
                                           0, 0, 0,
                                           0, 0, 0}));
}

TEST(Functions, matrix4) {
    math::Matrix4d m1 {1,2,3,4,
                       5,6,7,8,
                       9,4,5,6,
                       4,7,8,9};
    math::transpose(m1);
    ASSERT_EQ(m1, math::Matrix4d({1,5,9,4,
                                  2,6,4,7,
                                  3,7,5,8,
                                  4,8,6,9}));
    math::set_identity(m1);
    ASSERT_EQ(m1, math::Matrix4d({1,0,0,0,
                                  0,1,0,0,
                                  0,0,1,0,
                                  0,0,0,1}));
    math::set_zero(m1);
    ASSERT_EQ(m1, math::Matrix4d({0,0,0,0,
                                  0,0,0,0,
                                  0,0,0,0,
                                  0,0,0,0}));
    math::set_translation(m1, math::Vector3d(11,12,13));
    ASSERT_EQ(m1, math::Matrix4d({0,0,0,11,
                                  0,0,0,12,
                                  0,0,0,13,
                                  0,0,0,1}));
    ASSERT_EQ(math::translation(m1), math::Vector3d(11,12,13));
    math::set_rotation(m1, math::Matrix3d({1,2,3,
                                           4,5,6,
                                           7,8,9}));
    ASSERT_EQ(m1, math::Matrix4d({1,2,3,11,
                                  4,5,6,12,
                                  7,8,9,13,
                                  0,0,0,1}));
    math::Matrix4d m2 {1,2,3,4,
                       5,6,7,8,
                       9,4,5,6,
                       4,7,8,9};
    math::Matrix4d m3 {11,12,13,14,
                       15,16,17,18,
                       19,14,15,16,
                       14,17,18,19};
    ASSERT_EQ(lerp(m2,m3,0.0), m2);
    ASSERT_EQ(lerp(m2,m3,1.0), m3);
    ASSERT_EQ(lerp(m2,m3,0.5), (m2+m3)/2.0);
    math::Matrix4d m4 {1,2,3,4,
                       8,6,7,1,
                       9,4,5,1,
                       4,7,8,9};
    ASSERT_DOUBLE_EQ(det(m4), -123.0);
    ASSERT_EQ(inverse(m4), math::Matrix4d({-1.30081301e-01,-2.03252033e-01, 2.84552846e-01, 4.87804878e-02,
                                           -1.55284553e+00,-1.13821138e-01,-4.06504065e-02, 7.07317073e-01,
                                            1.48780488e+00, 5.12195122e-01,-3.17073171e-01,-6.82926829e-01,
                                           -5.69105691e-02,-2.76422764e-01, 1.86991870e-01, 1.46341463e-01}));
    // inverse for singular matrix
    ASSERT_EQ(inverse(m2), math::Matrix4d({0,0,0,0,
                                           0,0,0,0,
                                           0,0,0,0,
                                           0,0,0,0}));
}

