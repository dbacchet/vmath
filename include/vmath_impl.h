// ///////////////////////////////////////////////////////////////////////////// //
// The MIT License (MIT)                                                         //
//                                                                               //
// Copyright (c) 2012-2020, Davide Bacchet (davide.bacchet@gmail.com)            //
//                                                                               //
// Permission is hereby granted, free of charge, to any person obtaining a copy  //
// of this software and associated documentation files (the "Software"), to deal //
// in the Software without restriction, including without limitation the rights  //
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell     //
// copies of the Software, and to permit persons to whom the Software is         //
// furnished to do so, subject to the following conditions:                      //
//                                                                               //
// The above copyright notice and this permission notice shall be included in    //
// all copies or substantial portions of the Software.                           //
//                                                                               //
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR    //
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,      //
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE   //
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER        //
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, //
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN     //
// THE SOFTWARE.                                                                 //
// ///////////////////////////////////////////////////////////////////////////// //

#pragma once

#include <cmath>
#include <cassert>
#include <cstring>

namespace math {

// //////////////////////// //
// function implementations //
// //////////////////////// //

#define VMATH_EPSILON (4.37114e-07)
// namespace vector2
template <typename T> inline T length(const Vector2<T> &vec) {
    return (T)sqrt(vec.x * vec.x + vec.y * vec.y);
}

template <typename T> inline T length2(const Vector2<T> &vec) {
    return vec.x * vec.x + vec.y * vec.y;
}

template <typename T> void normalize(Vector2<T> &vec) {
    T s = length(vec);
    vec.x /= s;
    vec.y /= s;
}

template <typename T> Vector2<T> normalized(const Vector2<T> &vec) {
    T s = length(vec);
    return Vector2<T>(T(vec.x/s), T(vec.y/s));
}

template <typename T> inline Vector2<T> lerp(const Vector2<T> &v1, const Vector2<T> &v2, T fact) {
    return v1 + (v2 - v1) * fact;
}

// namespace vector3
template <typename T> inline T length(const Vector3<T> &vec) {
    return (T)sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

template <typename T> inline T length2(const Vector3<T> &vec) {
    return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
}

template <typename T> void normalize(Vector3<T> &vec) {
    T s = length(vec);
    vec.x /= s;
    vec.y /= s;
    vec.z /= s;
}

template <typename T> Vector3<T> normalized(const Vector3<T> &vec) {
    T s = length(vec);
    return Vector3<T>(T(vec.x/s), T(vec.y/s), T(vec.z/s));
}

template <typename T> inline Vector3<T> lerp(const Vector3<T> &v1, const Vector3<T> &v2, T fact) {
    return v1 + (v2 - v1) * fact;
}

// namespace vector4
template <typename T> inline T length(const Vector4<T> &vec) {
    return (T)sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w);
}

template <typename T> inline T length2(const Vector4<T> &vec) {
    return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w;
}

template <typename T> inline void normalize(Vector4<T> &vec) {
    T s = length(vec);
    vec.x /= s;
    vec.y /= s;
    vec.z /= s;
    vec.w /= s;
}

template <typename T> Vector4<T> normalized(const Vector4<T> &vec) {
    T s = length(vec);
    return Vector4<T>(T(vec.x/s), T(vec.y/s), T(vec.z/s), T(vec.w/s));
}

template <typename T> inline Vector4<T> lerp(const Vector4<T> &v1, const Vector4<T> &v2, T fact) {
    return v1 + (v2 - v1) * fact;
}

// namespace matrix3
template <typename T> inline void set_zero(Matrix3<T> &mat) {
    for (int i = 0; i < 9; i++)
        mat.data[i] = T(0);
}

template <typename T> inline void set_identity(Matrix3<T> &mat) {
    for (int i = 0; i < 9; i++)
        mat.data[i] = (i % 4) ? T(0) : T(1);
}

template <typename T> inline void transpose(Matrix3<T> &mat) {
    Matrix3<T> ret;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            ret.at(i, j) = mat.at(j, i);
        }
    }
    mat = ret;
}

template <typename T> inline Matrix3<T> lerp(const Matrix3<T> &m1, const Matrix3<T> &m2, T fact) {
    return m1 + (m2 - m1) * fact;
}

template <typename T> inline T det(const Matrix3<T> &mat) {
    return mat.at(0, 0) * mat.at(1, 1) * mat.at(2, 2) + mat.at(0, 1) * mat.at(1, 2) * mat.at(2, 0) +
           mat.at(0, 2) * mat.at(1, 0) * mat.at(2, 1) - mat.at(0, 0) * mat.at(1, 2) * mat.at(2, 1) -
           mat.at(0, 1) * mat.at(1, 0) * mat.at(2, 2) - mat.at(0, 2) * mat.at(1, 1) * mat.at(2, 0);
}

template <typename T> inline Matrix3<T> inverse(const Matrix3<T> &mat) {
    T d = det(mat);
    /// \todo better API in case the inverse does not exist. See https://github.com/dbacchet/vmath/issues/3
    if (std::abs(d)<VMATH_EPSILON) {
        return Matrix3<T>(); // return null matrix
    }
    Matrix3<T> ret;
    ret.at(0, 0) = mat.at(1, 1) * mat.at(2, 2) - mat.at(2, 1) * mat.at(1, 2);
    ret.at(0, 1) = mat.at(2, 1) * mat.at(0, 2) - mat.at(0, 1) * mat.at(2, 2);
    ret.at(0, 2) = mat.at(0, 1) * mat.at(1, 2) - mat.at(1, 1) * mat.at(0, 2);
    ret.at(1, 0) = mat.at(2, 0) * mat.at(1, 2) - mat.at(1, 0) * mat.at(2, 2);
    ret.at(1, 1) = mat.at(0, 0) * mat.at(2, 2) - mat.at(2, 0) * mat.at(0, 2);
    ret.at(1, 2) = mat.at(1, 0) * mat.at(0, 2) - mat.at(0, 0) * mat.at(1, 2);
    ret.at(2, 0) = mat.at(1, 0) * mat.at(2, 1) - mat.at(2, 0) * mat.at(1, 1);
    ret.at(2, 1) = mat.at(2, 0) * mat.at(0, 1) - mat.at(0, 0) * mat.at(2, 1);
    ret.at(2, 2) = mat.at(0, 0) * mat.at(1, 1) - mat.at(1, 0) * mat.at(0, 1);
    return ret * T(T(1) / d);
}

// namespace matrix4
template <typename T> inline void set_zero(Matrix4<T> &mat) {
    for (int i = 0; i < 16; i++)
        mat.data[i] = T(0);
}

template <typename T> inline void set_identity(Matrix4<T> &mat) {
    for (int i = 0; i < 16; i++)
        mat.data[i] = (i % 5) ? T(0) : T(1);
}

/// set translation part of matrix.
template <typename T> inline void set_translation(Matrix4<T> &mat, const Vector3<T> &v) {
    mat.at(3, 0) = v.x;
    mat.at(3, 1) = v.y;
    mat.at(3, 2) = v.z;
    mat.at(3, 3) = 1;
}
/// get translation vector
template <typename T> inline Vector3<T> translation(const Matrix4<T> &mat) {
    return Vector3<T>(mat.at(3, 0), mat.at(3, 1), mat.at(3, 2));
}
/// set matrix rotation part
template <typename T> inline void set_rotation(Matrix4<T> &mat, const Matrix3<T> &rot) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mat.at(i, j) = rot.at(i, j);
        }
    }
}
/// determinant
template <typename T> T det(const Matrix4<T> &m) {
    return m.at(3, 0) * m.at(2, 1) * m.at(1, 2) * m.at(0, 3) - m.at(2, 0) * m.at(3, 1) * m.at(1, 2) * m.at(0, 3) -
           m.at(3, 0) * m.at(1, 1) * m.at(2, 2) * m.at(0, 3) + m.at(1, 0) * m.at(3, 1) * m.at(2, 2) * m.at(0, 3) +
           m.at(2, 0) * m.at(1, 1) * m.at(3, 2) * m.at(0, 3) - m.at(1, 0) * m.at(2, 1) * m.at(3, 2) * m.at(0, 3) -
           m.at(3, 0) * m.at(2, 1) * m.at(0, 2) * m.at(1, 3) + m.at(2, 0) * m.at(3, 1) * m.at(0, 2) * m.at(1, 3) +
           m.at(3, 0) * m.at(0, 1) * m.at(2, 2) * m.at(1, 3) - m.at(0, 0) * m.at(3, 1) * m.at(2, 2) * m.at(1, 3) -
           m.at(2, 0) * m.at(0, 1) * m.at(3, 2) * m.at(1, 3) + m.at(0, 0) * m.at(2, 1) * m.at(3, 2) * m.at(1, 3) +
           m.at(3, 0) * m.at(1, 1) * m.at(0, 2) * m.at(2, 3) - m.at(1, 0) * m.at(3, 1) * m.at(0, 2) * m.at(2, 3) -
           m.at(3, 0) * m.at(0, 1) * m.at(1, 2) * m.at(2, 3) + m.at(0, 0) * m.at(3, 1) * m.at(1, 2) * m.at(2, 3) +
           m.at(1, 0) * m.at(0, 1) * m.at(3, 2) * m.at(2, 3) - m.at(0, 0) * m.at(1, 1) * m.at(3, 2) * m.at(2, 3) -
           m.at(2, 0) * m.at(1, 1) * m.at(0, 2) * m.at(3, 3) + m.at(1, 0) * m.at(2, 1) * m.at(0, 2) * m.at(3, 3) +
           m.at(2, 0) * m.at(0, 1) * m.at(1, 2) * m.at(3, 3) - m.at(0, 0) * m.at(2, 1) * m.at(1, 2) * m.at(3, 3) -
           m.at(1, 0) * m.at(0, 1) * m.at(2, 2) * m.at(3, 3) + m.at(0, 0) * m.at(1, 1) * m.at(2, 2) * m.at(3, 3);
}
/// calc inverse matrix
template <typename T> Matrix4<T> inverse(const Matrix4<T> &m) {
    /// \todo better API in case the inverse does not exist. See https://github.com/dbacchet/vmath/issues/3
    T d = det(m);
    if (std::abs(d)<VMATH_EPSILON) {
        return Matrix4<T>(); // return null matrix
    }
    Matrix4<T> ret;
    ret.at(0, 0) = m.at(2, 1) * m.at(3, 2) * m.at(1, 3) - m.at(3, 1) * m.at(2, 2) * m.at(1, 3) +
                   m.at(3, 1) * m.at(1, 2) * m.at(2, 3) - m.at(1, 1) * m.at(3, 2) * m.at(2, 3) -
                   m.at(2, 1) * m.at(1, 2) * m.at(3, 3) + m.at(1, 1) * m.at(2, 2) * m.at(3, 3);
    ret.at(1, 0) = m.at(3, 0) * m.at(2, 2) * m.at(1, 3) - m.at(2, 0) * m.at(3, 2) * m.at(1, 3) -
                   m.at(3, 0) * m.at(1, 2) * m.at(2, 3) + m.at(1, 0) * m.at(3, 2) * m.at(2, 3) +
                   m.at(2, 0) * m.at(1, 2) * m.at(3, 3) - m.at(1, 0) * m.at(2, 2) * m.at(3, 3);
    ret.at(2, 0) = m.at(2, 0) * m.at(3, 1) * m.at(1, 3) - m.at(3, 0) * m.at(2, 1) * m.at(1, 3) +
                   m.at(3, 0) * m.at(1, 1) * m.at(2, 3) - m.at(1, 0) * m.at(3, 1) * m.at(2, 3) -
                   m.at(2, 0) * m.at(1, 1) * m.at(3, 3) + m.at(1, 0) * m.at(2, 1) * m.at(3, 3);
    ret.at(3, 0) = m.at(3, 0) * m.at(2, 1) * m.at(1, 2) - m.at(2, 0) * m.at(3, 1) * m.at(1, 2) -
                   m.at(3, 0) * m.at(1, 1) * m.at(2, 2) + m.at(1, 0) * m.at(3, 1) * m.at(2, 2) +
                   m.at(2, 0) * m.at(1, 1) * m.at(3, 2) - m.at(1, 0) * m.at(2, 1) * m.at(3, 2);
    ret.at(0, 1) = m.at(3, 1) * m.at(2, 2) * m.at(0, 3) - m.at(2, 1) * m.at(3, 2) * m.at(0, 3) -
                   m.at(3, 1) * m.at(0, 2) * m.at(2, 3) + m.at(0, 1) * m.at(3, 2) * m.at(2, 3) +
                   m.at(2, 1) * m.at(0, 2) * m.at(3, 3) - m.at(0, 1) * m.at(2, 2) * m.at(3, 3);
    ret.at(1, 1) = m.at(2, 0) * m.at(3, 2) * m.at(0, 3) - m.at(3, 0) * m.at(2, 2) * m.at(0, 3) +
                   m.at(3, 0) * m.at(0, 2) * m.at(2, 3) - m.at(0, 0) * m.at(3, 2) * m.at(2, 3) -
                   m.at(2, 0) * m.at(0, 2) * m.at(3, 3) + m.at(0, 0) * m.at(2, 2) * m.at(3, 3);
    ret.at(2, 1) = m.at(3, 0) * m.at(2, 1) * m.at(0, 3) - m.at(2, 0) * m.at(3, 1) * m.at(0, 3) -
                   m.at(3, 0) * m.at(0, 1) * m.at(2, 3) + m.at(0, 0) * m.at(3, 1) * m.at(2, 3) +
                   m.at(2, 0) * m.at(0, 1) * m.at(3, 3) - m.at(0, 0) * m.at(2, 1) * m.at(3, 3);
    ret.at(3, 1) = m.at(2, 0) * m.at(3, 1) * m.at(0, 2) - m.at(3, 0) * m.at(2, 1) * m.at(0, 2) +
                   m.at(3, 0) * m.at(0, 1) * m.at(2, 2) - m.at(0, 0) * m.at(3, 1) * m.at(2, 2) -
                   m.at(2, 0) * m.at(0, 1) * m.at(3, 2) + m.at(0, 0) * m.at(2, 1) * m.at(3, 2);
    ret.at(0, 2) = m.at(1, 1) * m.at(3, 2) * m.at(0, 3) - m.at(3, 1) * m.at(1, 2) * m.at(0, 3) +
                   m.at(3, 1) * m.at(0, 2) * m.at(1, 3) - m.at(0, 1) * m.at(3, 2) * m.at(1, 3) -
                   m.at(1, 1) * m.at(0, 2) * m.at(3, 3) + m.at(0, 1) * m.at(1, 2) * m.at(3, 3);
    ret.at(1, 2) = m.at(3, 0) * m.at(1, 2) * m.at(0, 3) - m.at(1, 0) * m.at(3, 2) * m.at(0, 3) -
                   m.at(3, 0) * m.at(0, 2) * m.at(1, 3) + m.at(0, 0) * m.at(3, 2) * m.at(1, 3) +
                   m.at(1, 0) * m.at(0, 2) * m.at(3, 3) - m.at(0, 0) * m.at(1, 2) * m.at(3, 3);
    ret.at(2, 2) = m.at(1, 0) * m.at(3, 1) * m.at(0, 3) - m.at(3, 0) * m.at(1, 1) * m.at(0, 3) +
                   m.at(3, 0) * m.at(0, 1) * m.at(1, 3) - m.at(0, 0) * m.at(3, 1) * m.at(1, 3) -
                   m.at(1, 0) * m.at(0, 1) * m.at(3, 3) + m.at(0, 0) * m.at(1, 1) * m.at(3, 3);
    ret.at(3, 2) = m.at(3, 0) * m.at(1, 1) * m.at(0, 2) - m.at(1, 0) * m.at(3, 1) * m.at(0, 2) -
                   m.at(3, 0) * m.at(0, 1) * m.at(1, 2) + m.at(0, 0) * m.at(3, 1) * m.at(1, 2) +
                   m.at(1, 0) * m.at(0, 1) * m.at(3, 2) - m.at(0, 0) * m.at(1, 1) * m.at(3, 2);
    ret.at(0, 3) = m.at(2, 1) * m.at(1, 2) * m.at(0, 3) - m.at(1, 1) * m.at(2, 2) * m.at(0, 3) -
                   m.at(2, 1) * m.at(0, 2) * m.at(1, 3) + m.at(0, 1) * m.at(2, 2) * m.at(1, 3) +
                   m.at(1, 1) * m.at(0, 2) * m.at(2, 3) - m.at(0, 1) * m.at(1, 2) * m.at(2, 3);
    ret.at(1, 3) = m.at(1, 0) * m.at(2, 2) * m.at(0, 3) - m.at(2, 0) * m.at(1, 2) * m.at(0, 3) +
                   m.at(2, 0) * m.at(0, 2) * m.at(1, 3) - m.at(0, 0) * m.at(2, 2) * m.at(1, 3) -
                   m.at(1, 0) * m.at(0, 2) * m.at(2, 3) + m.at(0, 0) * m.at(1, 2) * m.at(2, 3);
    ret.at(2, 3) = m.at(2, 0) * m.at(1, 1) * m.at(0, 3) - m.at(1, 0) * m.at(2, 1) * m.at(0, 3) -
                   m.at(2, 0) * m.at(0, 1) * m.at(1, 3) + m.at(0, 0) * m.at(2, 1) * m.at(1, 3) +
                   m.at(1, 0) * m.at(0, 1) * m.at(2, 3) - m.at(0, 0) * m.at(1, 1) * m.at(2, 3);
    ret.at(3, 3) = m.at(1, 0) * m.at(2, 1) * m.at(0, 2) - m.at(2, 0) * m.at(1, 1) * m.at(0, 2) +
                   m.at(2, 0) * m.at(0, 1) * m.at(1, 2) - m.at(0, 0) * m.at(2, 1) * m.at(1, 2) -
                   m.at(1, 0) * m.at(0, 1) * m.at(2, 2) + m.at(0, 0) * m.at(1, 1) * m.at(2, 2);
    return ret / d;
}
/// transpose
template <typename T> inline void transpose(Matrix4<T> &mat) {
    Matrix4<T> ret;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            ret.at(i, j) = mat.at(j, i);
    mat = ret;
}

/// linear interpolation
template <typename T> inline Matrix4<T> lerp(const Matrix4<T> &m1, const Matrix4<T> &m2, T fact) {
    return m1 + (m2 - m1) * fact;
}

// namespace quaternion
template <typename T> inline T length(const Quaternion<T> &q) {
    return (T)sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
}

template <typename T> inline T length2(const Quaternion<T> &q) {
    return q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z;
}

template <typename T> inline void normalize(Quaternion<T> &q) {
    T len = length(q);
    q.w /= len;
    q.x /= len;
    q.y /= len;
    q.z /= len;
}

template <typename T> inline Vector3<T> axis(const Quaternion<T> &q) {
    if (fabs(q.w - 1) < VMATH_EPSILON)
        return (Vector3<T>(1, 0, 0)); // arbitrary when there is no rotation!!
    Vector3<T> axis;
    axis.x = q.x / sqrt(1 - q.w * q.w);
    axis.y = q.y / sqrt(1 - q.w * q.w);
    axis.z = q.z / sqrt(1 - q.w * q.w);
    return axis;
}

template <typename T> inline T angle(const Quaternion<T> &q) {
    return (T)(2 * acos(q.w));
}

template <typename T> Matrix3<T> rot_matrix(const Quaternion<T> &q) {
    Matrix3<T> ret;
    T xx = q.x * q.x;
    T xy = q.x * q.y;
    T xz = q.x * q.z;
    T xw = q.x * q.w;
    T yy = q.y * q.y;
    T yz = q.y * q.z;
    T yw = q.y * q.w;
    T zz = q.z * q.z;
    T zw = q.z * q.w;

    ret.at(0, 0) = 1 - 2 * (yy + zz);
    ret.at(1, 0) = 2 * (xy - zw);
    ret.at(2, 0) = 2 * (xz + yw);
    ret.at(0, 1) = 2 * (xy + zw);
    ret.at(1, 1) = 1 - 2 * (xx + zz);
    ret.at(2, 1) = 2 * (yz - xw);
    ret.at(0, 2) = 2 * (xz - yw);
    ret.at(1, 2) = 2 * (yz + xw);
    ret.at(2, 2) = 1 - 2 * (xx + yy);
    return ret;
}

template <typename T> Matrix4<T> transform(const Quaternion<T> &q) {
    Matrix4<T> ret;
    T xx = q.x * q.x;
    T xy = q.x * q.y;
    T xz = q.x * q.z;
    T xw = q.x * q.w;
    T yy = q.y * q.y;
    T yz = q.y * q.z;
    T yw = q.y * q.w;
    T zz = q.z * q.z;
    T zw = q.z * q.w;

    ret.at(0, 0) = 1 - 2 * (yy + zz);
    ret.at(1, 0) = 2 * (xy - zw);
    ret.at(2, 0) = 2 * (xz + yw);
    ret.at(3, 0) = 0;
    ret.at(0, 1) = 2 * (xy + zw);
    ret.at(1, 1) = 1 - 2 * (xx + zz);
    ret.at(2, 1) = 2 * (yz - xw);
    ret.at(3, 1) = 0;
    ret.at(0, 2) = 2 * (xz - yw);
    ret.at(1, 2) = 2 * (yz + xw);
    ret.at(2, 2) = 1 - 2 * (xx + yy);
    ret.at(3, 2) = 0;
    ret.at(0, 3) = 0;
    ret.at(1, 3) = 0;
    ret.at(2, 3) = 0;
    ret.at(3, 3) = 1;
    return ret;
}

template <typename T> inline Quaternion<T> lerp(const Quaternion<T> &q1, const Quaternion<T> &q2, T fact) {
    return Quaternion<T>((1 - fact) * q1.w + fact * q2.w, (1 - fact) * q1.x + fact * q2.x,
                         (1 - fact) * q1.y + fact * q2.y, (1 - fact) * q1.z + fact * q2.z);
}

template <typename T> inline Quaternion<T> slerp(const Quaternion<T> &q1, const Quaternion<T> &q2, T r) {
    T costheta = q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;
    // adjust signs (if necessary)
    Quaternion<T> end = q2;
    if (costheta < static_cast<T>(0.0)) {
        costheta = -costheta;
        end = -end; // Reverse all signs
    }

    // Calculate coefficients
    T sclp, sclq;
    if ((static_cast<T>(1.0) - costheta) > static_cast<T>(0.0001)) // some tolerance
    {
        // Standard case (slerp)
        T theta, sintheta;
        theta = acos(costheta); // extract theta from dot product's cos theta
        sintheta = sin(theta);
        sclp = sin((static_cast<T>(1.0) - r) * theta) / sintheta;
        sclq = sin(r * theta) / sintheta;
    } else {
        // Very close, do linear interp (because it's faster)
        sclp = static_cast<T>(1.0) - r;
        sclq = r;
    }

    Quaternion<T> out;
    out.x = sclp * q1.x + sclq * end.x;
    out.y = sclp * q1.y + sclq * end.y;
    out.z = sclp * q1.z + sclq * end.z;
    out.w = sclp * q1.w + sclq * end.w;

    return out;
}

// ///////// //
// factories //
// ///////// //

namespace factory {

// create an identity matrix
template <typename T> Matrix3<T> matrix3_identity() {
    Matrix3<T> m;
    for (int i = 0; i < 9; i++)
        m.data[i] = (i % 4) ? T(0) : T(1);
    return m;
}

// create an identity matrix
template <typename T> Matrix4<T> matrix4_identity() {
    Matrix3<T> m;
    for (int i = 0; i < 16; i++)
        m.data[i] = (i % 5) ? T(0) : T(1);
    return m;
}

/// create a translation matrix
template <typename T> Matrix4<T> create_translation(const Vector3<T> &v) {
    Matrix4<T> ret;
    set_translation(ret, v);
    return ret;
}

/// create a transformation matrix
template <typename T> Matrix4<T> create_transformation(const Vector3<T> &v, const Quaternion<T> &q) {
    Matrix4<T> ret = transform(q);
    set_translation(ret, v);
    return ret;
}

template <typename T> Matrix4<T> create_lookat(const Vector3<T> &eye, const Vector3<T> &to, const Vector3<T> &up) {
    // set rotation using axis/angle
    Vector3<T> z(eye - to);
    normalize(z);
    Vector3<T> x = up.cross(z);
    normalize(x);
    Vector3<T> y = z.cross(x);

    Matrix4<T> m = create_translation(eye);
    m(1, 1) = x.x;
    m(1, 2) = y.x;
    m(1, 3) = z.x;
    m(2, 1) = x.y;
    m(2, 2) = y.y;
    m(2, 3) = z.y;
    m(3, 1) = x.z;
    m(3, 2) = y.z;
    m(3, 3) = z.z;

    return m;
}

template <typename T> inline Quaternion<T> quat_from_euler_321(T x, T y, T z) {
    Quaternion<T> ret = quat_from_axis_angle(Vector3<T>(1, 0, 0), x) * quat_from_axis_angle(Vector3<T>(0, 1, 0), y) *
                        quat_from_axis_angle(Vector3<T>(0, 0, 1), z);
    return ret;
}

template <typename T> inline Quaternion<T> quat_from_axis_angle(Vector3<T> axis, T angle) {
    T sa2 = (T)sin(angle / 2);
    T ca2 = (T)cos(angle / 2);
    return Quaternion<T>(ca2, axis.x * sa2, axis.y * sa2, axis.z * sa2);
}

template <typename T> Quaternion<T> quat_from_matrix(const Matrix4<T> &m) {
    Quaternion<T> q;

    T tr, s;
    tr = m(1, 1) + m(2, 2) + m(3, 3);
    if (tr >= VMATH_EPSILON) {
        s = (T)(0.5 / sqrt(tr + 1.0));
        q.w = (T)(0.25 / s);
        q.x = (m(3, 2) - m(2, 3)) * s;
        q.y = (m(1, 3) - m(3, 1)) * s;
        q.z = (m(2, 1) - m(1, 2)) * s;
    } else {
        T d0 = m(1, 1);
        T d1 = m(2, 2);
        T d2 = m(3, 3);

        char bigIdx = (d0 > d1) ? ((d0 > d2) ? 0 : 2) : ((d1 > d2) ? 1 : 2);

        if (bigIdx == 0) {
            s = (T)(2.0 * sqrt(1.0 + m(1, 1) - m(2, 2) - m(3, 3)));
            q.w = (m(3, 2) - m(2, 3)) / s;
            q.x = (T)(0.25 * s);
            q.y = (m(1, 2) + m(2, 1)) / s;
            q.z = (m(1, 3) + m(3, 1)) / s;
        } else if (bigIdx == 1) {
            s = (T)(2.0 * sqrt(1.0 + m(2, 2) - m(1, 1) - m(3, 3)));
            q.w = (m(1, 3) - m(3, 1)) / s;
            q.x = (m(1, 2) + m(2, 1)) / s;
            q.y = (T)(0.25 * s);
            q.z = (m(2, 3) + m(3, 2)) / s;
        } else {
            s = (T)(2.0 * sqrt(1.0 + m(3, 3) - m(1, 1) - m(2, 2)));
            q.w = (m(2, 1) - m(1, 2)) / s;
            q.x = (m(1, 3) + m(3, 1)) / s;
            q.y = (m(2, 3) + m(3, 2)) / s;
            q.z = (T)(0.25 * s);
        }
    }

    return q;
}

template <typename T> Quaternion<T> quat_from_matrix(const Matrix3<T> &m) {
    Quaternion<T> q;

    T tr, s;
    tr = m(1, 1) + m(2, 2) + m(3, 3);
    if (tr >= VMATH_EPSILON) {
        s = T(0.5) / (T)sqrt(tr + 1.0);
        q.w = T(0.25) / s;
        q.x = (m(3, 2) - m(2, 3)) * s;
        q.y = (m(1, 3) - m(3, 1)) * s;
        q.z = (m(2, 1) - m(1, 2)) * s;
    } else {
        T d0 = m(1, 1);
        T d1 = m(2, 2);
        T d2 = m(3, 3);

        char bigIdx = (d0 > d1) ? ((d0 > d2) ? 0 : 2) : ((d1 > d2) ? 1 : 2);

        if (bigIdx == 0) {
            s = T(2.0) * (T)sqrt(1.0 + m(1, 1) - m(2, 2) - m(3, 3));
            q.w = (m(3, 2) - m(2, 3)) / s;
            q.x = T(0.25) * s;
            q.y = (m(1, 2) + m(2, 1)) / s;
            q.z = (m(1, 3) + m(3, 1)) / s;
        } else if (bigIdx == 1) {
            s = T(2.0) * (T)sqrt(1.0 + m(2, 2) - m(1, 1) - m(3, 3));
            q.w = (m(1, 3) - m(3, 1)) / s;
            q.x = (m(1, 2) + m(2, 1)) / s;
            q.y = T(0.25) * s;
            q.z = (m(2, 3) + m(3, 2)) / s;
        } else {
            s = T(2.0) * (T)sqrt(1.0 + m(3, 3) - m(1, 1) - m(2, 2));
            q.w = (m(2, 1) - m(1, 2)) / s;
            q.x = (m(1, 3) + m(3, 1)) / s;
            q.y = (m(2, 3) + m(3, 2)) / s;
            q.z = T(0.25) * s;
        }
    }
    return q;
}

} // namespace factory

} // namespace math
