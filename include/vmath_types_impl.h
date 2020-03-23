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

#define VMATH_EPSILON (4.37114e-07)

namespace math {

//--------------------------------------
// Implementation
//--------------------------------------

// Vector2<T> implementation

template <typename T>
inline Vector2<T>::Vector2()
: x(0)
, y(0) {}

template <typename T>
inline Vector2<T>::Vector2(T _x, T _y)
: x(_x)
, y(_y) {}

template <typename T>
inline Vector2<T>::Vector2(const Vector2<T> &src)
: x(src.x)
, y(src.y) {}

template <typename T> inline Vector2<T> &Vector2<T>::operator=(const Vector2<T> &rhs) {
    x = rhs.x;
    y = rhs.y;
    return *this;
}

template <typename T> inline T &Vector2<T>::operator[](int n) {
    assert(n >= 0 && n <= 1);
    if (0 == n)
        return x;
    else
        return y;
}

template <typename T> inline const T &Vector2<T>::operator[](int n) const {
    assert(n >= 0 && n <= 1);
    if (0 == n)
        return x;
    else
        return y;
}

template <typename T> inline Vector2<T> Vector2<T>::operator+(const Vector2<T> &rhs) const {
    return Vector2<T>(x + rhs.x, y + rhs.y);
}

template <typename T> inline Vector2<T> Vector2<T>::operator-(const Vector2<T> &rhs) const {
    return Vector2<T>(x - rhs.x, y - rhs.y);
}

template <typename T> inline void Vector2<T>::operator+=(const Vector2<T> &rhs) {
    x += rhs.x;
    y += rhs.y;
}

template <typename T> inline void Vector2<T>::operator-=(const Vector2<T> &rhs) {
    x -= rhs.x;
    y -= rhs.y;
}

template <typename T> inline T Vector2<T>::dot(const Vector2<T> &rhs) const {
    return x * rhs.x + y * rhs.y;
}

template <typename T> inline void Vector2<T>::operator+=(T rhs) {
    x += rhs;
    y += rhs;
}

template <typename T> inline void Vector2<T>::operator-=(T rhs) {
    x -= rhs;
    y -= rhs;
}

template <typename T> inline void Vector2<T>::operator*=(T rhs) {
    x *= rhs;
    y *= rhs;
}

template <typename T> inline void Vector2<T>::operator/=(T rhs) {
    x /= rhs;
    y /= rhs;
}

template <typename T> inline bool Vector2<T>::operator==(const Vector2<T> &rhs) const {
    return (fabs(x - rhs.x) < VMATH_EPSILON) && (fabs(y - rhs.y) < VMATH_EPSILON);
}

template <typename T> inline bool Vector2<T>::operator!=(const Vector2<T> &rhs) const {
    return !(*this == rhs);
}

template <typename T> inline Vector2<T> Vector2<T>::operator-() const {
    return Vector2<T>(-x, -y);
}


// Vector3<T> implementation //

template <typename T>
inline Vector3<T>::Vector3()
: x(0)
, y(0)
, z(0) {}

template <typename T>
inline Vector3<T>::Vector3(T nx, T ny, T nz)
: x(nx)
, y(ny)
, z(nz) {}

template <typename T>
inline Vector3<T>::Vector3(const Vector3<T> &src)
: x(src.x)
, y(src.y)
, z(src.z) {}

template <typename T> inline Vector3<T> &Vector3<T>::operator=(const Vector3<T> &rhs) {
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    return *this;
}

template <typename T> inline T &Vector3<T>::operator[](int n) {
    assert(n >= 0 && n <= 2);
    if (0 == n)
        return x;
    else if (1 == n)
        return y;
    else
        return z;
}

template <typename T> inline const T &Vector3<T>::operator[](int n) const {
    assert(n >= 0 && n <= 2);
    if (0 == n)
        return x;
    else if (1 == n)
        return y;
    else
        return z;
}

template <typename T> inline Vector3<T> Vector3<T>::operator+(const Vector3<T> &rhs) const {
    return Vector3<T>(x + rhs.x, y + rhs.y, z + rhs.z);
}

template <typename T> inline Vector3<T> Vector3<T>::operator-(const Vector3<T> &rhs) const {
    return Vector3<T>(x - rhs.x, y - rhs.y, z - rhs.z);
}

template <typename T> inline void Vector3<T>::operator+=(const Vector3<T> &rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
}

template <typename T> inline void Vector3<T>::operator-=(const Vector3<T> &rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
}

template <typename T> inline T Vector3<T>::dot(const Vector3<T> &rhs) const {
    return x * rhs.x + y * rhs.y + z * rhs.z;
}

template <typename T> inline Vector3<T> Vector3<T>::cross(const Vector3<T> &rhs) const {
    return Vector3<T>(y * rhs.z - rhs.y * z, z * rhs.x - rhs.z * x, x * rhs.y - rhs.x * y);
}

template <typename T> inline void Vector3<T>::operator+=(T rhs) {
    x += rhs;
    y += rhs;
    z += rhs;
}

template <typename T> inline void Vector3<T>::operator-=(T rhs) {
    x -= rhs;
    y -= rhs;
    z -= rhs;
}

template <typename T> inline void Vector3<T>::operator*=(T rhs) {
    x *= rhs;
    y *= rhs;
    z *= rhs;
}

template <typename T> inline void Vector3<T>::operator/=(T rhs) {
    x /= rhs;
    y /= rhs;
    z /= rhs;
}

template <typename T> inline bool Vector3<T>::operator==(const Vector3<T> &rhs) const {
    return fabs(x - rhs.x) < VMATH_EPSILON && fabs(y - rhs.y) < VMATH_EPSILON && fabs(z - rhs.z) < VMATH_EPSILON;
}

template <typename T> inline bool Vector3<T>::operator!=(const Vector3<T> &rhs) const {
    return !(*this == rhs);
}

template <typename T> inline Vector3<T> Vector3<T>::operator-() const {
    return Vector3<T>(-x, -y, -z);
}

// Vector4<T> implementation

template <typename T>
inline Vector4<T>::Vector4()
: x(0)
, y(0)
, z(0)
, w(0) {}

template <typename T>
inline Vector4<T>::Vector4(T nx, T ny, T nz, T nw)
: x(nx)
, y(ny)
, z(nz)
, w(nw) {}

template <typename T>
inline Vector4<T>::Vector4(const Vector4<T> &src)
: x(src.x)
, y(src.y)
, z(src.z)
, w(src.w) {}

template <typename T> inline Vector4<T> &Vector4<T>::operator=(const Vector4<T> &rhs) {
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    w = rhs.w;
    return *this;
}

template <typename T> inline T &Vector4<T>::operator[](int n) {
    assert(n >= 0 && n <= 3);
    if (0 == n)
        return x;
    else if (1 == n)
        return y;
    else if (2 == n)
        return z;
    else
        return w;
}

template <typename T> inline const T &Vector4<T>::operator[](int n) const {
    assert(n >= 0 && n <= 3);
    if (0 == n)
        return x;
    else if (1 == n)
        return y;
    else if (2 == n)
        return z;
    else
        return w;
}

template <typename T> inline Vector4<T> Vector4<T>::operator+(const Vector4<T> &rhs) const {
    return Vector4<T>(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}

template <typename T> inline Vector4<T> Vector4<T>::operator-(const Vector4<T> &rhs) const {
    return Vector4<T>(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}

template <typename T> inline void Vector4<T>::operator+=(const Vector4<T> &rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    w += rhs.w;
}

template <typename T> inline void Vector4<T>::operator-=(const Vector4<T> &rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    w -= rhs.w;
}

template <typename T> inline T Vector4<T>::dot(const Vector4<T> &rhs) const {
    return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
}


template <typename T> inline bool Vector4<T>::operator==(const Vector4<T> &rhs) const {
    return fabs(x - rhs.x) < VMATH_EPSILON && fabs(y - rhs.y) < VMATH_EPSILON && fabs(z - rhs.z) < VMATH_EPSILON &&
           fabs(w - rhs.w) < VMATH_EPSILON;
}

template <typename T> inline bool Vector4<T>::operator!=(const Vector4<T> &rhs) const {
    return !(*this == rhs);
}

template <typename T> inline Vector4<T> Vector4<T>::operator-() const {
    return Vector4<T>(-x, -y, -z, -w);
}

template <typename T> inline void Vector4<T>::operator+=(T rhs) {
    x += rhs;
    y += rhs;
    z += rhs;
    w += rhs;
}

template <typename T> inline void Vector4<T>::operator-=(T rhs) {
    x -= rhs;
    y -= rhs;
    z -= rhs;
    w -= rhs;
}

template <typename T> inline void Vector4<T>::operator*=(T rhs) {
    x *= rhs;
    y *= rhs;
    z *= rhs;
    w *= rhs;
}

template <typename T> inline void Vector4<T>::operator/=(T rhs) {
    x /= rhs;
    y /= rhs;
    z /= rhs;
    w /= rhs;
}

// Matrix3<T> implementation

template <typename T>
inline Matrix3<T>::Matrix3() ///< default to identity matrix
{
    for (int i = 0; i < 9; i++)
        data[i] = (i % 4) ? T(0) : T(1);
}

template <typename T> inline Matrix3<T>::Matrix3(const Matrix3<T> &src) {
    std::memcpy(data, src.data, sizeof(T) * 9);
}

template <typename T> inline Matrix3<T>::Matrix3(const T *dt) {
    for (int k=0; k<9; k++) {
        data[k] = dt[(k%3)*3 + k/3];
    }
}

template <typename T> inline Matrix3<T>::Matrix3(std::initializer_list<T> init) {
    assert(init.size()>=9);
    const T *v = init.begin();
    for (int k=0; k<9; k++) {
        data[k] = v[(k%3)*3 + k/3];
    }
}

template <typename T> inline bool Matrix3<T>::operator==(const Matrix3<T> &rhs) const {
    for (int i = 0; i < 9; i++)
        if (fabs(data[i] - rhs.data[i]) >= VMATH_EPSILON)
            return false;
    return true;
}

template <typename T> inline bool Matrix3<T>::operator!=(const Matrix3<T> &rhs) const {
    return !(*this == rhs);
}

template <typename T> inline T &Matrix3<T>::operator()(int i, int j) {
    assert(i >= 0 && i < 3);
    assert(j >= 0 && j < 3);
    return data[j * 3 + i];
}

template <typename T> inline const T &Matrix3<T>::operator()(int i, int j) const {
    assert(i >= 0 && i < 3);
    assert(j >= 0 && j < 3);
    return data[j * 3 + i];
}

template <typename T> inline T &Matrix3<T>::at(int x, int y) {
    assert(x >= 0 && x < 3);
    assert(y >= 0 && y < 3);
    return data[x * 3 + y];
}

template <typename T> inline const T &Matrix3<T>::at(int x, int y) const {
    assert(x >= 0 && x < 3);
    assert(y >= 0 && y < 3);
    return data[x * 3 + y];
}

template <typename T> inline Matrix3<T> &Matrix3<T>::operator=(const Matrix3<T> &rhs) {
    std::memcpy(data, rhs.data, sizeof(T) * 9);
    return *this;
}

template <typename T> inline void Matrix3<T>::operator+=(T rhs) {
    for (int i = 0; i < 9; i++)
        data[i] += rhs;
}

template <typename T> inline void Matrix3<T>::operator-=(T rhs) {
    for (int i = 0; i < 9; i++)
        data[i] -= rhs;
}

template <typename T> inline void Matrix3<T>::operator*=(T rhs) {
    for (int i = 0; i < 9; i++)
        data[i] *= rhs;
}

template <typename T> inline void Matrix3<T>::operator/=(T rhs) {
    for (int i = 0; i < 9; i++)
        data[i] /= rhs;
}


// Matrix4<T> implementation

template <typename T>
inline Matrix4<T>::Matrix4() // default to identity
{
    for (int i = 0; i < 16; i++)
        data[i] = (i % 5) ? T(0) : T(1);
}

template <typename T> inline Matrix4<T>::Matrix4(const T *dt) {
    for (int k=0; k<16; k++) {
        data[k] = dt[(k%4)*4 + k/4];
    }
}

template <typename T> inline Matrix4<T>::Matrix4(std::initializer_list<T> init) {
    assert(init.size()>=16);
    const T *v = init.begin();
    for (int k=0; k<16; k++) {
        data[k] = v[(k%4)*4 + k/4];
    }
}


template <typename T> inline Matrix4<T>::Matrix4(const Matrix4<T> &src) {
    std::memcpy(data, src.data, 16 * sizeof(T));
}

template <typename T> inline bool Matrix4<T>::operator==(const Matrix4<T> &rhs) const {
    for (int i = 0; i < 16; i++) {
        if (fabs(data[i] - rhs.data[i]) >= VMATH_EPSILON)
            return false;
    }
    return true;
}

template <typename T> inline bool Matrix4<T>::operator!=(const Matrix4<T> &rhs) const {
    return !(*this == rhs);
}

template <typename T> inline T &Matrix4<T>::at(int x, int y) {
    assert(x >= 0 && x < 4);
    assert(y >= 0 && y < 4);
    return data[x * 4 + y];
}

template <typename T> inline const T &Matrix4<T>::at(int x, int y) const {
    assert(x >= 0 && x < 4);
    assert(y >= 0 && y < 4);
    return data[x * 4 + y];
}

template <typename T> inline T &Matrix4<T>::operator()(int i, int j) {
    assert(i >= 0 && i < 4);
    assert(j >= 0 && j < 4);
    return data[j * 4 + i];
}

template <typename T> inline const T &Matrix4<T>::operator()(int i, int j) const {
    assert(i >= 0 && i < 4);
    assert(j >= 0 && j < 4);
    return data[j * 4 + i];
}

template <typename T> inline Matrix4<T> &Matrix4<T>::operator=(const Matrix4<T> &rhs) {
    std::memcpy(data, rhs.data, 16 * sizeof(T));
    return *this;
}

template <typename T> inline void Matrix4<T>::operator+=(T rhs) {
    for (int i = 0; i < 16; i++)
        data[i] += rhs;
}

template <typename T> inline void Matrix4<T>::operator-=(T rhs) {
    for (int i = 0; i < 16; i++)
        data[i] -= rhs;
}

template <typename T> inline void Matrix4<T>::operator*=(T rhs) {
    for (int i = 0; i < 16; i++)
        data[i] *= rhs;
}

template <typename T> inline void Matrix4<T>::operator/=(T rhs) {
    for (int i = 0; i < 16; i++)
        data[i] /= rhs;
}


// Quaternion<T> implementation

template <typename T>
inline Quaternion<T>::Quaternion()
: w(0)
, v(0, 0, 0) {}

template <typename T>
inline Quaternion<T>::Quaternion(const Quaternion<T> &q)
: w(q.w)
, v(q.v) {}

template <typename T>
inline Quaternion<T>::Quaternion(T w_, const Vector3<T> &v_)
: w(w_)
, v(v_) {}

template <typename T>
inline Quaternion<T>::Quaternion(T w_, T x, T y, T z)
: w(w_)
, v(x, y, z) {}

template <typename T> inline Quaternion<T> &Quaternion<T>::operator=(const Quaternion<T> &rhs) {
    v = rhs.v;
    w = rhs.w;
    return *this;
}

template <typename T> inline Quaternion<T> Quaternion<T>::operator+(const Quaternion<T> &rhs) const {
    const Quaternion<T> &lhs = *this;
    return Quaternion<T>(lhs.w + rhs.w, lhs.v + rhs.v);
}

template <typename T> inline Quaternion<T> Quaternion<T>::operator*(const Quaternion<T> &rhs) const {
    const Quaternion<T> &lhs = *this;
    return Quaternion<T>(lhs.w * rhs.w - lhs.v.x * rhs.v.x - lhs.v.y * rhs.v.y - lhs.v.z * rhs.v.z,
                         lhs.w * rhs.v.x + lhs.v.x * rhs.w + lhs.v.y * rhs.v.z - lhs.v.z * rhs.v.y,
                         lhs.w * rhs.v.y - lhs.v.x * rhs.v.z + lhs.v.y * rhs.w + lhs.v.z * rhs.v.x,
                         lhs.w * rhs.v.z + lhs.v.x * rhs.v.y - lhs.v.y * rhs.v.x + lhs.v.z * rhs.w);
}

template <typename T> inline Quaternion<T> Quaternion<T>::operator-(const Quaternion<T> &rhs) const {
    const Quaternion<T> &lhs = *this;
    return Quaternion<T>(lhs.w - rhs.w, lhs.v - rhs.v);
}

template <typename T> inline void Quaternion<T>::operator+=(const Quaternion<T> &rhs) {
    w += rhs.w;
    v += rhs.v;
}

template <typename T> inline void Quaternion<T>::operator-=(const Quaternion<T> &rhs) {
    w -= rhs.w;
    v -= rhs.v;
}

template <typename T> inline void Quaternion<T>::operator*=(const Quaternion<T> &rhs) {
    Quaternion q = (*this) * rhs;
    v = q.v;
    w = q.w;
}

template <typename T> inline Quaternion<T> Quaternion<T>::operator*(T rhs) const {
    return Quaternion<T>(w * rhs, v * rhs);
}

template <typename T> inline void Quaternion<T>::operator*=(T rhs) {
    w *= rhs;
    v *= rhs;
}

template <typename T> inline bool Quaternion<T>::operator==(const Quaternion<T> &rhs) const {
    const Quaternion<T> &lhs = *this;
    return (fabs(lhs.w - rhs.w) < VMATH_EPSILON) && lhs.v == rhs.v;
}

template <typename T> inline bool Quaternion<T>::operator!=(const Quaternion<T> &rhs) const {
    return !(*this == rhs);
}

template <typename T> inline Quaternion<T> Quaternion<T>::operator-() const {
    return Quaternion<T>(-w, -v);
}

template <typename T> inline Quaternion<T> Quaternion<T>::operator~() const {
    return Quaternion<T>(w, -v);
}

template <typename T> inline Vector3<T> Quaternion<T>::operator*(const Vector3<T> &vec) const {
    // implements: res = rot*point* ~rot
    // where rot is the quaternion and point a quat where v.x/y/z contains point coords

    T rw = w * 0 - v.x * vec.x - v.y * vec.y - v.z * vec.z;
    T rx = w * vec.x + v.x * 0 + v.y * vec.z - v.z * vec.y;
    T ry = w * vec.y - v.x * vec.z + v.y * 0 + v.z * vec.x;
    T rz = w * vec.z + v.x * vec.y - v.y * vec.x + v.z * 0;
    // w coord is: rw*w   - rx*v.x - ry*v.y - rz*v.z
    return Vector3<T>(-rw * v.x + rx * w - ry * v.z + rz * v.y, -rw * v.y + rx * v.z + ry * w - rz * v.x,
                      -rw * v.z - rx * v.y + ry * v.x + rz * w);
}

template <typename T> inline Vector4<T> Quaternion<T>::operator*(const Vector4<T> &vec) const {
    // implements: res = rot*point* ~rot
    // where rot is the quaternion and point a quat where v.x/y/z contains point coords

    T rw = w * 0 - v.x * vec.x - v.y * vec.y - v.z * vec.z;
    T rx = w * vec.x + v.x * 0 + v.y * vec.z - v.z * vec.y;
    T ry = w * vec.y - v.x * vec.z + v.y * 0 + v.z * vec.x;
    T rz = w * vec.z + v.x * vec.y - v.y * vec.x + v.z * 0;
    // w coord is: rw*w   - rx*v.x - ry*v.y - rz*v.z
    return Vector4<T>(-rw * v.x + rx * w - ry * v.z + rz * v.y, -rw * v.y + rx * v.z + ry * w - rz * v.x,
                      -rw * v.z - rx * v.y + ry * v.x + rz * w,
                      vec.w); // last component kept from source
}

} // namespace math
