#include "vmath.h"

#include <gtest/gtest.h>

#include <cmath>
#include <vector>
#include <numeric>

namespace {
template <typename T>
void print_vec3(const math::Vector3<T> &q) {
    printf("%9.7f %9.7f %9.7f\n", (double)q.x, (double)q.y, (double)q.z);
}

template <typename T>
void print_quat(const math::Quaternion<T> &q) {
    printf("%9.7f %9.7f %9.7f %9.7f\n", (double)q.w, (double)q.x, (double)q.y, (double)q.z);
}

template <typename T>
void print_matrix(const math::Matrix4<T> &m) {
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            printf("%9.7f ", (double)m(i,j));
        }
        printf("\n");
    }
}

template <typename T> 
bool orientation_equal(const math::Quaternion<T> &q1, const math::Quaternion<T> &q2) {
    T tolerance = 1e-5;
    bool is_equal = std::abs(q1.w-q2.w)<tolerance
                 && std::abs(q1.x-q2.x)<tolerance
                 && std::abs(q1.y-q2.y)<tolerance
                 && std::abs(q1.z-q2.z)<tolerance;
    bool is_opposite = std::abs(q1.w+q2.w)<tolerance
                    && std::abs(q1.x+q2.x)<tolerance
                    && std::abs(q1.y+q2.y)<tolerance
                    && std::abs(q1.z+q2.z)<tolerance;
    return is_equal || is_opposite;
}
} // namespace

TEST(Factories, matrices) {
    math::Matrix3f m1 = math::matrix3_identity<float>();
    math::Matrix4f m2 = math::matrix4_identity<float>();
    ASSERT_EQ(m1, math::Matrix3f({1,0,0,
                                  0,1,0,
                                  0,0,1}));
    ASSERT_EQ(m2, math::Matrix4f({1,0,0,0,
                                  0,1,0,0,
                                  0,0,1,0,
                                  0,0,0,1}));
    math::Matrix4f m3 = math::create_translation(math::Vector3f(1,2,3));
    ASSERT_EQ(m3, math::Matrix4f({1,0,0,1,
                                  0,1,0,2,
                                  0,0,1,3,
                                  0,0,0,1}));
	math::Quatf r1(0.8775826, 0.1281319, 0.2562637, 0.3843956); // axis {1,2,3}, angle 1rad
    math::Matrix4f m4 = math::create_transformation(math::Vector3f(1,2,3), r1);
    ASSERT_EQ(m4, math::Matrix4f({ 0.5731379, -0.6090066,  0.5482918, 1,
                                   0.7403488,  0.6716445, -0.0278793, 2,
                                  -0.3512785,  0.4219059,  0.8358222, 3,
                                   0,          0,          0,         1}));
}

TEST(Factories, lookat) {
    math::Matrix4f m1 = math::create_lookat(math::Vector3f(0,-10,0), math::Vector3f(0,0,0), math::Vector3f(0,0,1));
    ASSERT_EQ(m1, math::Matrix4f({1.0, 0.0, 0.0,  0.0,
                                  0.0, 0.0,-1.0,-10.0,
                                  0.0, 1.0, 0.0,  0.0,
                                  0.0, 0.0, 0.0,  1.0}));
    // ADD MORE TESTS HERE!!
}

TEST(Factories, euler) {
    // from euler body321
    math::Quatf q1 = math::quat_from_euler_321(0.0,0.0,0.0);
    ASSERT_EQ(q1, math::Quatf(1,0,0,0));
    q1 = math::quat_from_euler_321(0.0,0.0,1.0);
    ASSERT_EQ(q1, math::Quatf(0.8775826,0,0,0.4794255));
    q1 = math::quat_from_euler_321(0.0,1.0,0.0);
    ASSERT_EQ(q1, math::Quatf(0.8775826,0,0.4794255,0));
    q1 = math::quat_from_euler_321(1.0,0.0,0.0);
    ASSERT_EQ(q1, math::Quatf(0.8775826,0.4794255,0,0));
    q1 = math::quat_from_euler_321(0.1,0.2,0.3);
    ASSERT_EQ(q1, math::Quatf(0.9833474, 0.0342708, 0.1060205, 0.1435722));
    q1 = math::quat_from_euler_321(1.0,2.0,3.0);
    ASSERT_EQ(q1, math::Quatf(0.4359528,-0.718287, 0.3106225, 0.4444351));
    // to euler body321
    math::Vector3f v1 = math::to_euler_321(math::Quatf(0.9833474, 0.0342708, 0.1060205, 0.1435722));
    ASSERT_EQ(v1, math::Vector3f(0.1, 0.2, 0.3));
    // since there are different representation of the same orientation using euler angles, convert back to quaternion and check that
    auto quat_to_euler_to_quat = [](const math::Quatf &q) {
        math::Vector3f euler = math::to_euler_321(q);
        bool gimbal_lock = std::abs(std::abs(euler.x)-M_PI_2) < 1e-3
                        || std::abs(std::abs(euler.y)-M_PI_2) < 1e-3
                        || std::abs(std::abs(euler.z)-M_PI_2) < 1e-3;
        return std::pair<bool, math::Quatf>(gimbal_lock, math::quat_from_euler_321(euler.x, euler.y, euler.z));
    };
    for (double w=-1.0; w<1.0; w+=0.1) {
        for (double x=-1.0; x<1.0; x+=0.1) {
            for (double y=-1.0; y<1.0; y+=0.1) {
                for (double z=-1.0; z<1.0; z+=0.1) {
                    math::Quatd q1(w,x,y,z);
                    math::normalize(q1);
                    auto res = quat_to_euler_to_quat(q1);
                    bool gimbal_lock = res.first;
                    if (gimbal_lock) {
                        continue; // euler angles cannot represent correctly this orientation
                    }
                    math::Quatd q2 = res.second;
                    ASSERT_PRED2(orientation_equal<float>, q1, q2);
                }
            }
        }
    }
}

TEST(Factories, axis_angle) {
    math::Quatf q1 = math::quat_from_axis_angle<float>(math::normalized(math::Vector3f(1,2,3)), 1.0);
    ASSERT_EQ(q1, math::Quatf(0.8775826, 0.1281319, 0.2562637, 0.3843956));
    q1 = math::quat_from_axis_angle<float>(math::normalized(math::Vector3f(5,2,3)), 0.5);
    ASSERT_EQ(q1, math::Quatf(0.9689124, 0.2006711, 0.0802684, 0.1204027));
}

TEST(Factories, quaternions) {
    // matrix3
    math::Matrix3f m1({ 0.9581203, -0.2011042,  0.2038689,
                        0.2655344,  0.8904686, -0.3695364, 
                       -0.1072235,  0.4081945,  0.9065762 });
    math::Quatf q1 = math::quat_from_matrix(m1);
    ASSERT_PRED2(orientation_equal<float>, q1, math::Quatf(0.9689124, 0.2006711, 0.0802684, 0.1204027));
    // matrix with negative trace and xx component dominant:
    math::Matrix3f m2({0.8518519, -0.0740741,  0.5185185,
                       0.3703704, -0.6148148, -0.6962963,
                       0.3703704,  0.7851852, -0.4962963});
    math::Quatf q2 = math::quat_from_matrix(m2);
    ASSERT_PRED2(orientation_equal<float>, q2, math::Quatf(0.4303315, 0.860663, 0.0860663, 0.2581989));
    // matrix with negative trace and yy component dominant:
    math::Matrix3f m3({-0.8010421,  0.3810056,  0.4616993,
                        0.4996996,  0.8502801,  0.1653000,
                       -0.3295935,  0.3631231, -0.8714985});
    math::Quatf q3 = math::quat_from_matrix(m3);
    ASSERT_PRED2(orientation_equal<float>, q3, math::Quatf(-0.2107958, -0.2346147, -0.9384589, -0.1407688));
    // matrix with negative trace and zz component dominant:
    math::Matrix3f m4({-0.8597005, -0.3850632,  0.3356210,
                        0.4262070, -0.9029015,  0.0558256,
                        0.2815363,  0.1910373,  0.9403415});
    math::Quatf q4 = math::quat_from_matrix(m4);
    ASSERT_PRED2(orientation_equal<float>, q4, math::Quatf(-0.2107958, -0.1603586, -0.0641434, -0.9621517));
    // matrix4
    math::Matrix4f m5({ 0.9581203, -0.2011042,  0.2038689, 10,
                        0.2655344,  0.8904686, -0.3695364, 11, 
                       -0.1072235,  0.4081945,  0.9065762, 12,
                        0.0      ,  0.0      ,  0.0      , 1.0});
    math::Quatf q5 = math::quat_from_matrix(m5);
    ASSERT_PRED2(orientation_equal<float>, q5, math::Quatf(0.9689124, 0.2006711, 0.0802684, 0.1204027));
    // matrix with negative trace and xx component dominant:
    math::Matrix4f m6({0.8518519, -0.0740741,  0.5185185, 33,
                       0.3703704, -0.6148148, -0.6962963, 33,
                       0.3703704,  0.7851852, -0.4962963, 33,
                        0.0      ,  0.0      ,  0.0      , 1.0});
    math::Quatf q6 = math::quat_from_matrix(m6);
    ASSERT_PRED2(orientation_equal<float>, q6, math::Quatf(0.4303315, 0.860663, 0.0860663, 0.2581989));
    // matrix with negative trace and yy component dominant:
    math::Matrix4f m7({-0.8010421,  0.3810056,  0.4616993, 0,
                        0.4996996,  0.8502801,  0.1653000, 0,
                       -0.3295935,  0.3631231, -0.8714985, 0,
                        0.0      ,  0.0      ,  0.0      , 1.0});
    math::Quatf q7 = math::quat_from_matrix(m7);
    ASSERT_PRED2(orientation_equal<float>, q7, math::Quatf(-0.2107958, -0.2346147, -0.9384589, -0.1407688));
    // matrix with negative trace and zz component dominant:
    math::Matrix4f m8({-0.8597005, -0.3850632,  0.3356210, 3,
                        0.4262070, -0.9029015,  0.0558256, 2,
                        0.2815363,  0.1910373,  0.9403415, 1,
                        0.0      ,  0.0      ,  0.0      , 1.0});
    math::Quatf q8 = math::quat_from_matrix(m8);
    ASSERT_PRED2(orientation_equal<float>, q8, math::Quatf(-0.2107958, -0.1603586, -0.0641434, -0.9621517));
}

