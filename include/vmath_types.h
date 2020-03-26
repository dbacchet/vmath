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
#include <initializer_list>

namespace math {

// ///////// //
// 2D Vector //
// ///////// //

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

template <typename T> Vector2<T> operator+(const Vector2<T> &v, T s);
template <typename T> Vector2<T> operator+(T s, const Vector2<T> &v);
template <typename T> Vector2<T> operator-(const Vector2<T> &v, T s);
template <typename T> Vector2<T> operator-(T s, const Vector2<T> &v);
template <typename T> Vector2<T> operator*(const Vector2<T> &v, T s);
template <typename T> Vector2<T> operator*(T s, const Vector2<T> &v);
template <typename T> Vector2<T> operator/(const Vector2<T> &v, T s);
 

// ///////// //
// 3D Vector //
// ///////// //

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

template <typename T> Vector3<T> operator+(const Vector3<T> &v, T s);
template <typename T> Vector3<T> operator+(T s, const Vector3<T> &v);
template <typename T> Vector3<T> operator-(const Vector3<T> &v, T s);
template <typename T> Vector3<T> operator-(T s, const Vector3<T> &v);
template <typename T> Vector3<T> operator*(const Vector3<T> &v, T s);
template <typename T> Vector3<T> operator*(T s, const Vector3<T> &v);
template <typename T> Vector3<T> operator/(const Vector3<T> &v, T s);


// ///////// //
// 4D Vector //
// ///////// //

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
    Vector4<T> &operator=(const Vector4<T> &rhs);
    template <typename fromT> Vector4<T> &operator=(const fromT &rhs) {
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
    // scalar operators
    void operator+=(T rhs);
    void operator-=(T rhs);
    void operator*=(T rhs);
    void operator/=(T rhs);
    // unary operators
    Vector4<T> operator-() const;
    // conversion to pointer operator (for passing the instance as a T*)
    operator T *() { return (T *)this; }
    operator const T *() const { return (const T *)this; }
};

template <typename T> Vector4<T> operator+(const Vector4<T> &v, T s);
template <typename T> Vector4<T> operator+(T s, const Vector4<T> &v);
template <typename T> Vector4<T> operator-(const Vector4<T> &v, T s);
template <typename T> Vector4<T> operator-(T s, const Vector4<T> &v);
template <typename T> Vector4<T> operator*(const Vector4<T> &v, T s);
template <typename T> Vector4<T> operator*(T s, const Vector4<T> &v);
template <typename T> Vector4<T> operator/(const Vector4<T> &v, T s);


// ////////// //
// 3x3 Matrix //
// ////////// //

/// 3x3 Matrix
/// @note data is stored in column major order
template <typename T> struct Matrix3 {
    T data[9]; ///< values (stored in column-major order)

    // constructors
    Matrix3();
    Matrix3(const Matrix3<T> &src);
    template <typename fromT> Matrix3(const Matrix3<fromT> &src) {
        for (int i = 0; i < 9; i++)
            data[i] = static_cast<T>(src.data[i]);
    }
    // from arrays. Note: the input arrays are assumed in row-major, to be more consistent with the usual way of writing a matrix in a file
    Matrix3(const T *dt);
    Matrix3(std::initializer_list<T>);
    // comparison
    bool operator==(const Matrix3<T> &rhs) const;
    bool operator!=(const Matrix3<T> &rhs) const;
    /// element at position (i,j), with linear algebra matrix notation (row,column), 0..2
    /// @param i row (0..2)
    /// @param j column (0..2)
    T &operator()(int i, int j);
    const T &operator()(int i, int j) const;
    /// element at position (x,y), using the internal column-major notation (column,row), 0..2
    T &at(int x, int y);
    const T &at(int x, int y) const;
    // assignment operators
    Matrix3<T> &operator=(const Matrix3<T> &rhs);
    template <typename fromT> Matrix3<T> &operator=(const Matrix3<fromT> &rhs) {
        for (int i = 0; i < 9; i++)
            data[i] = static_cast<T>(rhs.data[i]);
        return *this;
    }
    // scalar operations
    void operator+=(T rhs);
    void operator-=(T rhs);
    void operator*=(T rhs);
    void operator/=(T rhs);
    // conversion to pointer operator (for passing the instance as a T*)
    operator T *() { return (T *)data; }
    operator const T *() const { return (const T *)data; }
};

// unary operators
template <typename T> Matrix3<T> operator-(const Matrix3<T> &m1);
// matrix operations
template <typename T> Matrix3<T> operator+(const Matrix3<T> &m1, const Matrix3<T> &m2);
template <typename T> Matrix3<T> operator-(const Matrix3<T> &m1, const Matrix3<T> &m2);
template <typename T> Matrix3<T> operator*(const Matrix3<T> &m1, const Matrix3<T> &m2);
// scalar operations
template <typename T> Matrix3<T> operator+(const Matrix3<T> &m1, T s);
template <typename T> Matrix3<T> operator+(T s, const Matrix3<T> &m1);
template <typename T> Matrix3<T> operator-(const Matrix3<T> &m1, T s);
template <typename T> Matrix3<T> operator-(T s, const Matrix3<T> &m1);
template <typename T> Matrix3<T> operator*(const Matrix3<T> &m1, T s);
template <typename T> Matrix3<T> operator*(T s, const Matrix3<T> &m1);
template <typename T> Matrix3<T> operator/(const Matrix3<T> &m1, T s);
// vector operations
template <typename T> Vector3<T> operator*(const Matrix3<T> &m1, const Vector3<T> &rhs);


// ////////// //
// 4x4 Matrix //
// ////////// //

/// 4x4 Matrix
/// @note data is stored in column major order.
template <typename T> struct Matrix4 {
    T data[16]; ///< data stored in column major order

    Matrix4();
    Matrix4(const Matrix4<T> &src);
    template <typename fromT> Matrix4(const Matrix4<fromT> &src) {
        for (int i = 0; i < 16; i++)
            data[i] = static_cast<T>(src.data[i]);
    }
    // from arrays. Note: the input arrays are assumed in row-major, to be more consistent with the usual way of writing a matrix in a file
    Matrix4(const T *dt);
    Matrix4(std::initializer_list<T>);
    // comparison
    bool operator==(const Matrix4<T> &rhs) const;
    bool operator!=(const Matrix4<T> &rhs) const;
    /// element at position (i,j), with linear algebra matrix notation (row,column), 0..3
    /// @param i row (0..3)
    /// @param j column (0..3)
    T &operator()(int i, int j);
    const T &operator()(int i, int j) const;
    /// element at position (x,y), using the internal column-major notation (column,row), 0..3
    T &at(int x, int y);
    const T &at(int x, int y) const;
    // assignment
    Matrix4<T> &operator=(const Matrix4<T> &rhs);
    template <typename fromT> Matrix4<T> &operator=(const Matrix4<fromT> &rhs) {
        for (int i = 0; i < 16; i++)
            data[i] = static_cast<T>(rhs.data[i]);
        return *this;
    }
    // scalar operations
    void operator+=(T rhs);
    void operator-=(T rhs);
    void operator*=(T rhs);
    void operator/=(T rhs);
    // conversion to pointer operator (for passing the instance as a T*)
    operator T *() { return (T *)data; }
    operator const T *() const { return (const T *)data; }
};

// unary operators
template <typename T> Matrix4<T> operator-(const Matrix4<T> &m1);
// matrix operations
template <typename T> Matrix4<T> operator+(const Matrix4<T> &m1, const Matrix4<T> &m2);
template <typename T> Matrix4<T> operator-(const Matrix4<T> &m1, const Matrix4<T> &m2);
template <typename T> Matrix4<T> operator*(const Matrix4<T> &m1, const Matrix4<T> &m2);
// scalar operations
template <typename T> Matrix4<T> operator+(const Matrix4<T> &m1, T s);
template <typename T> Matrix4<T> operator+(T s, const Matrix4<T> &m1);
template <typename T> Matrix4<T> operator-(const Matrix4<T> &m1, T s);
template <typename T> Matrix4<T> operator-(T s, const Matrix4<T> &m1);
template <typename T> Matrix4<T> operator*(const Matrix4<T> &m1, T s);
template <typename T> Matrix4<T> operator*(T s, const Matrix4<T> &m1);
template <typename T> Matrix4<T> operator/(const Matrix4<T> &m1, T s);
// vector operations
template <typename T> Vector4<T> operator*(const Matrix4<T> &m1, const Vector4<T> &rhs);
template <typename T> Vector3<T> operator*(const Matrix4<T> &m1, const Vector3<T> &rhs);


// ////////// //
// Quaternion //
// ////////// //

/// Quaternion
template <typename T> struct Quaternion {
    T w; ///< real part
    T x; ///< imaginary x component
    T y; ///< imaginary y component
    T z; ///< imaginary z component

    Quaternion();
    Quaternion(const Quaternion<T> &q);
    template <typename fromT>
    Quaternion(const fromT &q)
    : w(static_cast<T>(q.w)), x(static_cast<T>(q.x)) 
    , y(static_cast<T>(q.y)), z(static_cast<T>(q.z)) {}

    Quaternion(T w_, T x_, T y_, T z_)
    : w(w_), x(x_), y(y_), z(z_) {}
    // assignment
    Quaternion<T> &operator=(const Quaternion<T> &rhs);
    template <typename fromT> Quaternion<T> &operator=(const fromT &rhs) {
        w = static_cast<T>(rhs.w);
        x = static_cast<T>(rhs.x);
        y = static_cast<T>(rhs.y);
        z = static_cast<T>(rhs.z);
        return *this;
    }
    // comparison
    bool operator==(const Quaternion<T> &rhs) const;
    bool operator!=(const Quaternion<T> &rhs) const;
    // quaternion algebra
    void operator+=(const Quaternion<T> &rhs);
    void operator-=(const Quaternion<T> &rhs);
    // scalar operators
    void operator+=(T rhs);
    void operator-=(T rhs);
    void operator*=(T rhs);
};

// unary operators
template <typename T> Quaternion<T> operator-(const Quaternion<T> &q);
// binary operators
template <typename T> Quaternion<T> operator+(const Quaternion<T> &q1, const Quaternion<T> &q2);
template <typename T> Quaternion<T> operator-(const Quaternion<T> &q1, const Quaternion<T> &q2);
template <typename T> Quaternion<T> operator*(const Quaternion<T> &q1, const Quaternion<T> &q2);
// conjugate operator
template <typename T> Quaternion<T> operator~(const Quaternion<T> &q);
// scalar operations
template <typename T> Quaternion<T> operator+(const Quaternion<T> &q1, T v);
template <typename T> Quaternion<T> operator+(T v, const Quaternion<T> &q1);
template <typename T> Quaternion<T> operator-(const Quaternion<T> &q1, T v);
template <typename T> Quaternion<T> operator-(T v, const Quaternion<T> &q1);
template <typename T> Quaternion<T> operator*(const Quaternion<T> &q1, T v);
template <typename T> Quaternion<T> operator*(T v, const Quaternion<T> &q1);
template <typename T> Quaternion<T> operator/(const Quaternion<T> &q1, T v);
// vector operators
template <typename T> Vector3<T> operator*(const Quaternion<T> &q, const Vector3<T> &vec);
template <typename T> Vector4<T> operator*(const Quaternion<T> &q, const Vector4<T> &vec);

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


//----------------------------------------------------------------------------
// implementations for the functions that will not have explicit instantiation
//----------------------------------------------------------------------------
// vector2
template <typename T> inline Vector2<T> operator+(const Vector2<T> &v, T s) {
    return Vector2<T>(v.x+s, v.y+s);
}
template <typename T> inline Vector2<T> operator+(T s, const Vector2<T> &v) {
    return Vector2<T>(v.x+s, v.y+s);
}
template <typename T> inline Vector2<T> operator-(const Vector2<T> &v, T s) {
    return Vector2<T>(v.x-s, v.y-s);
}
template <typename T> inline Vector2<T> operator-(T s, const Vector2<T> &v) {
    return Vector2<T>(s-v.x, s-v.y);
}
template <typename T> inline Vector2<T> operator*(const Vector2<T> &v, T s) {
    return Vector2<T>(v.x*s, v.y*s);
}
template <typename T> inline Vector2<T> operator*(T s, const Vector2<T> &v) {
    return Vector2<T>(v.x*s, v.y*s);
}
template <typename T> inline Vector2<T> operator/(const Vector2<T> &v, T s) {
    return Vector2<T>(v.x/s, v.y/s);
}

// vector3
template <typename T> inline Vector3<T> operator+(const Vector3<T> &v, T s) {
    return Vector3<T>(v.x+s, v.y+s, v.z+s);
}
template <typename T> inline Vector3<T> operator+(T s, const Vector3<T> &v) {
    return Vector3<T>(v.x+s, v.y+s, v.z+s);
}
template <typename T> inline Vector3<T> operator-(const Vector3<T> &v, T s) {
    return Vector3<T>(v.x-s, v.y-s, v.z-s);
}
template <typename T> inline Vector3<T> operator-(T s, const Vector3<T> &v) {
    return Vector3<T>(s-v.x, s-v.y, s-v.z);
}
template <typename T> inline Vector3<T> operator*(const Vector3<T> &v, T s) {
    return Vector3<T>(v.x*s, v.y*s, v.z*s);
}
template <typename T> inline Vector3<T> operator*(T s, const Vector3<T> &v) {
    return Vector3<T>(v.x*s, v.y*s, v.z*s);
}
template <typename T> inline Vector3<T> operator/(const Vector3<T> &v, T s) {
    return Vector3<T>(v.x/s, v.y/s, v.z/s);
}

// vector4
template <typename T> inline Vector4<T> operator+(const Vector4<T> &v, T s) {
    return Vector4<T>(v.x+s, v.y+s, v.z+s, v.w+s);
}
template <typename T> inline Vector4<T> operator+(T s, const Vector4<T> &v) {
    return Vector4<T>(v.x+s, v.y+s, v.z+s, v.w+s);
}
template <typename T> inline Vector4<T> operator-(const Vector4<T> &v, T s) {
    return Vector4<T>(v.x-s, v.y-s, v.z-s, v.w-s);
}
template <typename T> inline Vector4<T> operator-(T s, const Vector4<T> &v) {
    return Vector4<T>(s-v.x, s-v.y, s-v.z, s-v.w);
}
template <typename T> inline Vector4<T> operator*(const Vector4<T> &v, T s) {
    return Vector4<T>(v.x*s, v.y*s, v.z*s, v.w*s);
}
template <typename T> inline Vector4<T> operator*(T s, const Vector4<T> &v) {
    return Vector4<T>(v.x*s, v.y*s, v.z*s, v.w*s);
}
template <typename T> inline Vector4<T> operator/(const Vector4<T> &v, T s) {
    return Vector4<T>(v.x/s, v.y/s, v.z/s, v.w/s);
}

// matrix3
template <typename T> inline Matrix3<T> operator-(const Matrix3<T> &m1) {
    Matrix3<T> ret;
    for (int i = 0; i < 9; i++)
        ret.data[i] = -m1.data[i];
    return ret;
}
template <typename T> inline Matrix3<T> operator+(const Matrix3<T> &m1, const Matrix3<T> &m2) {
    Matrix3<T> ret;
    for (int i = 0; i < 9; i++)
        ret.data[i] = m1.data[i] + m2.data[i];
    return ret;
}
template <typename T> inline Matrix3<T> operator-(const Matrix3<T> &m1, const Matrix3<T> &m2) {
    Matrix3<T> ret;
    for (int i = 0; i < 9; i++)
        ret.data[i] = m1.data[i] - m2.data[i];
    return ret;
}
template <typename T> inline Matrix3<T> operator*(const Matrix3<T> &m1, const Matrix3<T> &m2) {
    Matrix3<T> w;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            T n = T(0);
            for (int k = 0; k < 3; k++)
                n += m1(i, k) * m2(k, j);
            w(i, j) = n;
        }
    }
    return w;
}
// scalar operations
template <typename T> inline Matrix3<T> operator+(const Matrix3<T> &m1, T s) {
    Matrix3<T> ret;
    for (int i = 0; i < 9; i++)
        ret.data[i] = m1.data[i] + s;
    return ret;
}
template <typename T> inline Matrix3<T> operator+(T s, const Matrix3<T> &m1) {
    Matrix3<T> ret;
    for (int i = 0; i < 9; i++)
        ret.data[i] = s + m1.data[i];
    return ret;
}
template <typename T> inline Matrix3<T> operator-(const Matrix3<T> &m1, T s) {
    Matrix3<T> ret;
    for (int i = 0; i < 9; i++)
        ret.data[i] = m1.data[i] - s;
    return ret;
}
template <typename T> inline Matrix3<T> operator-(T s, const Matrix3<T> &m1) {
    Matrix3<T> ret;
    for (int i = 0; i < 9; i++)
        ret.data[i] = s - m1.data[i];
    return ret;
}
template <typename T> inline Matrix3<T> operator*(const Matrix3<T> &m1, T s) {
    Matrix3<T> ret;
    for (int i = 0; i < 9; i++)
        ret.data[i] = m1.data[i] * s;
    return ret;
}
template <typename T> inline Matrix3<T> operator*(T s, const Matrix3<T> &m1) {
    Matrix3<T> ret;
    for (int i = 0; i < 9; i++)
        ret.data[i] = s * m1.data[i];
    return ret;
}
template <typename T> inline Matrix3<T> operator/(const Matrix3<T> &m1, T s) {
    Matrix3<T> ret;
    for (int i = 0; i < 9; i++)
        ret.data[i] = m1.data[i] / s;
    return ret;
}
// vector operations
template <typename T> inline Vector3<T> operator*(const Matrix3<T> &m1, const Vector3<T> &rhs) {
    return Vector3<T>(m1.data[0] * rhs.x + m1.data[3] * rhs.y + m1.data[6] * rhs.z,
                      m1.data[1] * rhs.x + m1.data[4] * rhs.y + m1.data[7] * rhs.z,
                      m1.data[2] * rhs.x + m1.data[5] * rhs.y + m1.data[8] * rhs.z);
}


// matrix4
template <typename T> inline Matrix4<T> operator-(const Matrix4<T> &m1) {
    Matrix4<T> ret;
    for (int i = 0; i < 16; i++)
        ret.data[i] = -m1.data[i];
    return ret;
}
template <typename T> inline Matrix4<T> operator+(const Matrix4<T> &m1, const Matrix4<T> &m2) {
    Matrix4<T> ret;
    for (int i = 0; i < 16; i++)
        ret.data[i] = m1.data[i] + m2.data[i];
    return ret;
}
template <typename T> inline Matrix4<T> operator-(const Matrix4<T> &m1, const Matrix4<T> &m2) {
    Matrix4<T> ret;
    for (int i = 0; i < 16; i++)
        ret.data[i] = m1.data[i] - m2.data[i];
    return ret;
}
template <typename T> inline Matrix4<T> operator*(const Matrix4<T> &m1, const Matrix4<T> &m2) {
    Matrix4<T> w;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            T n = T(0);
            for (int k = 0; k < 4; k++)
                n += m1(i, k) * m2(k, j);
            w(i, j) = n;
        }
    }
    return w;
}
// scalar operations
template <typename T> inline Matrix4<T> operator+(const Matrix4<T> &m1, T s) {
    Matrix4<T> ret;
    for (int i = 0; i < 16; i++)
        ret.data[i] = m1.data[i] + s;
    return ret;
}
template <typename T> inline Matrix4<T> operator+(T s, const Matrix4<T> &m1) {
    Matrix4<T> ret;
    for (int i = 0; i < 16; i++)
        ret.data[i] = s + m1.data[i];
    return ret;
}
template <typename T> inline Matrix4<T> operator-(const Matrix4<T> &m1, T s) {
    Matrix4<T> ret;
    for (int i = 0; i < 16; i++)
        ret.data[i] = m1.data[i] - s;
    return ret;
}
template <typename T> inline Matrix4<T> operator-(T s, const Matrix4<T> &m1) {
    Matrix4<T> ret;
    for (int i = 0; i < 16; i++)
        ret.data[i] = s - m1.data[i];
    return ret;
}
template <typename T> inline Matrix4<T> operator*(const Matrix4<T> &m1, T s) {
    Matrix4<T> ret;
    for (int i = 0; i < 16; i++)
        ret.data[i] = m1.data[i] * s;
    return ret;
}
template <typename T> inline Matrix4<T> operator*(T s, const Matrix4<T> &m1) {
    Matrix4<T> ret;
    for (int i = 0; i < 16; i++)
        ret.data[i] = s * m1.data[i];
    return ret;
}
template <typename T> inline Matrix4<T> operator/(const Matrix4<T> &m1, T s) {
    Matrix4<T> ret;
    for (int i = 0; i < 16; i++)
        ret.data[i] = m1.data[i] / s;
    return ret;
}
// vector operations
template <typename T> inline Vector4<T> operator*(const Matrix4<T> &m1, const Vector4<T> &rhs) {
    return Vector4<T>(m1.data[0] * rhs.x + m1.data[4] * rhs.y + m1.data[8] * rhs.z  + m1.data[12] * rhs.w,
                      m1.data[1] * rhs.x + m1.data[5] * rhs.y + m1.data[9] * rhs.z  + m1.data[13] * rhs.w,
                      m1.data[2] * rhs.x + m1.data[6] * rhs.y + m1.data[10] * rhs.z + m1.data[14] * rhs.w,
                      m1.data[3] * rhs.x + m1.data[7] * rhs.y + m1.data[11] * rhs.z + m1.data[15] * rhs.w);
}
template <typename T> inline Vector3<T> operator*(const Matrix4<T> &m1, const Vector3<T> &rhs) {
    return Vector3<T>(m1.data[0] * rhs.x + m1.data[4] * rhs.y + m1.data[8] * rhs.z + m1.data[12],
                      m1.data[1] * rhs.x + m1.data[5] * rhs.y + m1.data[9] * rhs.z + m1.data[13],
                      m1.data[2] * rhs.x + m1.data[6] * rhs.y + m1.data[10] * rhs.z + m1.data[14]);
}

// quaternion

// unary operators
template <typename T> inline Quaternion<T> operator-(const Quaternion<T> &q) {
    return Quaternion<T>(-q.w, -q.x, -q.y, -q.z);
}
// conjugate operator
template <typename T> inline Quaternion<T> operator~(const Quaternion<T> &q) {
    return Quaternion<T>(q.w, -q.x, -q.y, -q.z);
}
// binary operators
template <typename T> inline Quaternion<T> operator+(const Quaternion<T> &q1, const Quaternion<T> &q2) {
    return Quaternion<T>(q1.w + q2.w, q1.x + q2.x, q1.y + q2.y, q1.z + q2.z);
}
template <typename T> inline Quaternion<T> operator-(const Quaternion<T> &q1, const Quaternion<T> &q2) {
    return Quaternion<T>(q1.w - q2.w, q1.x - q2.x, q1.y - q2.y, q1.z - q2.z);
}
template <typename T> inline Quaternion<T> operator*(const Quaternion<T> &q1, const Quaternion<T> &q2) {
    return Quaternion<T>(q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z,
                         q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
                         q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x,
                         q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w);
}
// scalar operations
template <typename T> inline Quaternion<T> operator+(const Quaternion<T> &q1, T v) {
    return Quaternion<T>(q1.w + v, q1.x + v, q1.y + v, q1.z + v);
}
template <typename T> inline Quaternion<T> operator+(T v, const Quaternion<T> &q1) {
    return Quaternion<T>(q1.w + v, q1.x + v, q1.y + v, q1.z + v);
}
template <typename T> inline Quaternion<T> operator-(const Quaternion<T> &q1, T v) {
    return Quaternion<T>(q1.w - v, q1.x - v, q1.y - v, q1.z - v);
}
template <typename T> inline Quaternion<T> operator-(T v, const Quaternion<T> &q1) {
    return Quaternion<T>(v - q1.w, v - q1.x, v - q1.y, v - q1.z);
}
template <typename T> inline Quaternion<T> operator*(const Quaternion<T> &q1, T v) {
    return Quaternion<T>(q1.w * v, q1.x * v, q1.y * v, q1.z * v);
}
template <typename T> inline Quaternion<T> operator*(T v, const Quaternion<T> &q1) {
    return Quaternion<T>(q1.w * v, q1.x * v, q1.y * v, q1.z * v);
}
template <typename T> inline Quaternion<T> operator/(const Quaternion<T> &q1, T v) {
    return Quaternion<T>(q1.w / v, q1.x / v, q1.y / v, q1.z / v);
}
// vector operators
template <typename T> inline Vector3<T> operator*(const Quaternion<T> &q, const Vector3<T> &vec) {
    // implements: res = rot*point* ~rot
    // where rot is the quaternion and point a quat where x/y/z contains point coords
    T rw = q.w * 0 - q.x * vec.x - q.y * vec.y - q.z * vec.z;
    T rx = q.w * vec.x + q.x * 0 + q.y * vec.z - q.z * vec.y;
    T ry = q.w * vec.y - q.x * vec.z + q.y * 0 + q.z * vec.x;
    T rz = q.w * vec.z + q.x * vec.y - q.y * vec.x + q.z * 0;
    return Vector3<T>(-rw * q.x + rx * q.w - ry * q.z + rz * q.y, 
                      -rw * q.y + rx * q.z + ry * q.w - rz * q.x,
                      -rw * q.z - rx * q.y + ry * q.x + rz * q.w);
}
template <typename T> inline Vector4<T> operator*(const Quaternion<T> &q, const Vector4<T> &vec) {
    // This is a convenience function, identical to the one multiplying a Vector3.
    // In this case with a vector4, we ignore the vec.w coord and pass it through in the result
    T rw = q.w * 0 - q.x * vec.x - q.y * vec.y - q.z * vec.z;
    T rx = q.w * vec.x + q.x * 0 + q.y * vec.z - q.z * vec.y;
    T ry = q.w * vec.y - q.x * vec.z + q.y * 0 + q.z * vec.x;
    T rz = q.w * vec.z + q.x * vec.y - q.y * vec.x + q.z * 0;
    return Vector4<T>(-rw * q.x + rx * q.w - ry * q.z + rz * q.y,
                      -rw * q.y + rx * q.z + ry * q.w - rz * q.x,
                      -rw * q.z - rx * q.y + ry * q.x + rz * q.w,
                      vec.w); // last component kept from source
}

} // namespace math

#if not defined(VMATH_COMPILED_LIB)
#include "vmath_types_impl.h"
#endif

