#include "vmath_types.h"
#include "vmath_types_impl.h"

#include <cstdint>

// use explicit instantiation to reduce compilation time
template struct math::Vector2<int8_t>;
template struct math::Vector2<int32_t>;
template struct math::Vector2<int64_t>;
template struct math::Vector2<float>;
template struct math::Vector2<double>;

template struct math::Vector3<int8_t>;
template struct math::Vector3<int32_t>;
template struct math::Vector3<int64_t>;
template struct math::Vector3<float>;
template struct math::Vector3<double>;

template struct math::Vector4<int8_t>;
template struct math::Vector4<int32_t>;
template struct math::Vector4<int64_t>;
template struct math::Vector4<float>;
template struct math::Vector4<double>;

template struct math::Matrix3<int8_t>;
template struct math::Matrix3<int32_t>;
template struct math::Matrix3<int64_t>;
template struct math::Matrix3<float>;
template struct math::Matrix3<double>;

template struct math::Matrix4<int8_t>;
template struct math::Matrix4<int32_t>;
template struct math::Matrix4<int64_t>;
template struct math::Matrix4<float>;
template struct math::Matrix4<double>;

template struct math::Quaternion<float>;
template struct math::Quaternion<double>;


#include "vmath.h"
#include "vmath_impl.h"

#define VMATH_FUNCTIONS_VECTOR(T) \
namespace math { \
    template T          length<T>(const Vector2<T> &vec); \
    template T          length2<T>(const Vector2<T> &vec); \
    template void       normalize<T>(Vector2<T> &vec); \
    template Vector2<T> lerp<T>(const Vector2<T>& v1, const Vector2<T>& v2, T fact); \
\
    template T          length<T>(const Vector3<T>& vec); \
    template T          length2<T>(const Vector3<T>& vec); \
    template void       normalize<T>(Vector3<T>& vec); \
    template Vector3<T> lerp<T>(const Vector3<T>& v1, const Vector3<T>& v2, T fact); \
\
    template T          length<T>(const Vector4<T>& vec); \
    template T          length2<T>(const Vector4<T>& vec); \
    template void       normalize<T>(Vector4<T>& vec); \
    template Vector4<T> lerp<T>(const Vector4<T>& v1, const Vector4<T>& v2, T fact); \
\
}

#define VMATH_FUNCTIONS_MATRIX(T) \
namespace math { \
    template void       set_zero<T>(Matrix3<T> &mat); \
    template void       set_identity<T>(Matrix3<T> &mat); \
    template void       transpose<T>(Matrix3<T> &mat); \
    template T          det<T>(const Matrix3<T> &mat); \
    template Matrix3<T> inverse<T>(const Matrix3<T> &mat); \
    template Matrix3<T> lerp<T>(const Matrix3<T>& m1, const Matrix3<T>& m2, T fact); \
\
    template void       set_zero<T>(Matrix4<T> &mat); \
    template void       set_identity<T>(Matrix4<T> &mat); \
    template Vector3<T> translation<T>(const Matrix4<T> &mat); \
    template void       set_translation<T>(Matrix4<T> &mat, const Vector3<T>& v); \
    template void       set_rotation<T>(Matrix4<T> &mat, const Matrix3<T>& rot); \
    template T          det<T>(const Matrix4<T> &m); \
    template Matrix4<T> inverse<T>(const Matrix4<T> &m); \
    template void       transpose<T>(Matrix4<T> &mat); \
    template Matrix4<T> lerp<T>(const Matrix4<T>& m1, const Matrix4<T>& m2, T fact); \
\
}

#define VMATH_FUNCTIONS_QUATERNION(T) \
namespace math { \
    template T             length<T>(const Quaternion<T> &q); \
    template T             length2<T>(const Quaternion<T> &q); \
    template void          normalize<T>(Quaternion<T> &q); \
    template Vector3<T>    axis<T>(const Quaternion<T> &q); \
    template T             angle<T>(const Quaternion<T> &q); \
    template Matrix3<T>    rot_matrix<T>(const Quaternion<T> &q); \
    template Matrix4<T>    transform<T>(const Quaternion<T> &q); \
    template Quaternion<T> lerp<T>(const Quaternion<T> &q1, const Quaternion<T> &q2, T fact); \
    template Quaternion<T> slerp<T>(const Quaternion<T>& q1, const Quaternion<T>& q2, T r); \
}

#define VMATH_FUNCTIONS_FACTORIES(T) \
namespace math { \
namespace factory { \
    template Matrix4<T> create_translation<T>(const Vector3<T>& v); \
    template Matrix4<T> create_transformation<T>(const Vector3<T>& v, const Quaternion<T> &q); \
    template Matrix4<T> create_lookat<T>(const Vector3<T>& eye, const Vector3<T>& to, const Vector3<T>& up=Vector3<T>(T(0),T(0),T(1))); \
    template Quaternion<T> quat_from_euler_321<T>(T x, T y, T z); \
    template Quaternion<T> quat_from_axis_angle<T>(Vector3<T> axis, T angle); \
    template Quaternion<T> quat_from_matrix<T>(const Matrix4<T>& m); \
    template Quaternion<T> quat_from_matrix<T>(const Matrix3<T>& m); \
} \
}

VMATH_FUNCTIONS_VECTOR(uint8_t)
VMATH_FUNCTIONS_VECTOR(int8_t)
VMATH_FUNCTIONS_VECTOR(int32_t)
VMATH_FUNCTIONS_VECTOR(int64_t)
VMATH_FUNCTIONS_VECTOR(float)
VMATH_FUNCTIONS_VECTOR(double)

VMATH_FUNCTIONS_MATRIX(int8_t)
VMATH_FUNCTIONS_MATRIX(int32_t)
VMATH_FUNCTIONS_MATRIX(int64_t)
VMATH_FUNCTIONS_MATRIX(float)
VMATH_FUNCTIONS_MATRIX(double)

VMATH_FUNCTIONS_QUATERNION(float)
VMATH_FUNCTIONS_QUATERNION(double)

VMATH_FUNCTIONS_FACTORIES(float)
VMATH_FUNCTIONS_FACTORIES(double)
