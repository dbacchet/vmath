#include "vmath_types.h"

#include <gtest/gtest.h>

#include <cmath>
#include <array>
#include <vector>
#include <numeric>
#include <limits>

namespace {

// predicates used in the tests
template <typename T> 
bool matrix_array_equal(const math::Matrix4<T> &m1, const T *m2) {
    bool is_equal = true;
    for (uint8_t i=0; i<4; i++) {
        for (uint8_t j=0; j<4; j++) {
            // array is row-major, but internal dat is col-major
            is_equal = is_equal && (std::abs(m1.data[j*4+i] - m2[i*4+j])<=1e-5); // reasonable value for 'float' that is the type with the biggest approx error        }
        }
    }
    return is_equal;
}
template <typename T> 
bool matrix_matrix_equal(const math::Matrix4<T> &m1, const math::Matrix4<T> &m2) {
    bool is_equal = true;
    for (uint8_t i=0; i<16; i++) {
        is_equal = is_equal && (std::abs(m1.data[i] - m2.data[i])<=1e-5); // reasonable value for 'float' that is the type with the biggest approx error
        // printf("%12.9f %12.9f %8.6f %d\n",m1.data[i], m2.data[i], std::abs(m1.data[i] - m2.data[i]), int(is_equal));
    }
    return is_equal;
}

template <typename T>
void print_matrix(const math::Matrix4<T> &m) {
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            printf("%7.5f ", (double)m(i,j));
        }
        printf("\n");
    }
}
} // namespace

// ///////// //
// Matrix4x4 //
// ///////// //

TEST(Matrix4x4, constructors) {
    // default constructor
    std::array<double,16> zero = {0.0, 0.0, 0.0, 0.0, // row0
                                  0.0, 0.0, 0.0, 0.0, // row1
                                  0.0, 0.0, 0.0, 0.0, // row2
                                  0.0, 0.0, 0.0, 0.0};// row3
    std::array<double,16> sample = {11.1, 12.2, 13.3, 14.4, 
                                    21.1, 22.2, 23.3, 24.4, 
                                    31.1, 32.2, 33.3, 34.4, 
                                    41.1, 42.2, 43.3, 44.4};
    math::Matrix4d m1;
    ASSERT_PRED2(matrix_array_equal<double>, m1, zero.data());
    math::Matrix4d m2(sample.data());
    ASSERT_PRED2(matrix_array_equal<double>, m2, sample.data());
    // copy constructor
    math::Matrix4d m3(m2);
    ASSERT_PRED2(matrix_array_equal<double>, m3, sample.data());
    ASSERT_PRED2(matrix_matrix_equal<double>, m3, m2);
    // from matrix different type
    std::array<float,16> sample_f = {11.1f, 12.2f, 13.3f, 14.4f, 
                                     21.1f, 22.2f, 23.3f, 24.4f, 
                                     31.1f, 32.2f, 33.3f, 34.4f, 
                                     41.1f, 42.2f, 43.3f, 44.4f};
    math::Matrix4f m4(m2);
    ASSERT_PRED2(matrix_array_equal<float>, m4, sample_f.data());
    std::array<int32_t,16> sample_i = {11, 12, 13, 14, 
                                       21, 22, 23, 24, 
                                       31, 32, 33, 34, 
                                       41, 42, 43, 44};
    math::Matrix4i m5(m2);
    ASSERT_PRED2(matrix_array_equal<int32_t>, m5, sample_i.data());
    // from initializer list
    math::Matrix4i m6({11, 12, 13, 14, 
                       21, 22, 23, 24, 
                       31, 32, 33, 34, 
                       41, 42, 43, 44});
    ASSERT_PRED2(matrix_array_equal<int32_t>, m6, sample_i.data());
    math::Matrix4f m7({11.1f, 12.2f, 13.3f, 14.4f, 
                       21.1f, 22.2f, 23.3f, 24.4f, 
                       31.1f, 32.2f, 33.3f, 34.4f, 
                       41.1f, 42.2f, 43.3f, 44.4f});
    ASSERT_PRED2(matrix_array_equal<float>, m7, sample_f.data());
}

TEST(Matrix4x4, assignment) {
    std::array<double,16> sample = {11.1, 12.2, 13.3, 14.4, 
                                    21.1, 22.2, 23.3, 24.4, 
                                    31.1, 32.2, 33.3, 34.4, 
                                    41.1, 42.2, 43.3, 44.4};
    math::Matrix4d m1(sample.data());
    math::Matrix4d m2;
    m2 = m1;
    ASSERT_PRED2(matrix_matrix_equal<double>, m1, m2);
    // from a different type
    std::array<int32_t,16> sample_i = {11, 12, 13, 14, 
                                       21, 22, 23, 24, 
                                       31, 32, 33, 34, 
                                       41, 42, 43, 44};
    math::Matrix4i mi;
    mi = m1;
    ASSERT_PRED2(matrix_array_equal<int32_t>, mi, sample_i.data());
}

TEST(Matrix4x4, access) {
    std::array<double,16> sample = {11.1, 12.2, 13.3, 14.4, 
                                    21.1, 22.2, 23.3, 24.4, 
                                    31.1, 32.2, 33.3, 34.4, 
                                    41.1, 42.2, 43.3, 44.4};
    math::Matrix4d m1(sample.data());
    ASSERT_DOUBLE_EQ(m1(0,0), 11.1);
    ASSERT_DOUBLE_EQ(m1(0,1), 12.2);
    ASSERT_DOUBLE_EQ(m1(0,2), 13.3);
    ASSERT_DOUBLE_EQ(m1(0,3), 14.4);
    ASSERT_DOUBLE_EQ(m1(1,0), 21.1);
    ASSERT_DOUBLE_EQ(m1(1,1), 22.2);
    ASSERT_DOUBLE_EQ(m1(1,2), 23.3);
    ASSERT_DOUBLE_EQ(m1(1,3), 24.4);
    ASSERT_DOUBLE_EQ(m1(2,0), 31.1);
    ASSERT_DOUBLE_EQ(m1(2,1), 32.2);
    ASSERT_DOUBLE_EQ(m1(2,2), 33.3);
    ASSERT_DOUBLE_EQ(m1(2,3), 34.4);
    ASSERT_DOUBLE_EQ(m1(3,0), 41.1);
    ASSERT_DOUBLE_EQ(m1(3,1), 42.2);
    ASSERT_DOUBLE_EQ(m1(3,2), 43.3);
    ASSERT_DOUBLE_EQ(m1(3,3), 44.4);
    const math::Matrix4d m2(sample.data());
    ASSERT_DOUBLE_EQ(m2(0,0), 11.1);
    ASSERT_DOUBLE_EQ(m2(0,1), 12.2);
    ASSERT_DOUBLE_EQ(m2(0,2), 13.3);
    ASSERT_DOUBLE_EQ(m2(0,3), 14.4);
    ASSERT_DOUBLE_EQ(m2(1,0), 21.1);
    ASSERT_DOUBLE_EQ(m2(1,1), 22.2);
    ASSERT_DOUBLE_EQ(m2(1,2), 23.3);
    ASSERT_DOUBLE_EQ(m2(1,3), 24.4);
    ASSERT_DOUBLE_EQ(m2(2,0), 31.1);
    ASSERT_DOUBLE_EQ(m2(2,1), 32.2);
    ASSERT_DOUBLE_EQ(m2(2,2), 33.3);
    ASSERT_DOUBLE_EQ(m2(2,3), 34.4);
    ASSERT_DOUBLE_EQ(m2(3,0), 41.1);
    ASSERT_DOUBLE_EQ(m2(3,1), 42.2);
    ASSERT_DOUBLE_EQ(m2(3,2), 43.3);
    ASSERT_DOUBLE_EQ(m2(3,3), 44.4);
    // 'at()' uses the column major order - consider it internal api
    ASSERT_DOUBLE_EQ(m1.at(0,0), 11.1);
    ASSERT_DOUBLE_EQ(m1.at(1,0), 12.2);
    ASSERT_DOUBLE_EQ(m1.at(2,0), 13.3);
    ASSERT_DOUBLE_EQ(m1.at(3,0), 14.4);
    ASSERT_DOUBLE_EQ(m1.at(0,1), 21.1);
    ASSERT_DOUBLE_EQ(m1.at(1,1), 22.2);
    ASSERT_DOUBLE_EQ(m1.at(2,1), 23.3);
    ASSERT_DOUBLE_EQ(m1.at(3,1), 24.4);
    ASSERT_DOUBLE_EQ(m1.at(0,2), 31.1);
    ASSERT_DOUBLE_EQ(m1.at(1,2), 32.2);
    ASSERT_DOUBLE_EQ(m1.at(2,2), 33.3);
    ASSERT_DOUBLE_EQ(m1.at(3,2), 34.4);
    ASSERT_DOUBLE_EQ(m1.at(0,3), 41.1);
    ASSERT_DOUBLE_EQ(m1.at(1,3), 42.2);
    ASSERT_DOUBLE_EQ(m1.at(2,3), 43.3);
    ASSERT_DOUBLE_EQ(m1.at(3,3), 44.4);
    ASSERT_DOUBLE_EQ(m2.at(0,0), 11.1);
    ASSERT_DOUBLE_EQ(m2.at(1,0), 12.2);
    ASSERT_DOUBLE_EQ(m2.at(2,0), 13.3);
    ASSERT_DOUBLE_EQ(m2.at(3,0), 14.4);
    ASSERT_DOUBLE_EQ(m2.at(0,1), 21.1);
    ASSERT_DOUBLE_EQ(m2.at(1,1), 22.2);
    ASSERT_DOUBLE_EQ(m2.at(2,1), 23.3);
    ASSERT_DOUBLE_EQ(m2.at(3,1), 24.4);
    ASSERT_DOUBLE_EQ(m2.at(0,2), 31.1);
    ASSERT_DOUBLE_EQ(m2.at(1,2), 32.2);
    ASSERT_DOUBLE_EQ(m2.at(2,2), 33.3);
    ASSERT_DOUBLE_EQ(m2.at(3,2), 34.4);
    ASSERT_DOUBLE_EQ(m2.at(0,3), 41.1);
    ASSERT_DOUBLE_EQ(m2.at(1,3), 42.2);
    ASSERT_DOUBLE_EQ(m2.at(2,3), 43.3);
    ASSERT_DOUBLE_EQ(m2.at(3,3), 44.4);
}

TEST(Matrix4x4, comparison) {
    std::array<double,16> sample = {11.1, 12.2, 13.3, 14.4, 
                                    21.1, 22.2, 23.3, 24.4, 
                                    31.1, 32.2, 33.3, 34.4, 
                                    41.1, 42.2, 43.3, 44.4};
    math::Matrix4d m0(sample.data());
    math::Matrix4d m1 = math::Matrix4d(sample.data());
    ASSERT_TRUE(m0 == m1);
    ASSERT_FALSE(m0 != m1);
    // change one element at the time
    for (int i=0; i<16; i++) {
        m1 = math::Matrix4d(sample.data());
        m1.data[i] = -1.0;
        ASSERT_FALSE(m0 == m1);
        ASSERT_TRUE(m0 != m1);
    }
}

TEST(Matrix4x4, scalar_operations_internal) {
    math::Matrix4f m1({11.1f, 12.2f, 13.3f, 14.4f, 
                       21.1f, 22.2f, 23.3f, 24.4f, 
                       31.1f, 32.2f, 33.3f, 34.4f, 
                       41.1f, 42.2f, 43.3f, 44.4f});
    m1 += 1.0;
    ASSERT_PRED2(matrix_matrix_equal<float>, m1, math::Matrix4f({12.1f, 13.2f, 14.3f, 15.4f,
                                                                 22.1f, 23.2f, 24.3f, 25.4f,
                                                                 32.1f, 33.2f, 34.3f, 35.4f,
                                                                 42.1f, 43.2f, 44.3f, 45.4f}));
    m1 -= 2.0;
    ASSERT_PRED2(matrix_matrix_equal<float>, m1, math::Matrix4f({10.1f, 11.2f, 12.3f, 13.4f,
                                                                 20.1f, 21.2f, 22.3f, 23.4f,
                                                                 30.1f, 31.2f, 32.3f, 33.4f,
                                                                 40.1f, 41.2f, 42.3f, 43.4f}));
    m1 *= 2.0;
    ASSERT_PRED2(matrix_matrix_equal<float>, m1, math::Matrix4f({20.2f, 22.4f, 24.6f, 26.8f,
                                                                 40.2f, 42.4f, 44.6f, 46.8f,
                                                                 60.2f, 62.4f, 64.6f, 66.8f,
                                                                 80.2f, 82.4f, 84.6f, 86.8f}));
    m1 /= 2.0;
    ASSERT_PRED2(matrix_matrix_equal<float>, m1, math::Matrix4f({10.1f, 11.2f, 12.3f, 13.4f,
                                                                 20.1f, 21.2f, 22.3f, 23.4f,
                                                                 30.1f, 31.2f, 32.3f, 33.4f,
                                                                 40.1f, 41.2f, 42.3f, 43.4f}));
}

TEST(Matrix4x4, matrix_operations) {
    math::Matrix4d m1({11.1, 12.2, 13.3, 14.4,
                       21.1, 22.2, 23.3, 24.4,
                       31.1, 32.2, 33.3, 34.4,
                       41.1, 42.2, 43.3, 44.4});
    math::Matrix4d m2({111.1, 112.2, 113.3, 114.4,
                       121.1, 122.2, 123.3, 124.4,
                       131.1, 132.2, 133.3, 134.4,
                       141.1, 142.2, 143.3, 144.4});
    math::Matrix4d m3 = m1+m2;
    math::Matrix4d m4 = m1-m2;
    ASSERT_PRED2(matrix_matrix_equal<double>, m3, math::Matrix4d({122.2, 124.4, 126.6, 128.8,
                                                                  142.2, 144.4, 146.6, 148.8,
                                                                  162.2, 164.4, 166.6, 168.8,
                                                                  182.2, 184.4, 186.6, 188.8}));
    ASSERT_PRED2(matrix_matrix_equal<double>, m4, math::Matrix4d({-100.0, -100.0, -100.0, -100.0,
                                                                  -100.0, -100.0, -100.0, -100.0,
                                                                  -100.0, -100.0, -100.0, -100.0,
                                                                  -100.0, -100.0, -100.0, -100.0}));
    math::Matrix4d m5 = m1*m2;
    ASSERT_PRED2(matrix_matrix_equal<double>, m5, math::Matrix4d({ 6486.1,  6542.2,  6598.3,  6654.4,
                                                                  11530.1, 11630.2, 11730.3, 11830.4,
                                                                  16574.1, 16718.2, 16862.3, 17006.4,
                                                                  21618.1, 21806.2, 21994.3, 22182.4}));
}

TEST(Matrix4x4, scalar_operations_external) {
    math::Matrix4d m0({11.1, 12.2, 13.3, 14.4,
                       21.1, 22.2, 23.3, 24.4,
                       31.1, 32.2, 33.3, 34.4,
                       41.1, 42.2, 43.3, 44.4});
    math::Matrix4d m1 = m0 + 1.0;
    ASSERT_PRED2(matrix_matrix_equal<double>, m1, math::Matrix4f({12.1, 13.2, 14.3, 15.4,
                                                                  22.1, 23.2, 24.3, 25.4,
                                                                  32.1, 33.2, 34.3, 35.4,
                                                                  42.1, 43.2, 44.3, 45.4}));
    m1 = 1.0 + m0;
    ASSERT_PRED2(matrix_matrix_equal<double>, m1, math::Matrix4f({12.1, 13.2, 14.3, 15.4,
                                                                  22.1, 23.2, 24.3, 25.4,
                                                                  32.1, 33.2, 34.3, 35.4,
                                                                  42.1, 43.2, 44.3, 45.4}));
    m1 = m0 - 2.0;
    ASSERT_PRED2(matrix_matrix_equal<double>, m1, math::Matrix4f({ 9.1, 10.2, 11.3, 12.4,
                                                                  19.1, 20.2, 21.3, 22.4,
                                                                  29.1, 30.2, 31.3, 32.4,
                                                                  39.1, 40.2, 41.3, 42.4}));
    m1 = 2.0 - m0;
    ASSERT_PRED2(matrix_matrix_equal<double>, m1, math::Matrix4f({ -9.1, -10.2, -11.3, -12.4,
                                                                  -19.1, -20.2, -21.3, -22.4,
                                                                  -29.1, -30.2, -31.3, -32.4,
                                                                  -39.1, -40.2, -41.3, -42.4}));
    m1 = m0 * 2.0;
    ASSERT_PRED2(matrix_matrix_equal<double>, m1, math::Matrix4f({22.2, 24.4, 26.6, 28.8,
                                                                  42.2, 44.4, 46.6, 48.8,
                                                                  62.2, 64.4, 66.6, 68.8,
                                                                  82.2, 84.4, 86.6, 88.8}));
    m1 = 2.0 * m0;
    ASSERT_PRED2(matrix_matrix_equal<double>, m1, math::Matrix4f({22.2, 24.4, 26.6, 28.8,
                                                                  42.2, 44.4, 46.6, 48.8,
                                                                  62.2, 64.4, 66.6, 68.8,
                                                                  82.2, 84.4, 86.6, 88.8}));
    m1 = m0 / 2.0;
    ASSERT_PRED2(matrix_matrix_equal<double>, m1, math::Matrix4f({ 5.55,  6.1,  6.65,  7.2,
                                                                  10.55, 11.1, 11.65, 12.2,
                                                                  15.55, 16.1, 16.65, 17.2,
                                                                  20.55, 21.1, 21.65, 22.2}));
}

TEST(Matrix4x4, vector_operations) {
    math::Matrix4d m({11.1, 12.2, 13.3, 14.4,
                      21.1, 22.2, 23.3, 24.4,
                      31.1, 32.2, 33.3, 34.4,
                      41.1, 42.2, 43.3, 44.4});

    math::Vector4d v4d(3,1,2,1);
    math::Vector4d v2 = m * v4d;
    ASSERT_NEAR(v2.x, 86.5, 1e-6);
    ASSERT_NEAR(v2.y, 156.5, 1e-6);
    ASSERT_NEAR(v2.z, 226.5, 1e-6);
    ASSERT_NEAR(v2.w, 296.5, 1e-6);
    // shortcut with a vec3d (assume homogeneous vec with last coord to 1)
    math::Vector3d v(3,1,2);
    math::Vector3d v1 = m * v;
    ASSERT_NEAR(v1.x, 86.5, 1e-6);
    ASSERT_NEAR(v1.y, 156.5, 1e-6);
    ASSERT_NEAR(v1.z, 226.5, 1e-6);
}

TEST(Matrix4x4, other_operators) {
    // sign inversion
    math::Matrix4d m({11.1, 12.2, 13.3, 14.4,
                      21.1, 22.2, 23.3, 24.4,
                      31.1, 32.2, 33.3, 34.4,
                      41.1, 42.2, 43.3, 44.4});
    math::Matrix4d m2 = -m;
    ASSERT_PRED2(matrix_matrix_equal<double>, m2, math::Matrix4f({-11.1, -12.2, -13.3, -14.4,
                                                                  -21.1, -22.2, -23.3, -24.4,
                                                                  -31.1, -32.2, -33.3, -34.4,
                                                                  -41.1, -42.2, -43.3, -44.4}));
    // conversion to pointer to array
    const math::Matrix4d mconst(m);
    const double *p = mconst;
    for (int i=0; i<16; i++) {
        ASSERT_DOUBLE_EQ(p[i], mconst.data[i]);
    }
    double *mp = m;
    for (int i=0; i<16; i++) {
        mp[i] = 3*i + 0.2;
    }
    for (int i=0; i<9; i++) {
        ASSERT_DOUBLE_EQ(3*i+0.2, m.data[i]);
    }
}



