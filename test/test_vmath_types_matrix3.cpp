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
bool matrix_array_equal(const math::Matrix3<T> &m1, const T *m2) {
    bool is_equal = true;
    for (uint8_t i=0; i<3; i++) {
        for (uint8_t j=0; j<3; j++) {
            // array is row-major, but internal dat is col-major
            is_equal = is_equal && (std::abs(m1.data[j*3+i] - m2[i*3+j])<=1e-5); // reasonable value for 'float' that is the type with the biggest approx error        }
        }
    }
    return is_equal;
}
template <typename T> 
bool matrix_matrix_equal(const math::Matrix3<T> &m1, const math::Matrix3<T> &m2) {
    bool is_equal = true;
    for (uint8_t i=0; i<9; i++) {
        is_equal = is_equal && (std::abs(m1.data[i] - m2.data[i])<=1e-5); // reasonable value for 'float' that is the type with the biggest approx error
        // printf("%12.9f %12.9f %8.6f %d\n",m1.data[i], m2.data[i], std::abs(m1.data[i] - m2.data[i]), int(is_equal));
    }
    return is_equal;
}

template <typename T>
void print_matrix(const math::Matrix3<T> &m) {
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            printf("%7.5f ", (double)m(i,j));
        }
        printf("\n");
    }
}
} // namespace

// ///////// //
// Matrix3x3 //
// ///////// //

TEST(Matrix3x3, constructors) {
    // default constructor
    std::array<double,9> zero = {0.0, 0.0, 0.0, // row0
                                 0.0, 0.0, 0.0, // row1
                                 0.0, 0.0, 0.0};// row2
    std::array<double,9> sample = {1.1, 2.2, 3.3, // row0
                                   4.4, 5.5, 6.6, // row1
                                   7.7, 8.8, 9.9};// row2
    math::Matrix3d m1;
    ASSERT_PRED2(matrix_array_equal<double>, m1, zero.data());
    math::Matrix3d m2(sample.data());
    ASSERT_PRED2(matrix_array_equal<double>, m2, sample.data());
    // copy constructor
    math::Matrix3d m3(m2);
    ASSERT_PRED2(matrix_array_equal<double>, m3, sample.data());
    ASSERT_PRED2(matrix_matrix_equal<double>, m3, m2);
    // from matrix different type
    std::array<float,9> sample_f = {1.1f, 2.2f, 3.3f, // row0
                                    4.4f, 5.5f, 6.6f, // row1
                                    7.7f, 8.8f, 9.9f};// row2
    math::Matrix3f m4(m2);
    ASSERT_PRED2(matrix_array_equal<float>, m4, sample_f.data());
    std::array<int32_t,9> sample_i = {1, 2, 3, // row0
                                      4, 5, 6, // row1
                                      7, 8, 9};// row2
    math::Matrix3i m5(m2);
    ASSERT_PRED2(matrix_array_equal<int32_t>, m5, sample_i.data());
    // from initializer list
    math::Matrix3i m6({1, 2, 3, 
                       4, 5, 6, 
                       7, 8, 9});
    ASSERT_PRED2(matrix_array_equal<int32_t>, m6, sample_i.data());
    math::Matrix3f m7({1.1f, 2.2f, 3.3f, 
                       4.4f, 5.5f, 6.6f, 
                       7.7f, 8.8f, 9.9f});
    ASSERT_PRED2(matrix_array_equal<float>, m7, sample_f.data());
}

TEST(Matrix3x3, assignment) {
    std::array<double,9> sample = {1.1, 2.2, 3.3, // row0
                                   4.4, 5.5, 6.6, // row1
                                   7.7, 8.8, 9.9};// row2
    math::Matrix3d m1(sample.data());
    math::Matrix3d m2;
    m2 = m1;
    ASSERT_PRED2(matrix_matrix_equal<double>, m1, m2);
    // from a different type
    std::array<int32_t,9> sample_i = {1, 2, 3, // row0
                                      4, 5, 6, // row1
                                      7, 8, 9};// row2
    math::Matrix3i mi;
    mi = m1;
    ASSERT_PRED2(matrix_array_equal<int32_t>, mi, sample_i.data());
}

TEST(Matrix3x3, access) {
    std::array<double,9> sample = {1.1, 2.2, 3.3, // row0
                                   4.4, 5.5, 6.6, // row1
                                   7.7, 8.8, 9.9};// row2
    math::Matrix3d m1(sample.data());
    ASSERT_DOUBLE_EQ(m1(0,0), 1.1);
    ASSERT_DOUBLE_EQ(m1(0,1), 2.2);
    ASSERT_DOUBLE_EQ(m1(0,2), 3.3);
    ASSERT_DOUBLE_EQ(m1(1,0), 4.4);
    ASSERT_DOUBLE_EQ(m1(1,1), 5.5);
    ASSERT_DOUBLE_EQ(m1(1,2), 6.6);
    ASSERT_DOUBLE_EQ(m1(2,0), 7.7);
    ASSERT_DOUBLE_EQ(m1(2,1), 8.8);
    ASSERT_DOUBLE_EQ(m1(2,2), 9.9);
    const math::Matrix3d m2(sample.data());
    ASSERT_DOUBLE_EQ(m2(0,0), 1.1);
    ASSERT_DOUBLE_EQ(m2(0,1), 2.2);
    ASSERT_DOUBLE_EQ(m2(0,2), 3.3);
    ASSERT_DOUBLE_EQ(m2(1,0), 4.4);
    ASSERT_DOUBLE_EQ(m2(1,1), 5.5);
    ASSERT_DOUBLE_EQ(m2(1,2), 6.6);
    ASSERT_DOUBLE_EQ(m2(2,0), 7.7);
    ASSERT_DOUBLE_EQ(m2(2,1), 8.8);
    ASSERT_DOUBLE_EQ(m2(2,2), 9.9);
    // 'at()' uses the column major order - consider with internal api
    ASSERT_DOUBLE_EQ(m1.at(0,0), 1.1);
    ASSERT_DOUBLE_EQ(m1.at(1,0), 2.2);
    ASSERT_DOUBLE_EQ(m1.at(2,0), 3.3);
    ASSERT_DOUBLE_EQ(m1.at(0,1), 4.4);
    ASSERT_DOUBLE_EQ(m1.at(1,1), 5.5);
    ASSERT_DOUBLE_EQ(m1.at(2,1), 6.6);
    ASSERT_DOUBLE_EQ(m1.at(0,2), 7.7);
    ASSERT_DOUBLE_EQ(m1.at(1,2), 8.8);
    ASSERT_DOUBLE_EQ(m1.at(2,2), 9.9);
    ASSERT_DOUBLE_EQ(m2.at(0,0), 1.1);
    ASSERT_DOUBLE_EQ(m2.at(1,0), 2.2);
    ASSERT_DOUBLE_EQ(m2.at(2,0), 3.3);
    ASSERT_DOUBLE_EQ(m2.at(0,1), 4.4);
    ASSERT_DOUBLE_EQ(m2.at(1,1), 5.5);
    ASSERT_DOUBLE_EQ(m2.at(2,1), 6.6);
    ASSERT_DOUBLE_EQ(m2.at(0,2), 7.7);
    ASSERT_DOUBLE_EQ(m2.at(1,2), 8.8);
    ASSERT_DOUBLE_EQ(m2.at(2,2), 9.9);
}

TEST(Matrix3x3, comparison) {
    std::array<double,9> sample = {1.1, 2.2, 3.3, // row0
                                   4.4, 5.5, 6.6, // row1
                                   7.7, 8.8, 9.9};// row2
    math::Matrix3d m0(sample.data());
    math::Matrix3d m1 = math::Matrix3d(sample.data());
    ASSERT_TRUE(m0 == m1);
    ASSERT_FALSE(m0 != m1);
    // change one element at the time
    for (int i=0; i<9; i++) {
        m1 = math::Matrix3d(sample.data());
        m1.data[i] = -1.0;
        ASSERT_FALSE(m0 == m1);
        ASSERT_TRUE(m0 != m1);
    }
}

TEST(Matrix3x3, scalar_operations_internal) {
    math::Matrix3f m1({1.1f, 2.2f, 3.3f,
                       4.4f, 5.5f, 6.6f,
                       7.7f, 8.8f, 9.9f});
    m1 += 1.0;
    ASSERT_PRED2(matrix_matrix_equal<float>, m1, math::Matrix3f({2.1f, 3.2f, 4.3f,
                                                                 5.4f, 6.5f, 7.6f,
                                                                 8.7f, 9.8f, 10.9f}));
    m1 -= 2.0;
    ASSERT_PRED2(matrix_matrix_equal<float>, m1, math::Matrix3f({0.1f, 1.2f, 2.3f,
                                                                 3.4f, 4.5f, 5.6f,
                                                                 6.7f, 7.8f, 8.9f}));
    m1 *= 2.0;
    ASSERT_PRED2(matrix_matrix_equal<float>, m1, math::Matrix3f({0.2f, 2.4f, 4.6f,
                                                                 6.8f, 9.0f, 11.2f,
                                                                 13.4f, 15.6f, 17.8f}));
    m1 /= 2.0;
    ASSERT_PRED2(matrix_matrix_equal<float>, m1, math::Matrix3f({0.1f, 1.2f, 2.3f,
                                                                 3.4f, 4.5f, 5.6f,
                                                                 6.7f, 7.8f, 8.9f}));
}

TEST(Matrix3x3, matrix_operations) {
    math::Matrix3d m1({1.1, 2.2, 3.3,
                       4.4, 5.5, 6.6,
                       7.7, 8.8, 9.9});
    math::Matrix3d m2({11.1, 12.2, 13.3,
                       14.4, 15.5, 16.6,
                       17.7, 18.8, 19.9});
    math::Matrix3d m3 = m1+m2;
    math::Matrix3d m4 = m1-m2;
    ASSERT_PRED2(matrix_matrix_equal<double>, m3, math::Matrix3d({12.2, 14.4, 16.6,
                                                                  18.8, 21.0, 23.2,
                                                                  25.4, 27.6, 29.8}));
    ASSERT_PRED2(matrix_matrix_equal<double>, m4, math::Matrix3d({-10.0, -10.0, -10.0,
                                                                  -10.0, -10.0, -10.0,
                                                                  -10.0, -10.0, -10.0}));
    math::Matrix3d m5 = m1*m2;
    ASSERT_PRED2(matrix_matrix_equal<double>, m5, math::Matrix3d({102.30, 109.56, 116.82,
                                                                  244.86, 263.01, 281.16,
                                                                  387.42, 416.46, 445.50}));
}


TEST(Matrix3x3, scalar_operations_external) {
    math::Matrix3d m0({1.1, 2.2, 3.3,
                       4.4, 5.5, 6.6,
                       7.7, 8.8, 9.9});
    math::Matrix3d m1 = m0 + 1.0;
    ASSERT_PRED2(matrix_matrix_equal<double>, m1, math::Matrix3f({2.1, 3.2, 4.3,
                                                                  5.4, 6.5, 7.6,
                                                                  8.7, 9.8, 10.9}));
    m1 = 1.0 + m0;
    ASSERT_PRED2(matrix_matrix_equal<double>, m1, math::Matrix3f({2.1, 3.2, 4.3,
                                                                  5.4, 6.5, 7.6,
                                                                  8.7, 9.8, 10.9}));
    m1 = m0 - 2.0;
    ASSERT_PRED2(matrix_matrix_equal<double>, m1, math::Matrix3f({-0.9, 0.2, 1.3,
                                                                  2.4, 3.5, 4.6,
                                                                  5.7, 6.8, 7.9}));
    m1 = 2.0 - m0;
    ASSERT_PRED2(matrix_matrix_equal<double>, m1, math::Matrix3f({0.9, -0.2, -1.3,
                                                                  -2.4, -3.5, -4.6,
                                                                  -5.7, -6.8, -7.9}));
    m1 = m0 * 2.0;
    ASSERT_PRED2(matrix_matrix_equal<double>, m1, math::Matrix3f({2.2, 4.4, 6.6,
                                                                  8.8, 11.0, 13.2,
                                                                  15.4, 17.6, 19.8}));
    m1 = 2.0 * m0;
    ASSERT_PRED2(matrix_matrix_equal<double>, m1, math::Matrix3f({2.2, 4.4, 6.6,
                                                                  8.8, 11.0, 13.2,
                                                                  15.4, 17.6, 19.8}));
    m1 = m0 / 2.0;
    ASSERT_PRED2(matrix_matrix_equal<double>, m1, math::Matrix3f({0.55, 1.1, 1.65,
                                                                  2.2, 2.75, 3.3,
                                                                  3.85, 4.4, 4.95}));
}

TEST(Matrix3x3, vector_operations) {
    math::Matrix3d m({1.1, 2.2, 3.3,
                      4.4, 5.5, 6.6,
                      7.7, 8.8, 9.9});
    math::Vector3d v(3,1,2);
    math::Vector3d v1 = m * v;
    ASSERT_NEAR(v1.x, 12.1, 1e-6);
    ASSERT_NEAR(v1.y, 31.9, 1e-6);
    ASSERT_NEAR(v1.z, 51.7, 1e-6);
}

TEST(Matrix3x3, other_operators) {
    // sign inversion
    math::Matrix3d m({1.1, 2.2, 3.3,
                      4.4, 5.5, 6.6,
                      7.7, 8.8, 9.9});
    math::Matrix3d m2 = -m;
    ASSERT_PRED2(matrix_matrix_equal<double>, m2, math::Matrix3f({-1.1, -2.2, -3.3,
                                                                  -4.4, -5.5, -6.6,
                                                                  -7.7, -8.8, -9.9}));
    // conversion to pointer to array
    const math::Matrix3d mconst(m);
    const double *p = mconst;
    for (int i=0; i<9; i++) {
        ASSERT_DOUBLE_EQ(p[i], mconst.data[i]);
    }
    double *mp = m;
    for (int i=0; i<9; i++) {
        mp[i] = 3*i + 0.2;
    }
    for (int i=0; i<9; i++) {
        ASSERT_DOUBLE_EQ(3*i+0.2, m.data[i]);
    }
}



