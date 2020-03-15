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
    Vector2(const Vector2<fromT> &src)
    : x(static_cast<T>(src.x))
    , y(static_cast<T>(src.y)) {}

    // assignment operators
    Vector2<T> &operator=(const Vector2<T> &rhs);
    template <typename fromT> Vector2<T> &operator=(const Vector2<fromT> &rhs) {
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
    T dot(const Vector2<T> &rhs) const { return x * rhs.x + y * rhs.y; }
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
    Vector3(const Vector3<fromT> &src)
    : x(static_cast<T>(src.x))
    , y(static_cast<T>(src.y))
    , z(static_cast<T>(src.z)) {}
    // assignment operators
    Vector3<T> operator=(const Vector3<T> &rhs);
    template <typename fromT> Vector3<T> operator=(const Vector3<fromT> &rhs) {
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
    T dot(const Vector3<T> &rhs) const { return x * rhs.x + y * rhs.y + z * rhs.z; }
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
    Vector4(const Vector4<fromT> &src)
    : x(static_cast<T>(src.x))
    , y(static_cast<T>(src.y))
    , z(static_cast<T>(src.z))
    , w(static_cast<T>(src.w)) {}
    // assignment operators
    Vector4<T> operator=(const Vector4<T> &rhs);
    template <typename fromT> Vector4<T> operator=(const Vector4<fromT> &rhs) {
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

//--------------------------------------
// shortcuts
//-------------------------------------
typedef Matrix3<float> Matrix3f;
typedef Matrix3<double> Matrix3d;
typedef Matrix3<int> Matrix3i;

typedef Matrix4<float> Matrix4f;
typedef Matrix4<double> Matrix4d;
typedef Matrix4<int> Matrix4i;

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
typedef Quaternion<float> Quatf;
typedef Quaternion<double> Quatd;


/*


//--------------------------------------
// Implementation
//--------------------------------------

// Vector2<T> implementation

template <typename T>
inline Vector2<T>::Vector2()
: x(0), y(0)
{}

template <typename T>
inline Vector2<T>::Vector2(T _x, T _y)
: x(_x), y(_y)
{}

template <typename T>
inline Vector2<T>::Vector2(const Vector2<T>& src)
: x(src.x), y(src.y)
{}

template <typename T>
inline Vector2<T>& Vector2<T>::operator=(const Vector2<T>& rhs)
{
    x = rhs.x;
    y = rhs.y;
    return *this;
}

template <typename T>
inline T& Vector2<T>::operator[](int n)
{
    assert(n >= 0 && n <= 1);
    if (0 == n) return x;
    else        return y;
}

template <typename T>
inline const T& Vector2<T>::operator[](int n) const
{
    assert(n >= 0 && n <= 1);
    if (0 == n) return x;
    else        return y;
}

template <typename T>
inline Vector2<T> Vector2<T>::operator+(const Vector2<T>& rhs) const
{
    return Vector2<T>(x + rhs.x, y + rhs.y);
}

template <typename T>
inline Vector2<T> Vector2<T>::operator-(const Vector2<T>& rhs) const
{
    return Vector2<T>(x - rhs.x, y - rhs.y);
}

template <typename T>
inline void Vector2<T>::operator+=(const Vector2<T>& rhs)
{
    x += rhs.x;
    y += rhs.y;
}

template <typename T>
inline void Vector2<T>::operator-=(const Vector2<T>& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
}

template <typename T>
inline Vector2<T> Vector2<T>::operator+(T rhs) const
{
    return Vector2<T>(x + rhs, y + rhs);
}

template <typename T>
inline Vector2<T> Vector2<T>::operator-(T rhs) const
{
    return Vector2<T>(x - rhs, y - rhs);
}

template <typename T>
inline Vector2<T> Vector2<T>::operator*(T rhs) const
{
    return Vector2<T>(x * rhs, y * rhs);
}

template <typename T>
inline Vector2<T> Vector2<T>::operator/(T rhs) const
{
    return Vector2<T>(x / rhs, y / rhs);
}

template <typename T>
inline void Vector2<T>::operator+=(T rhs)
{
    x += rhs;
    y += rhs;
}

template <typename T>
inline void Vector2<T>::operator-=(T rhs)
{
    x -= rhs;
    y -= rhs;
}

template <typename T>
inline void Vector2<T>::operator*=(T rhs)
{
    x *= rhs;
    y *= rhs;
}

template <typename T>
inline void Vector2<T>::operator/=(T rhs)
{
    x /= rhs;
    y /= rhs;
}

template <typename T>
inline bool Vector2<T>::operator==(const Vector2<T>& rhs) const
{
    return (fabs(x - rhs.x) < VMATH_EPSILON) && (fabs(y - rhs.y) < VMATH_EPSILON);
}

template <typename T>
inline bool Vector2<T>::operator!=(const Vector2<T>& rhs) const
{
    return !(*this == rhs);
}

template <typename T>
inline Vector2<T> Vector2<T>::operator-() const
{
    return Vector2<T>(-x, -y);
}


// Vector3<T> implementation //

template <typename T>
inline Vector3<T>::Vector3()
        : x(0), y(0), z(0)
{
}

template <typename T>
inline Vector3<T>::Vector3(T nx, T ny, T nz)
        : x(nx), y(ny), z(nz)
{
}

template <typename T>
inline Vector3<T>::Vector3(const Vector3<T>& src)
        : x(src.x), y(src.y), z(src.z)
{
}

template <typename T>
inline Vector3<T> Vector3<T>::operator=(const Vector3<T>& rhs)
{
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    return *this;
}

template <typename T>
inline T& Vector3<T>::operator[](int n)
{
    assert(n >= 0 && n <= 2);
    if (0 == n)      return x;
    else if (1 == n) return y;
    else             return z;
}

template <typename T>
inline const T& Vector3<T>::operator[](int n) const
{
    assert(n >= 0 && n <= 2);
    if (0 == n)      return x;
    else if (1 == n) return y;
    else             return z;
}

template <typename T>
inline Vector3<T> Vector3<T>::operator+(const Vector3<T>& rhs) const
{
    return Vector3<T>(x + rhs.x, y + rhs.y, z + rhs.z);
}

template <typename T>
inline Vector3<T> Vector3<T>::operator-(const Vector3<T>& rhs) const
{
    return Vector3<T>(x - rhs.x, y - rhs.y, z - rhs.z);
}

template <typename T>
inline void Vector3<T>::operator+=(const Vector3<T>& rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
}

template <typename T>
inline void Vector3<T>::operator-=(const Vector3<T>& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
}

template <typename T>
inline Vector3<T> Vector3<T>::operator+(T rhs) const
{
    return Vector3<T>(x + rhs, y + rhs, z + rhs);
}

template <typename T>
inline Vector3<T> Vector3<T>::operator-(T rhs) const
{
    return Vector3<T>(x - rhs, y - rhs, z - rhs);
}

template <typename T>
inline Vector3<T> Vector3<T>::operator*(T rhs) const
{
    return Vector3<T>(x * rhs, y * rhs, z * rhs);
}

template <typename T>
inline Vector3<T> Vector3<T>::operator/(T rhs) const
{
    return Vector3<T>(x / rhs, y / rhs, z / rhs);
}

template <typename T>
inline void Vector3<T>::operator+=(T rhs)
{
    x += rhs;
    y += rhs;
    z += rhs;
}

template <typename T>
inline void Vector3<T>::operator-=(T rhs)
{
    x -= rhs;
    y -= rhs;
    z -= rhs;
}

template <typename T>
inline void Vector3<T>::operator*=(T rhs)
{
    x *= rhs;
    y *= rhs;
    z *= rhs;
}

template <typename T>
inline void Vector3<T>::operator/=(T rhs)
{
    x /= rhs;
    y /= rhs;
    z /= rhs;
}

template <typename T>
inline bool Vector3<T>::operator==(const Vector3<T>& rhs) const
{
    return fabs(x - rhs.x) < VMATH_EPSILON && fabs(y - rhs.y) < VMATH_EPSILON && fabs(z - rhs.z) < VMATH_EPSILON;
}

template <typename T>
inline bool Vector3<T>::operator!=(const Vector3<T>& rhs) const
{
    return !(*this == rhs);
}

template <typename T>
inline Vector3<T> Vector3<T>::operator-() const
{
    return Vector3<T>(-x, -y, -z);
}


// Vector4<T> implementation

template <typename T>
inline Vector4<T>::Vector4()
        : x(0), y(0), z(0), w(0)
{
}

template <typename T>
inline Vector4<T>::Vector4(T nx, T ny, T nz, T nw)
        : x(nx), y(ny), z(nz), w(nw)
{
}

template <typename T>
inline Vector4<T>::Vector4(const Vector4<T>& src)
        : x(src.x), y(src.y), z(src.z), w(src.w)
{
}

template <typename T>
inline Vector4<T> Vector4<T>::operator=(const Vector4<T>& rhs)
{
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    w = rhs.w;
    return *this;
}

template <typename T>
inline T& Vector4<T>::operator[](int n)
{
    assert(n >= 0 && n <= 3);
    if (0 == n)      return x;
    else if (1 == n) return y;
    else if (2 == n) return z;
    else             return w;
}

template <typename T>
inline const T& Vector4<T>::operator[](int n) const
{
    assert(n >= 0 && n <= 3);
    if (0 == n)      return x;
    else if (1 == n) return y;
    else if (2 == n) return z;
    else             return w;
}

template <typename T>
inline Vector4<T> Vector4<T>::operator+(const Vector4<T>& rhs) const
{
    return Vector4<T>(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}

template <typename T>
inline Vector4<T> Vector4<T>::operator-(const Vector4<T>& rhs) const
{
    return Vector4<T>(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}

template <typename T>
inline void Vector4<T>::operator+=(const Vector4<T>& rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    w += rhs.w;
}

template <typename T>
inline void Vector4<T>::operator-=(const Vector4<T>& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    w -= rhs.w;
}

template <typename T>
inline bool Vector4<T>::operator==(const Vector4<T>& rhs) const
{
    return fabs(x - rhs.x) < VMATH_EPSILON && fabs(y - rhs.y) < VMATH_EPSILON && fabs(z - rhs.z) < VMATH_EPSILON && fabs(w - rhs.w) < VMATH_EPSILON;
}

template <typename T>
inline bool Vector4<T>::operator!=(const Vector4<T>& rhs) const
{
    return !(*this == rhs);
}

template <typename T>
inline Vector4<T> Vector4<T>::operator-() const
{
    return Vector4<T>(-x, -y, -z, -w);
}

template <typename T>
inline Vector4<T> Vector4<T>::operator+(T rhs) const
{
    return Vector4<T>(x + rhs, y + rhs, z + rhs, w + rhs);
}

template <typename T>
inline Vector4<T> Vector4<T>::operator-(T rhs) const
{
    return Vector4<T>(x - rhs, y - rhs, z - rhs, w - rhs);
}

template <typename T>
inline Vector4<T> Vector4<T>::operator*(T rhs) const
{
    return Vector4<T>(x * rhs, y * rhs, z * rhs, w * rhs);
}

template <typename T>
inline Vector4<T> Vector4<T>::operator/(T rhs) const
{
    return Vector4<T>(x / rhs, y / rhs, z / rhs, w / rhs);
}

template <typename T>
inline void Vector4<T>::operator+=(T rhs)
{
    x += rhs;
    y += rhs;
    z += rhs;
    w += rhs;
}

template <typename T>
inline void Vector4<T>::operator-=(T rhs)
{
    x -= rhs;
    y -= rhs;
    z -= rhs;
    w -= rhs;
}

template <typename T>
inline void Vector4<T>::operator*=(T rhs)
{
    x *= rhs;
    y *= rhs;
    z *= rhs;
    w *= rhs;
}

template <typename T>
inline void Vector4<T>::operator/=(T rhs)
{
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

template <typename T>
inline Matrix3<T>::Matrix3(const Matrix3<T>& src)
{
    std::memcpy(data, src.data, sizeof(T) * 9);
}

template <typename T>
inline Matrix3<T>::Matrix3(const T * dt)
{
    std::memcpy(data, dt, 9*sizeof(T));
}

template <typename T>
inline bool Matrix3<T>::operator==(const Matrix3<T>& rhs) const
{
    for (int i = 0; i < 9; i++)
        if (fabs(data[i] - rhs.data[i]) >= VMATH_EPSILON)
            return false;
    return true;
}

template <typename T>
inline bool Matrix3<T>::operator!=(const Matrix3<T>& rhs) const
{
    return !(*this == rhs);
}

template <typename T>
inline T& Matrix3<T>::at(int x, int y)
{
    assert(x >= 0 && x < 3);
    assert(y >= 0 && y < 3);
    return data[x * 3 + y];
}

template <typename T>
inline const T& Matrix3<T>::at(int x, int y) const
{
    assert(x >= 0 && x < 3);
    assert(y >= 0 && y < 3);
    return data[x * 3 + y];
}

template <typename T>
inline T& Matrix3<T>::operator()(int i, int j)
{
    assert(i >= 1 && i <= 3);
    assert(j >= 1 && j <= 3);
    return data[(j - 1) * 3 + i - 1];
}

template <typename T>
inline const T& Matrix3<T>::operator()(int i, int j) const
{
    assert(i >= 1 && i <= 3);
    assert(j >= 1 && j <= 3);
    return data[(j - 1) * 3 + i - 1];
}

template <typename T>
inline Matrix3<T>& Matrix3<T>::operator=(const Matrix3<T>& rhs)
{
    std::memcpy(data, rhs.data, sizeof(T) * 9);
    return *this;
}

template <typename T>
inline Matrix3<T>& Matrix3<T>::operator=(const T* rhs)
{
    std::memcpy(data, rhs, sizeof(T) * 9);
    return *this;
}

template <typename T>
inline Matrix3<T> Matrix3<T>::operator+(const Matrix3<T>& rhs) const
{
    Matrix3<T> ret;
    for (int i = 0; i < 9; i++)
        ret.data[i] = data[i] + rhs.data[i];
    return ret;
}

template <typename T>
inline Matrix3<T> Matrix3<T>::operator-(const Matrix3<T>& rhs) const
{
    Matrix3<T> ret;
    for (int i = 0; i < 9; i++)
        ret.data[i] = data[i] - rhs.data[i];
    return ret;
}

template <typename T>
inline Matrix3<T> Matrix3<T>::operator*(Matrix3<T> rhs) const
{
    Matrix3<T> w;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            T n = 0;
            for (int k = 0; k < 3; k++)
                n += rhs.at(i, k) * at(k, j);
            w.at(i, j) = n;
        }
    }
    return w;
}

template <typename T>
inline Matrix3<T> Matrix3<T>::operator+(T rhs) const
{
    Matrix3<T> ret;
    for (int i = 0; i < 9; i++)
        ret.data[i] = data[i] + rhs;
    return ret;
}

template <typename T>
inline Matrix3<T> Matrix3<T>::operator-(T rhs) const
{
    Matrix3<T> ret;
    for (int i = 0; i < 9; i++)
        ret.data[i] = data[i] - rhs;
    return ret;
}

template <typename T>
inline Matrix3<T> Matrix3<T>::operator*(T rhs) const
{
    Matrix3<T> ret;
    for (int i = 0; i < 9; i++)
        ret.data[i] = data[i] * rhs;
    return ret;
}

template <typename T>
inline Matrix3<T> Matrix3<T>::operator/(T rhs) const
{
    Matrix3<T> ret;
    for (int i = 0; i < 9; i++)
        ret.data[i] = data[i] / rhs;
    return ret;
}
template <typename T>
inline void Matrix3<T>::operator+=(T rhs)
{
    for (int i = 0; i < 9; i++)
        data[i] + rhs;
}

template <typename T>
inline void Matrix3<T>::operator-=(T rhs)
{
    for (int i = 0; i < 9; i++)
        data[i] -= rhs;
}

template <typename T>
inline void Matrix3<T>::operator*=(T rhs)
{
    for (int i = 0; i < 9; i++)
        data[i] *= rhs;
}

template <typename T>
inline void Matrix3<T>::operator/=(T rhs)
{
    for (int i = 0; i < 9; i++)
        data[i] /= rhs;
}

template <typename T>
inline Vector3<T> Matrix3<T>::operator*(const Vector3<T>& rhs) const
{
    return Vector3<T>(data[0] * rhs.x + data[3] * rhs.y + data[6] * rhs.z,
                      data[1] * rhs.x + data[4] * rhs.y + data[7] * rhs.z,
                      data[2] * rhs.x + data[5] * rhs.y + data[8] * rhs.z);
}



// Matrix4<T> implementation

template <typename T>
inline Matrix4<T>::Matrix4()   // default to identity
{
    for (int i = 0; i < 16; i++)
        data[i] = (i % 5) ? T(0) : T(1);
}

template <typename T>
inline Matrix4<T>::Matrix4(const T * dt)
{
    std::memcpy(data, dt, 16*sizeof(T));
}

template <typename T>
inline Matrix4<T>::Matrix4(const Matrix4<T>& src)
{
    std::memcpy(data, src.data, 16*sizeof(T));
}

template <typename T>
inline bool Matrix4<T>::operator==(const Matrix4<T>& rhs) const
{
    for (int i = 0; i < 16; i++)
    {
        if (fabs(data[i] - rhs.data[i]) >= VMATH_EPSILON )
            return false;
    }
    return true;
}

template <typename T>
inline bool Matrix4<T>::operator!=(const Matrix4<T>& rhs) const
{
    return !(*this == rhs);
}

template <typename T>
inline T& Matrix4<T>::at(int x, int y)
{
    assert(x >= 0 && x < 4);
    assert(y >= 0 && y < 4);
    return data[x * 4 + y];
}

template <typename T>
inline const T& Matrix4<T>::at(int x, int y) const
{
    assert(x >= 0 && x < 4);
    assert(y >= 0 && y < 4);
    return data[x * 4 + y];
}

template <typename T>
inline T& Matrix4<T>::operator()(int i, int j)
{
    assert(i >= 1 && i <= 4);
    assert(j >= 1 && j <= 4);
    return data[(j - 1) * 4 + i - 1];
}

template <typename T>
inline const T& Matrix4<T>::operator()(int i, int j) const
{
    assert(i >= 1 && i <= 4);
    assert(j >= 1 && j <= 4);
    return data[(j - 1) * 4 + i - 1];
}

template <typename T>
inline Matrix4<T>& Matrix4<T>::operator=(const Matrix4<T>& rhs)
{
    std::memcpy(data, rhs.data, 16*sizeof(T));
    return *this;
}

template <typename T>
inline Matrix4<T> Matrix4<T>::operator+(const Matrix4<T>& rhs) const
{
    Matrix4<T> ret;
    for (int i = 0; i < 16; i++)
        ret.data[i] = data[i] + rhs.data[i];
    return ret;
}

template <typename T>
inline Matrix4<T> Matrix4<T>::operator-(const Matrix4<T>& rhs) const
{
    Matrix4<T> ret;
    for (int i = 0; i < 16; i++)
        ret.data[i] = data[i] - rhs.data[i];
    return ret;
}

template <typename T>
inline Matrix4<T> Matrix4<T>::operator*(Matrix4<T> rhs) const
{
    Matrix4<T> w;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            T n = 0;
            for (int k = 0; k < 4; k++)
                n += rhs.at(i, k) * at(k, j);
            w.at(i, j) = n;
        }
    }
    return w;

}

template <typename T>
inline Matrix4<T> Matrix4<T>::operator+(T rhs) const
{
    Matrix4<T> ret;
    for (int i = 0; i < 16; i++)
        ret.data[i] = data[i] + rhs;
    return ret;
}

template <typename T>
inline Matrix4<T> Matrix4<T>::operator-(T rhs) const
{
    Matrix4<T> ret;
    for (int i = 0; i < 16; i++)
        ret.data[i] = data[i] - rhs;
    return ret;
}

template <typename T>
inline Matrix4<T> Matrix4<T>::operator*(T rhs) const
{
    Matrix4<T> ret;
    for (int i = 0; i < 16; i++)
        ret.data[i] = data[i] * rhs;
    return ret;
}

template <typename T>
inline Matrix4<T> Matrix4<T>::operator/(T rhs) const
{
    Matrix4<T> ret;
    for (int i = 0; i < 16; i++)
        ret.data[i] = data[i] / rhs;
    return ret;
}
template <typename T>
inline void Matrix4<T>::operator+=(T rhs)
{
    for (int i = 0; i < 16; i++)
        data[i] + rhs;
}

template <typename T>
inline void Matrix4<T>::operator-=(T rhs)
{
    for (int i = 0; i < 16; i++)
        data[i] -= rhs;
}

template <typename T>
inline void Matrix4<T>::operator*=(T rhs)
{
    for (int i = 0; i < 16; i++)
        data[i] *= rhs;
}

template <typename T>
inline void Matrix4<T>::operator/=(T rhs)
{
    for (int i = 0; i < 16; i++)
        data[i] /= rhs;
}

// vector operators
template <typename T>
inline Vector4<T> Matrix4<T>::operator*(const Vector4<T>& rhs) const
{
    return Vector4<T>(data[0] * rhs.x + data[4] * rhs.y + data[8] * rhs.z  + data[12] * rhs.w,
                      data[1] * rhs.x + data[5] * rhs.y + data[9] * rhs.z  + data[13] * rhs.w,
                      data[2] * rhs.x + data[6] * rhs.y + data[10] * rhs.z + data[14] * rhs.w,
                      data[3] * rhs.x + data[7] * rhs.y + data[11] * rhs.z + data[15] * rhs.w);

}

template <typename T>
inline Vector3<T> Matrix4<T>::operator*(const Vector3<T>& rhs) const
{
    return Vector3<T>(data[0] * rhs.x + data[4] * rhs.y + data[8] * rhs.z  + data[12],
                      data[1] * rhs.x + data[5] * rhs.y + data[9] * rhs.z  + data[13],
                      data[2] * rhs.x + data[6] * rhs.y + data[10] * rhs.z + data[14]);
}



// Quaternion<T> implementation

template <typename T>
inline Quaternion<T>::Quaternion()
        : w(0), v(0, 0, 0)
{}

template <typename T>
inline Quaternion<T>::Quaternion(const Quaternion<T>& q)
        : w(q.w), v(q.v)
{}

template <typename T>
inline Quaternion<T>::Quaternion(T w_, const Vector3<T>& v_)
        : w(w_), v(v_)
{
}

template <typename T>
inline Quaternion<T>::Quaternion(T w_, T x, T y, T z)
        : w(w_), v(x, y, z)
{
}

template <typename T>
inline Quaternion<T>& Quaternion<T>::operator=(const Quaternion<T>& rhs)
{
    v = rhs.v;
    w = rhs.w;
    return *this;
}

template <typename T>
inline Quaternion<T> Quaternion<T>::operator+(const Quaternion<T>& rhs) const
{
    const Quaternion<T>& lhs = *this;
    return Quaternion<T>(lhs.w + rhs.w, lhs.v + rhs.v);
}

template <typename T>
inline Quaternion<T> Quaternion<T>::operator*(const Quaternion<T>& rhs) const
{
    const Quaternion<T>& lhs = *this;
    return Quaternion<T>(lhs.w*rhs.w   - lhs.v.x*rhs.v.x - lhs.v.y*rhs.v.y - lhs.v.z*rhs.v.z,
                         lhs.w*rhs.v.x + lhs.v.x*rhs.w   + lhs.v.y*rhs.v.z - lhs.v.z*rhs.v.y,
                         lhs.w*rhs.v.y - lhs.v.x*rhs.v.z + lhs.v.y*rhs.w   + lhs.v.z*rhs.v.x,
                         lhs.w*rhs.v.z + lhs.v.x*rhs.v.y - lhs.v.y*rhs.v.x + lhs.v.z*rhs.w);
}

template <typename T>
inline Quaternion<T> Quaternion<T>::operator-(const Quaternion<T>& rhs) const
{
    const Quaternion<T>& lhs = *this;
    return Quaternion<T>(lhs.w - rhs.w, lhs.v - rhs.v);
}

template <typename T>
inline void Quaternion<T>::operator+=(const Quaternion<T>& rhs)
{
    w += rhs.w;
    v += rhs.v;
}

template <typename T>
inline void Quaternion<T>::operator-=(const Quaternion<T>& rhs)
{
    w -= rhs.w;
    v -= rhs.v;
}

template <typename T>
inline void Quaternion<T>::operator*=(const Quaternion<T>& rhs)
{
    Quaternion q = (*this) * rhs;
    v = q.v;
    w = q.w;
}

template <typename T>
inline Quaternion<T> Quaternion<T>::operator*(T rhs) const
{
    return Quaternion<T>(w * rhs, v * rhs);
}

template <typename T>
inline void Quaternion<T>::operator*=(T rhs)
{
    w *= rhs;
    v *= rhs;
}

template <typename T>
inline bool Quaternion<T>::operator==(const Quaternion<T>& rhs) const
{
    const Quaternion<T>& lhs = *this;
    return (fabs(lhs.w - rhs.w) < VMATH_EPSILON) && lhs.v == rhs.v;
}

template <typename T>
inline bool Quaternion<T>::operator!=(const Quaternion<T>& rhs) const
{
    return !(*this == rhs);
}

template <typename T>
inline Quaternion<T> Quaternion<T>::operator-() const
{
    return Quaternion<T>(-w, -v);
}

template <typename T>
inline Quaternion<T> Quaternion<T>::operator~() const
{
    return Quaternion<T>(w, -v);
}

template <typename T>
inline Vector3<T> Quaternion<T>::operator*(const Vector3<T>& vec) const
{
    // implements: res = rot*point* ~rot
    // where rot is the quaternion and point a quat where v.x/y/z contains point coords

    T rw = w*0     - v.x*vec.x - v.y*vec.y - v.z*vec.z;
    T rx = w*vec.x + v.x*0     + v.y*vec.z - v.z*vec.y;
    T ry = w*vec.y - v.x*vec.z + v.y*0     + v.z*vec.x;
    T rz = w*vec.z + v.x*vec.y - v.y*vec.x + v.z*0;
    // w coord is: rw*w   - rx*v.x - ry*v.y - rz*v.z
    return Vector3<T>(-rw*v.x + rx*w   - ry*v.z + rz*v.y,
                      -rw*v.y + rx*v.z + ry*w   - rz*v.x,
                      -rw*v.z - rx*v.y + ry*v.x + rz*w);

}

template <typename T>
inline Vector4<T> Quaternion<T>::operator*(const Vector4<T>& vec) const
{
    // implements: res = rot*point* ~rot
    // where rot is the quaternion and point a quat where v.x/y/z contains point coords

    T rw = w*0     - v.x*vec.x - v.y*vec.y - v.z*vec.z;
    T rx = w*vec.x + v.x*0     + v.y*vec.z - v.z*vec.y;
    T ry = w*vec.y - v.x*vec.z + v.y*0     + v.z*vec.x;
    T rz = w*vec.z + v.x*vec.y - v.y*vec.x + v.z*0;
    // w coord is: rw*w   - rx*v.x - ry*v.y - rz*v.z
    return Vector4<T>(-rw*v.x + rx*w   - ry*v.z + rz*v.y,
                      -rw*v.y + rx*v.z + ry*w   - rz*v.x,
                      -rw*v.z - rx*v.y + ry*v.x + rz*w,
                      vec.w);   // last component kept from source
}
*/

} // namespace math

#if not defined(VMATH_COMPILED_LIB)
#include "vmath_types_impl.h"
#endif
