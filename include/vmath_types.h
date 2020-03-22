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
/// 2D Vector.
/// fields can be addressed with math names (x,y) or texture-lookup names (s,t)
template <typename T> struct Vector2 {
    union {
        T x;
        T s;
    };
    union {
        T y;
        T t;
    };

    // constructors
    Vector2();
    Vector2(T _x, T _y);
    Vector2(const Vector2<T> &src);
    template <typename fromT>
    Vector2(const fromT &src)
    : x(static_cast<T>(src.x))
    , y(static_cast<T>(src.y)) {}

    // assignment operators
    Vector2<T> &operator=(const Vector2<T> &rhs);
    template <typename fromT> Vector2<T> &operator=(const fromT &rhs) {
        x = static_cast<T>(rhs.x);
        y = static_cast<T>(rhs.y);
        return *this;
    }
    // access operators
    T &operator[](int n);
    const T &operator[](int n) const;
    // vector operations
    Vector2<T> operator+(const Vector2<T> &rhs) const;
    Vector2<T> operator-(const Vector2<T> &rhs) const;
    void operator+=(const Vector2<T> &rhs);
    void operator-=(const Vector2<T> &rhs);
    T dot(const Vector2<T> &rhs) const;
    // scalar operations
    Vector2<T> operator+(T rhs) const;
    Vector2<T> operator-(T rhs) const;
    Vector2<T> operator*(T rhs) const;
    Vector2<T> operator/(T rhs) const;
    void operator+=(T rhs);
    void operator-=(T rhs);
    void operator*=(T rhs);
    void operator/=(T rhs);
    // comparison
    bool operator==(const Vector2<T> &rhs) const;
    bool operator!=(const Vector2<T> &rhs) const;
    // unary operators
    Vector2<T> operator-() const;
    // conversion to pointer operator (for passing the instance as a T*)
    operator T *() { return (T *)this; }
    operator const T *() const { return (const T *)this; }
};

/// 3D vector
template <typename T> struct Vector3 {
    union {
        T x;
        T s;
        T r;
    };
    union {
        T y;
        T t;
        T g;
    };
    union {
        T z;
        T u;
        T b;
    };

    // constructors
    Vector3();
    Vector3(T nx, T ny, T nz);
    Vector3(const Vector3<T> &src);
    template <typename fromT>
    Vector3(const fromT &src)
    : x(static_cast<T>(src.x))
    , y(static_cast<T>(src.y))
    , z(static_cast<T>(src.z)) {}
    // assignment operators
    Vector3<T> &operator=(const Vector3<T> &rhs);
    template <typename fromT> Vector3<T> &operator=(const fromT &rhs) {
        x = static_cast<T>(rhs.x);
        y = static_cast<T>(rhs.y);
        z = static_cast<T>(rhs.z);
        return *this;
    }
    // access operators
    T &operator[](int n);
    const T &operator[](int n) const;
    // vector operators
    Vector3<T> operator+(const Vector3<T> &rhs) const;
    Vector3<T> operator-(const Vector3<T> &rhs) const;
    void operator+=(const Vector3<T> &rhs);
    void operator-=(const Vector3<T> &rhs);
    T dot(const Vector3<T> &rhs) const;
    Vector3<T> cross(const Vector3<T> &rhs) const;
    // scalar operators
    Vector3<T> operator+(T rhs) const;
    Vector3<T> operator-(T rhs) const;
    Vector3<T> operator*(T rhs) const;
    Vector3<T> operator/(T rhs) const;
    void operator+=(T rhs);
    void operator-=(T rhs);
    void operator*=(T rhs);
    void operator/=(T rhs);
    // comparison
    bool operator==(const Vector3<T> &rhs) const;
    bool operator!=(const Vector3<T> &rhs) const;
    // unary operators
    Vector3<T> operator-() const;
    // conversion to pointer operator (for passing the instance as a T*)
    operator T *() { return (T *)this; }
    operator const T *() const { return (const T *)this; }
};

/// 4D vector
template <typename T> struct Vector4 {
    union {
        T r;
        T x;
    };
    union {
        T g;
        T y;
    };
    union {
        T b;
        T z;
    };
    union {
        T a;
        T w;
    };

    Vector4();
    Vector4(T nx, T ny, T nz, T nw);
    Vector4(const Vector4<T> &src);
    template <typename fromT>
    Vector4(const fromT &src)
    : x(static_cast<T>(src.x))
    , y(static_cast<T>(src.y))
    , z(static_cast<T>(src.z))
    , w(static_cast<T>(src.w)) {}
    // assignment operators
    Vector4<T> operator=(const Vector4<T> &rhs);
    template <typename fromT> Vector4<T> operator=(const fromT &rhs) {
        x = static_cast<T>(rhs.x);
        y = static_cast<T>(rhs.y);
        z = static_cast<T>(rhs.z);
        w = static_cast<T>(rhs.w);
        return *this;
    }
    // access operators
    T &operator[](int n);
    const T &operator[](int n) const;
    // vector math
    Vector4<T> operator+(const Vector4<T> &rhs) const;
    Vector4<T> operator-(const Vector4<T> &rhs) const;
    void operator+=(const Vector4<T> &rhs);
    void operator-=(const Vector4<T> &rhs);
    T dot(const Vector4<T> &rhs) const;
    // comparison
    bool operator==(const Vector4<T> &rhs) const;
    bool operator!=(const Vector4<T> &rhs) const;
    // unary operators
    Vector4<T> operator-() const;
    // scalar math
    Vector4<T> operator+(T rhs) const;
    Vector4<T> operator-(T rhs) const;
    Vector4<T> operator*(T rhs) const;
    Vector4<T> operator/(T rhs) const;
    void operator+=(T rhs);
    void operator-=(T rhs);
    void operator*=(T rhs);
    void operator/=(T rhs);
    // conversion to pointer operator (for passing the instance as a T*)
    operator T *() { return (T *)this; }
    operator const T *() const { return (const T *)this; }
};

/// 3x3 Matrix
/// @note data is stored in column major order (same as opengl, to enforce compatibility)
template <typename T> struct Matrix3 {
    T data[9]; ///< values (stored in column-major order)

    // constructors
    Matrix3();
    Matrix3(const Matrix3<T> &src);
    Matrix3(const T *dt);
    template <typename fromT> Matrix3(const Matrix3<fromT> &src) {
        for (int i = 0; i < 9; i++)
            data[i] = static_cast<T>(src.data[i]);
    }
    // comparison
    bool operator==(const Matrix3<T> &rhs) const;
    bool operator!=(const Matrix3<T> &rhs) const;
    /// element at position (x,y): (column,row), 0..2
    T &at(int x, int y);
    const T &at(int x, int y) const;
    /// element at position (i,j), with linear algebra matrix notation (row,column), 1..3
    /// @param i row (1..3)
    /// @param j column (1..3)
    T &operator()(int i, int j);
    const T &operator()(int i, int j) const;
    // assignment operators
    Matrix3<T> &operator=(const Matrix3<T> &rhs);
    template <typename fromT> Matrix3<T> &operator=(const Matrix3<fromT> &rhs) {
        for (int i = 0; i < 9; i++)
            data[i] = static_cast<T>(rhs.data[i]);
        return *this;
    }

    Matrix3<T> &operator=(const T *rhs);
    // matrix operations
    Matrix3<T> operator+(const Matrix3<T> &rhs) const;
    Matrix3<T> operator-(const Matrix3<T> &rhs) const;
    Matrix3<T> operator*(Matrix3<T> rhs) const;
    // scalar operations
    Matrix3<T> operator+(T rhs) const;
    Matrix3<T> operator-(T rhs) const;
    Matrix3<T> operator*(T rhs) const;
    Matrix3<T> operator/(T rhs) const;
    void operator+=(T rhs);
    void operator-=(T rhs);
    void operator*=(T rhs);
    void operator/=(T rhs);
    // vector operations
    Vector3<T> operator*(const Vector3<T> &rhs) const;
    // conversion to pointer operator (for passing the instance as a T*)
    operator T *() { return (T *)data; }
    operator const T *() const { return (const T *)data; }
};

/// 4x4 Matrix
/// @note data is stored in column major order.
template <typename T> struct Matrix4 {
    T data[16]; ///< data stored in column major order

    Matrix4();
    Matrix4(const T *dt);
    Matrix4(const Matrix4<T> &src);
    template <typename fromT> Matrix4(const Matrix4<fromT> &src) {
        for (int i = 0; i < 16; i++)
            data[i] = static_cast<T>(src.data[i]);
    }
    // comparison
    bool operator==(const Matrix4<T> &rhs) const;
    bool operator!=(const Matrix4<T> &rhs) const;
    // access operators
    /// element at position (x,y): (column,row), 0..3
    T &at(int x, int y);
    const T &at(int x, int y) const;
    /// element at position (i,j), with linear algebra matrix notation (row,column), 1..4
    /// @param i row (1..4)
    /// @param j column (1..4)
    T &operator()(int i, int j);
    const T &operator()(int i, int j) const;
    // assignment
    Matrix4<T> &operator=(const Matrix4<T> &rhs);
    template <typename fromT> Matrix4<T> &operator=(const Matrix4<fromT> &rhs) {
        for (int i = 0; i < 16; i++)
            data[i] = static_cast<T>(rhs.data[i]);
        return *this;
    }
    // matrix operations
    Matrix4<T> operator+(const Matrix4<T> &rhs) const;
    Matrix4<T> operator-(const Matrix4<T> &rhs) const;
    Matrix4<T> operator*(Matrix4<T> rhs) const;
    // scalar operations
    Matrix4<T> operator+(T rhs) const;
    Matrix4<T> operator-(T rhs) const;
    Matrix4<T> operator*(T rhs) const;
    Matrix4<T> operator/(T rhs) const;
    void operator+=(T rhs);
    void operator-=(T rhs);
    void operator*=(T rhs);
    void operator/=(T rhs);
    // vector operators
    Vector4<T> operator*(const Vector4<T> &rhs) const;
    Vector3<T> operator*(const Vector3<T> &rhs) const;
    // conversion to pointer operator (for passing the instance as a T*)
    operator T *() { return (T *)data; }
    operator const T *() const { return (const T *)data; }
};

/// Quaternion
template <typename T> struct Quaternion {
    T w;          ///< real part
    Vector3<T> v; ///< imaginary components

    Quaternion();
    Quaternion(const Quaternion<T> &q);
    template <typename fromT>
    Quaternion(const Quaternion<fromT> &q)
    : w(static_cast<T>(q.w))
    , v(q.v) {}

    Quaternion(T w_, const Vector3<T> &v_);
    Quaternion(T w_, T x, T y, T z);
    // assignment
    Quaternion<T> &operator=(const Quaternion<T> &rhs);
    template <typename fromT> Quaternion<T> &operator=(const Quaternion<fromT> &rhs) {
        w = static_cast<T>(rhs.w);
        v.x = static_cast<T>(rhs.v.x);
        v.y = static_cast<T>(rhs.v.y);
        v.z = static_cast<T>(rhs.v.z);
        return *this;
    }
    // quaternion algebra
    Quaternion<T> operator+(const Quaternion<T> &rhs) const;
    Quaternion<T> operator*(const Quaternion<T> &rhs) const;
    Quaternion<T> operator-(const Quaternion<T> &rhs) const;
    void operator+=(const Quaternion<T> &rhs);
    void operator-=(const Quaternion<T> &rhs);
    void operator*=(const Quaternion<T> &rhs);
    // scalar operations
    Quaternion<T> operator*(T rhs) const;
    void operator*=(T rhs);
    // comparison
    bool operator==(const Quaternion<T> &rhs) const;
    bool operator!=(const Quaternion<T> &rhs) const;
    // unary operators
    Quaternion<T> operator-() const;
    // conjugate operator
    Quaternion<T> operator~() const;
    // vector operators
    Vector3<T> operator*(const Vector3<T> &vec) const;
    Vector4<T> operator*(const Vector4<T> &vec) const;
};

//--------------------------------------
// shortcuts
//-------------------------------------

typedef Vector2<float> Vector2f;
typedef Vector2<double> Vector2d;
typedef Vector2<int> Vector2i;

typedef Vector3<float> Vector3f;
typedef Vector3<double> Vector3d;
typedef Vector3<int> Vector3i;

typedef Vector4<float> Vector4f;
typedef Vector4<double> Vector4d;
typedef Vector4<int> Vector4i;

typedef Matrix3<float> Matrix3f;
typedef Matrix3<double> Matrix3d;
typedef Matrix3<int> Matrix3i;

typedef Matrix4<float> Matrix4f;
typedef Matrix4<double> Matrix4d;
typedef Matrix4<int> Matrix4i;

typedef Quaternion<float> Quatf;
typedef Quaternion<double> Quatd;

} // namespace math

#if not defined(VMATH_COMPILED_LIB)
#include "vmath_types_impl.h"
#endif

