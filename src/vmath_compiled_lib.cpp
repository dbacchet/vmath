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

// template struct math::Quaternion<float>;
// template struct math::Quaternion<double>;
