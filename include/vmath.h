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

#include "vmath_types.h"

#define EPSILON (4.37114e-07)

#ifndef M_PI
  #define M_PI           3.14159265358979323846  /* pi */
#endif

namespace math
{
    namespace vector2
    {
        /// get length of vector.
        template <typename T> T          length(const Vector2<T> &vec);
        /// square of length.
        template <typename T> T          length2(const Vector2<T> &vec);
        /// Normalize vector
        template <typename T> void       normalize(Vector2<T> &vec);
        /// linear interpolation of two vectors
        template <typename T> Vector2<T> lerp(const Vector2<T>& v1, const Vector2<T>& v2, T fact);
    }

    namespace vector3
    {
        /// dot product
        template <typename T> T          dot(const Vector3<T>& v1, const Vector3<T>& v2);
        /// cross product
        template <typename T> Vector3<T> cross(const Vector3<T>& v1, const Vector3<T>& v2);
        /// get length of vector.
        template <typename T> T          length(const Vector3<T>& vec);
        /// square of length.
        template <typename T> T          length2(const Vector3<T>& vec);
        /// normalize vector
        template <typename T> void       normalize(const Vector3<T>& vec);
        /// linear interpolation of two vectors
        template <typename T> Vector3<T> lerp(const Vector3<T>& v1, const Vector3<T>& v2, T fact);
    }

    namespace vector4
    {
        /// get length of vector.
        template <typename T> T          length(const Vector4<T>& vec);
        /// square of length.
        template <typename T> T          length2(const Vector4<T>& vec);
        /// normalize vector
        template <typename T> void       normalize(const Vector4<T>& vec);
        /// linear interpolation of two vectors
        template <typename T> Vector4<T> lerp(const Vector4<T>& v1, const Vector4<T>& v2, T fact);
    }

    namespace matrix3
    {
        /// set matrix to zero
        template <typename T> void       set_zero(Matrix3<T> &mat);
        /// set matrix to identity
        template <typename T> void       set_identity(Matrix3<T> &mat);
        /// transpose
        template <typename T> void       transpose(Matrix3<T> &mat);
        /// determinant
        template <typename T> T          det(const Matrix3<T> &mat);
        /// calc inverse matrix
        template <typename T> Matrix3<T> inverse(const Matrix3<T> &mat);
        /// linear interpolation of two matrices
        template <typename T> Matrix3<T> lerp(const Matrix3<T>& m1, const Matrix3<T>& m2, T fact);
    }

    namespace matrix4
    {
        /// set matrix to zero
        template <typename T> void       set_zero(Matrix4<T> &mat);
        /// set matrix to identity
        template <typename T> void       set_identity(Matrix4<T> &mat);
        /// get translation vector
        template <typename T> Vector3<T> translation(const Matrix4<T> &mat);
        /// set translation part of matrix.
        template <typename T> void       set_translation(Matrix4<T> &mat, const Vector3<T>& v);
        /// set matrix rotation part
        template <typename T> void       set_rotation(Matrix4<T> &mat, const Matrix3<T>& rot);
        /// determinant
        template <typename T> T          det(const Matrix4<T> &m);
        /// calc inverse matrix
        template <typename T> Matrix4<T> inverse(const Matrix4<T> &m);
        /// transpose
        template <typename T> void       transpose(Matrix4<T> &mat);
        /// create a translation matrix
        template <typename T> Matrix4<T> create_translation(const Vector3<T>& v);
        /// create a transformation matrix
        template <typename T> Matrix4<T> create_transformation(const Vector3<T>& v, const Quaternion<T> &q);
        /// create look-at matrix
        template <typename T> Matrix4<T> create_lookat(const Vector3<T>& eye, const Vector3<T>& to, const Vector3<T>& up=Vector3<T>(T(0),T(0),T(1)));
        /// linear interpolation
        template <typename T> Matrix4<T> lerp(const Matrix4<T>& m1, const Matrix4<T>& m2, T fact);
    }

    namespace quaternion
    {
        /// get length
        template <typename T> T             length(const Quaternion<T> &q);
        /// square of length.
        template <typename T> T             length2(const Quaternion<T> &q);
        /// normalize quaternion
        template <typename T> void          normalize(Quaternion<T> &q);
        /// get the rotation axis
        template <typename T> Vector3<T>    axis(const Quaternion<T> &q);
        /// get rotation angle
        template <typename T> T             angle(const Quaternion<T> &q);
        /// quaternion from eulers angles.
        /// @param x Rotation around x axis (in radians).
        /// @param y Rotation around y axis (in radians).
        /// @param z Rotation around z axis (in radians).
        template <typename T> Quaternion<T> from_euler_321(T x, T y, T z);
        /// quaternion given axis and angle
        /// @param axis Unit vector expressing axis of rotation.
        /// @param angle Angle of rotation around axis (in radians).
        template <typename T> Quaternion<T> from_axis_angle(Vector3<T> axis, float angle);
        /// quaternion from transformation matrix (only rotation part is kept)
        template <typename T> Quaternion<T> from_matrix(const Matrix4<T>& m);
        /// quaternion from rotation matrix.
        template <typename T> Quaternion<T> from_matrix(const Matrix3<T>& m);
        /// convert to rotation matrix.
        template <typename T> Matrix3<T>    rot_matrix(const Quaternion<T> &q);
        /// Convert to transformation matrix.
        /// @note same operation as rotmatrix() but returns a 4x4 Matrix
        template <typename T> Matrix4<T>    transform(const Quaternion<T> &q);
        /// linear interpolation
        template <typename T> Quaternion<T> lerp(const Quaternion<T> &q1, const Quaternion<T> &q2, T fact);
        /// spherical interpolation between quaternions (q1, q2)
        template <typename T> Quaternion<T> slerp(const Quaternion<T>& q1, const Quaternion<T>& q2, T r);

    }








    // //////////////////////// //
    // function implementations //
    // //////////////////////// //

    namespace vector2
    {
        template <typename T> inline T length(const Vector2<T> &vec)
        {
            return (T) sqrt(vec.x*vec.x + vec.y*vec.y);
        }

        template <typename T> inline void normalize(Vector2<T> &vec)
        {
            T s = length(vec);
            vec.x /= s;
            vec.y /= s;
        }

        template <typename T> inline T length2(const Vector2<T> &vec)
        {
            return vec.x*vec.x + vec.y*vec.y;
        }

        template <typename T> inline Vector2<T> lerp(const Vector2<T>& v1, const Vector2<T>& v2, T fact)
        {
            return v1 + (v2-v1)*fact;
        }
    }


    namespace vector3
    {
        template <typename T> inline T dot(const Vector3<T>& v1, const Vector3<T>& v2)
        {
            return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
        }

        template <typename T> inline Vector3<T> cross(const Vector3<T>& v1, const Vector3<T>& v2)
        {
            return Vector3<T>(v1.y*v2.z - v2.y*v1.z, v1.z*v2.x - v2.z*v1.x, v1.x*v2.y - v2.x*v1.y);
        }

        template <typename T> inline T length(const Vector3<T>& vec)
        {
            return (T)sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
        }

        template <typename T> inline T length2(const Vector3<T>& vec)
        {
            return vec.x*vec.x + vec.y*vec.y + vec.z*vec.z;
        }

        template <typename T> inline void normalize(Vector3<T>& vec)
        {
            T s = length(vec);
            vec.x /= s;
            vec.y /= s;
            vec.z /= s;
        }

        template <typename T> inline Vector3<T> lerp(const Vector3<T>& v1, const Vector3<T>& v2, T fact)
        {
            return v1 + (v2-v1)*fact;
        }
    }


    namespace vector4
    {

        template <typename T> inline T length(const Vector4<T>& vec)
        {
            return (T)sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z + vec.w*vec.w);
        }

        template <typename T> inline T length2(const Vector4<T>& vec)
        {
            return vec.x*vec.x + vec.y*vec.y + vec.z*vec.z + vec.w*vec.w;
        }

        template <typename T> inline void normalize(Vector4<T>& vec)
        {
            T s = length(vec);
            vec.x /= s;
            vec.y /= s;
            vec.z /= s;
            vec.w /= s;
        }

        template <typename T> inline Vector4<T> lerp(const Vector4<T>& v1, const Vector4<T>& v2, T fact)
        {
            return v1 + (v2-v1)*fact;
        }
    }


    namespace matrix3
    {
        template <typename T> inline void set_zero(Matrix3<T> &mat)
        {
            for (int i = 0; i < 9; i++)
                mat.data[i] = T(0);
        }

        template <typename T> inline void set_identity(Matrix3<T> &mat)
        {
            for (int i = 0; i < 9; i++)
                mat.data[i] = (i % 4) ? T(0) : T(1);
        }

        template <typename T> inline void transpose(Matrix3<T> &mat)
        {
            Matrix3<T> ret;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    ret.at(i, j) = mat.at(j, i);
                }
            }
            mat = ret;
        }

        template <typename T> inline Matrix3<T> lerp(const Matrix3<T>& m1, const Matrix3<T>& m2, T fact)
        {
            return m1 + (m2-m1)*fact;
        }

        template <typename T> inline T det(const Matrix3<T> &mat)
        {
            return mat.at(0,0) * mat.at(1,1) * mat.at(2,2) + mat.at(0,1) * mat.at(1,2) * mat.at(2,0) + mat.at(0,2) * mat.at(1,0) * mat.at(2,1)
                 - mat.at(0,0) * mat.at(1,2) * mat.at(2,1) - mat.at(0,1) * mat.at(1,0) * mat.at(2,2) - mat.at(0,2) * mat.at(1,1) * mat.at(2,0);
        }

        template <typename T> inline Matrix3<T> inverse(const Matrix3<T> &mat)
        {
            Matrix3<T> ret;
            ret.at(0,0) = mat.at(1,1) * mat.at(2,2) - mat.at(2,1) * mat.at(1,2);
            ret.at(0,1) = mat.at(2,1) * mat.at(0,2) - mat.at(0,1) * mat.at(2,2);
            ret.at(0,2) = mat.at(0,1) * mat.at(1,2) - mat.at(1,1) * mat.at(0,2);
            ret.at(1,0) = mat.at(2,0) * mat.at(1,2) - mat.at(1,0) * mat.at(2,2);
            ret.at(1,1) = mat.at(0,0) * mat.at(2,2) - mat.at(2,0) * mat.at(0,2);
            ret.at(1,2) = mat.at(1,0) * mat.at(0,2) - mat.at(0,0) * mat.at(1,2);
            ret.at(2,0) = mat.at(1,0) * mat.at(2,1) - mat.at(2,0) * mat.at(1,1);
            ret.at(2,1) = mat.at(2,0) * mat.at(0,1) - mat.at(0,0) * mat.at(2,1);
            ret.at(2,2) = mat.at(0,0) * mat.at(1,1) - mat.at(1,0) * mat.at(0,1);
            return ret * (1.0f / det(mat));
        }

    }

    namespace matrix4
    {
        template <typename T> inline void set_zero(Matrix4<T> &mat)
        {
            for (int i = 0; i < 16; i++)
                mat.data[i] = T(0);
        }

        template <typename T> inline void set_identity(Matrix4<T> &mat)
        {
            for (int i = 0; i < 16; i++)
                mat.data[i] = (i % 5) ? T(0) : T(1);
        }

        /// set translation part of matrix.
        template <typename T> inline void set_translation(Matrix4<T> &mat, const Vector3<T>& v)
        {
            mat.at(3,0) = v.x;
            mat.at(3,1) = v.y;
            mat.at(3,2) = v.z;
            mat.at(3,3) = 1;
        }
        /// get translation vector
        template <typename T> inline Vector3<T> translation(const Matrix4<T> &mat)
        {
            return Vector3<T>(mat.at(3,0), mat.at(3,1), mat.at(3,2));
        }
        /// set matrix rotation part
        template <typename T> inline void set_rotation(Matrix4<T> &mat, const Matrix3<T>& rot)
        {
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    mat.at(i, j) = rot.at(i, j);
                }
            }
        }
        /// determinant
        template <typename T> T det(const Matrix4<T> &m)
        {
            return m.at(3,0)*m.at(2,1)*m.at(1,2)*m.at(0,3) - m.at(2,0)*m.at(3,1)*m.at(1,2)*m.at(0,3) - m.at(3,0)*m.at(1,1)*m.at(2,2)*m.at(0,3) + m.at(1,0)*m.at(3,1)*m.at(2,2)*m.at(0,3)
                 + m.at(2,0)*m.at(1,1)*m.at(3,2)*m.at(0,3) - m.at(1,0)*m.at(2,1)*m.at(3,2)*m.at(0,3) - m.at(3,0)*m.at(2,1)*m.at(0,2)*m.at(1,3) + m.at(2,0)*m.at(3,1)*m.at(0,2)*m.at(1,3)
                 + m.at(3,0)*m.at(0,1)*m.at(2,2)*m.at(1,3) - m.at(0,0)*m.at(3,1)*m.at(2,2)*m.at(1,3) - m.at(2,0)*m.at(0,1)*m.at(3,2)*m.at(1,3) + m.at(0,0)*m.at(2,1)*m.at(3,2)*m.at(1,3)
                 + m.at(3,0)*m.at(1,1)*m.at(0,2)*m.at(2,3) - m.at(1,0)*m.at(3,1)*m.at(0,2)*m.at(2,3) - m.at(3,0)*m.at(0,1)*m.at(1,2)*m.at(2,3) + m.at(0,0)*m.at(3,1)*m.at(1,2)*m.at(2,3)
                 + m.at(1,0)*m.at(0,1)*m.at(3,2)*m.at(2,3) - m.at(0,0)*m.at(1,1)*m.at(3,2)*m.at(2,3) - m.at(2,0)*m.at(1,1)*m.at(0,2)*m.at(3,3) + m.at(1,0)*m.at(2,1)*m.at(0,2)*m.at(3,3)
                 + m.at(2,0)*m.at(0,1)*m.at(1,2)*m.at(3,3) - m.at(0,0)*m.at(2,1)*m.at(1,2)*m.at(3,3) - m.at(1,0)*m.at(0,1)*m.at(2,2)*m.at(3,3) + m.at(0,0)*m.at(1,1)*m.at(2,2)*m.at(3,3);
        }
        /// calc inverse matrix
        template <typename T> Matrix4<T> inverse(const Matrix4<T> &m)
        {
            Matrix4<T> ret;
            ret.at(0, 0) = m.at(2, 1)*m.at(3, 2)*m.at(1, 3) - m.at(3, 1)*m.at(2, 2)*m.at(1, 3) + m.at(3, 1)*m.at(1, 2)*m.at(2, 3) - m.at(1, 1)*m.at(3, 2)*m.at(2, 3) - m.at(2, 1)*m.at(1, 2)*m.at(3, 3) + m.at(1, 1)*m.at(2, 2)*m.at(3, 3);
            ret.at(1, 0) = m.at(3, 0)*m.at(2, 2)*m.at(1, 3) - m.at(2, 0)*m.at(3, 2)*m.at(1, 3) - m.at(3, 0)*m.at(1, 2)*m.at(2, 3) + m.at(1, 0)*m.at(3, 2)*m.at(2, 3) + m.at(2, 0)*m.at(1, 2)*m.at(3, 3) - m.at(1, 0)*m.at(2, 2)*m.at(3, 3);
            ret.at(2, 0) = m.at(2, 0)*m.at(3, 1)*m.at(1, 3) - m.at(3, 0)*m.at(2, 1)*m.at(1, 3) + m.at(3, 0)*m.at(1, 1)*m.at(2, 3) - m.at(1, 0)*m.at(3, 1)*m.at(2, 3) - m.at(2, 0)*m.at(1, 1)*m.at(3, 3) + m.at(1, 0)*m.at(2, 1)*m.at(3, 3);
            ret.at(3, 0) = m.at(3, 0)*m.at(2, 1)*m.at(1, 2) - m.at(2, 0)*m.at(3, 1)*m.at(1, 2) - m.at(3, 0)*m.at(1, 1)*m.at(2, 2) + m.at(1, 0)*m.at(3, 1)*m.at(2, 2) + m.at(2, 0)*m.at(1, 1)*m.at(3, 2) - m.at(1, 0)*m.at(2, 1)*m.at(3, 2);
            ret.at(0, 1) = m.at(3, 1)*m.at(2, 2)*m.at(0, 3) - m.at(2, 1)*m.at(3, 2)*m.at(0, 3) - m.at(3, 1)*m.at(0, 2)*m.at(2, 3) + m.at(0, 1)*m.at(3, 2)*m.at(2, 3) + m.at(2, 1)*m.at(0, 2)*m.at(3, 3) - m.at(0, 1)*m.at(2, 2)*m.at(3, 3);
            ret.at(1, 1) = m.at(2, 0)*m.at(3, 2)*m.at(0, 3) - m.at(3, 0)*m.at(2, 2)*m.at(0, 3) + m.at(3, 0)*m.at(0, 2)*m.at(2, 3) - m.at(0, 0)*m.at(3, 2)*m.at(2, 3) - m.at(2, 0)*m.at(0, 2)*m.at(3, 3) + m.at(0, 0)*m.at(2, 2)*m.at(3, 3);
            ret.at(2, 1) = m.at(3, 0)*m.at(2, 1)*m.at(0, 3) - m.at(2, 0)*m.at(3, 1)*m.at(0, 3) - m.at(3, 0)*m.at(0, 1)*m.at(2, 3) + m.at(0, 0)*m.at(3, 1)*m.at(2, 3) + m.at(2, 0)*m.at(0, 1)*m.at(3, 3) - m.at(0, 0)*m.at(2, 1)*m.at(3, 3);
            ret.at(3, 1) = m.at(2, 0)*m.at(3, 1)*m.at(0, 2) - m.at(3, 0)*m.at(2, 1)*m.at(0, 2) + m.at(3, 0)*m.at(0, 1)*m.at(2, 2) - m.at(0, 0)*m.at(3, 1)*m.at(2, 2) - m.at(2, 0)*m.at(0, 1)*m.at(3, 2) + m.at(0, 0)*m.at(2, 1)*m.at(3, 2);
            ret.at(0, 2) = m.at(1, 1)*m.at(3, 2)*m.at(0, 3) - m.at(3, 1)*m.at(1, 2)*m.at(0, 3) + m.at(3, 1)*m.at(0, 2)*m.at(1, 3) - m.at(0, 1)*m.at(3, 2)*m.at(1, 3) - m.at(1, 1)*m.at(0, 2)*m.at(3, 3) + m.at(0, 1)*m.at(1, 2)*m.at(3, 3);
            ret.at(1, 2) = m.at(3, 0)*m.at(1, 2)*m.at(0, 3) - m.at(1, 0)*m.at(3, 2)*m.at(0, 3) - m.at(3, 0)*m.at(0, 2)*m.at(1, 3) + m.at(0, 0)*m.at(3, 2)*m.at(1, 3) + m.at(1, 0)*m.at(0, 2)*m.at(3, 3) - m.at(0, 0)*m.at(1, 2)*m.at(3, 3);
            ret.at(2, 2) = m.at(1, 0)*m.at(3, 1)*m.at(0, 3) - m.at(3, 0)*m.at(1, 1)*m.at(0, 3) + m.at(3, 0)*m.at(0, 1)*m.at(1, 3) - m.at(0, 0)*m.at(3, 1)*m.at(1, 3) - m.at(1, 0)*m.at(0, 1)*m.at(3, 3) + m.at(0, 0)*m.at(1, 1)*m.at(3, 3);
            ret.at(3, 2) = m.at(3, 0)*m.at(1, 1)*m.at(0, 2) - m.at(1, 0)*m.at(3, 1)*m.at(0, 2) - m.at(3, 0)*m.at(0, 1)*m.at(1, 2) + m.at(0, 0)*m.at(3, 1)*m.at(1, 2) + m.at(1, 0)*m.at(0, 1)*m.at(3, 2) - m.at(0, 0)*m.at(1, 1)*m.at(3, 2);
            ret.at(0, 3) = m.at(2, 1)*m.at(1, 2)*m.at(0, 3) - m.at(1, 1)*m.at(2, 2)*m.at(0, 3) - m.at(2, 1)*m.at(0, 2)*m.at(1, 3) + m.at(0, 1)*m.at(2, 2)*m.at(1, 3) + m.at(1, 1)*m.at(0, 2)*m.at(2, 3) - m.at(0, 1)*m.at(1, 2)*m.at(2, 3);
            ret.at(1, 3) = m.at(1, 0)*m.at(2, 2)*m.at(0, 3) - m.at(2, 0)*m.at(1, 2)*m.at(0, 3) + m.at(2, 0)*m.at(0, 2)*m.at(1, 3) - m.at(0, 0)*m.at(2, 2)*m.at(1, 3) - m.at(1, 0)*m.at(0, 2)*m.at(2, 3) + m.at(0, 0)*m.at(1, 2)*m.at(2, 3);
            ret.at(2, 3) = m.at(2, 0)*m.at(1, 1)*m.at(0, 3) - m.at(1, 0)*m.at(2, 1)*m.at(0, 3) - m.at(2, 0)*m.at(0, 1)*m.at(1, 3) + m.at(0, 0)*m.at(2, 1)*m.at(1, 3) + m.at(1, 0)*m.at(0, 1)*m.at(2, 3) - m.at(0, 0)*m.at(1, 1)*m.at(2, 3);
            ret.at(3, 3) = m.at(1, 0)*m.at(2, 1)*m.at(0, 2) - m.at(2, 0)*m.at(1, 1)*m.at(0, 2) + m.at(2, 0)*m.at(0, 1)*m.at(1, 2) - m.at(0, 0)*m.at(2, 1)*m.at(1, 2) - m.at(1, 0)*m.at(0, 1)*m.at(2, 2) + m.at(0, 0)*m.at(1, 1)*m.at(2, 2);
            return ret/det(m);
        }
        /// transpose
        template <typename T> inline void transpose(Matrix4<T> &mat)
        {
            Matrix4<T> ret;
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                    ret.at(i, j) = mat.at(j, i);
            mat = ret;
        }
        /// create a translation matrix
        template <typename T> Matrix4<T> create_translation(const Vector3<T>& v)
        {
            Matrix4<T> ret;
            set_translation(ret, v);
            return ret;
        }

        /// create a transformation matrix
        template <typename T> Matrix4<T> create_transformation(const Vector3<T>& v, const Quaternion<T> &q)
        {
            Matrix4<T> ret = quaternion::transform(q);
            set_translation(ret, v);
            return ret;
        }

        template <typename T> Matrix4<T> create_lookat(const Vector3<T>& eye, const Vector3<T>& to, const Vector3<T>& up)
        {
            // set rotation using axis/angle
            Vector3<T> z(eye-to);
            vector3::normalize(z);
            Vector3<T> x = vector3::cross(up,z);
            vector3::normalize(x);
            Vector3<T> y = vector3::cross(z,x);

            Matrix4<T> m = create_translation(eye);
            m(1,1)=x.x; m(1,2)=y.x; m(1,3)=z.x;
            m(2,1)=x.y; m(2,2)=y.y; m(2,3)=z.y;
            m(3,1)=x.z; m(3,2)=y.z; m(3,3)=z.z;

            return m;
        }

        /// linear interpolation
        template <typename T> inline Matrix4<T> lerp(const Matrix4<T>& m1, const Matrix4<T>& m2, T fact)
        {
            return m1 + (m2-m1)*fact;
        }
    }

    namespace quaternion
    {
        template <typename T> inline T length(const Quaternion<T> &q)
        {
            return (T)sqrt(q.w*q.w + vector3::length2(q.v));
        }

        template <typename T> inline T length2(const Quaternion<T> &q)
        {
            return q.w*q.w + vector3::length2(q.v);
        }

        template <typename T> inline void normalize(Quaternion<T> &q)
        {
            T len = length(q);
            q.w /= len;
            q.v /= len;
        }

        template <typename T> inline Vector3<T> axis(const Quaternion<T> &q)
        {
            if (fabs(q.w-1)<EPSILON)
                return (Vector3<T>(1,0,0)); // arbitrary when there is no rotation!!
            Vector3<T> axis;
            axis.x = q.v.x / sqrt(1-q.w*q.w);
            axis.y = q.v.y / sqrt(1-q.w*q.w);
            axis.z = q.v.z / sqrt(1-q.w*q.w);
            return axis;
        }

        template <typename T> inline T angle(const Quaternion<T> &q)
        {
            return (T)(2*acos(q.w));
        }

        template <typename T> inline Quaternion<T> from_euler_321(T x, T y, T z)
        {
            Quaternion<T> ret = from_axis_angle(Vector3<T>(1, 0, 0), x) * from_axis_angle(Vector3<T>(0, 1, 0), y)
                              * from_axis_angle(Vector3<T>(0, 0, 1), z);
            return ret;
        }

        template <typename T> inline Quaternion<T> from_axis_angle(Vector3<T> axis, float angle)
        {
            T sa2 = (T)sin(angle/2);
            T ca2 = (T)cos(angle/2);
            return Quaternion<T>(ca2, axis*sa2);
        }

        template <typename T> Quaternion<T> from_matrix(const Matrix4<T>& m)
        {
            Quaternion<T> q;

            T tr, s;
            tr = m(1, 1) + m(2, 2) + m(3, 3);
            if (tr >= EPSILON)
            {
                s = (T)(0.5/sqrt(tr + 1.0));
                q.w = (T)(0.25/s);
                q.v.x = (m(3, 2) - m(2, 3)) * s;
                q.v.y = (m(1, 3) - m(3, 1)) * s;
                q.v.z = (m(2, 1) - m(1, 2)) * s;
            }
            else
            {
                T d0 = m(1, 1);
                T d1 = m(2, 2);
                T d2 = m(3, 3);

                char bigIdx = (d0 > d1) ? ((d0 > d2) ? 0 : 2):((d1 > d2) ? 1 : 2);

                if (bigIdx == 0)
                {
                    s = (T)(2.0*sqrt(1.0 + m(1, 1) - m(2, 2) - m(3, 3)));
                    q.w = (m(3, 2) - m(2, 3)) / s;
                    q.v.x = (T)(0.25*s);
                    q.v.y = (m(1, 2) + m(2, 1)) / s;
                    q.v.z = (m(1, 3) + m(3, 1)) / s;
                }
                else if (bigIdx == 1)
                {
                    s = (T)(2.0*sqrt(1.0 + m(2, 2) - m(1, 1) - m(3, 3)));
                    q.w = (m(1, 3) - m(3, 1)) / s;
                    q.v.x = (m(1, 2) + m(2, 1)) / s;
                    q.v.y = (T)(0.25*s);
                    q.v.z = (m(2, 3) + m(3, 2)) / s;
                }
                else
                {
                    s = (T)(2.0*sqrt(1.0 + m(3, 3) - m(1, 1) - m(2, 2)));
                    q.w = (m(2, 1) - m(1, 2)) / s;
                    q.v.x = (m(1, 3) + m(3, 1)) / s;
                    q.v.y = (m(2, 3) + m(3, 2)) / s;
                    q.v.z = (T)(0.25*s);
                }
            }

            return q;
        }

        template <typename T> Quaternion<T> from_matrix(const Matrix3<T>& m)
        {
            Quaternion<T> q;

            T tr, s;
            tr = m(1, 1) + m(2, 2) + m(3, 3);
            if (tr >= EPSILON)
            {
                s = T(0.5) / (T)sqrt(tr + 1.0);
                q.w = T(0.25) / s;
                q.v.x = (m(3, 2) - m(2, 3)) * s;
                q.v.y = (m(1, 3) - m(3, 1)) * s;
                q.v.z = (m(2, 1) - m(1, 2)) * s;
            }
            else
            {
                T d0 = m(1, 1);
                T d1 = m(2, 2);
                T d2 = m(3, 3);

                char bigIdx = (d0 > d1) ? ((d0 > d2) ? 0 : 2):((d1 > d2) ? 1 : 2);

                if (bigIdx == 0)
                {
                    s = T(2.0) * (T) sqrt(1.0 + m(1, 1) - m(2, 2) - m(3, 3));
                    q.w = (m(3, 2) - m(2, 3)) / s;
                    q.v.x = T(0.25) * s;
                    q.v.y = (m(1, 2) + m(2, 1)) / s;
                    q.v.z = (m(1, 3) + m(3, 1)) / s;
                }
                else if (bigIdx == 1)
                {
                    s = T(2.0) * (T) sqrt(1.0 + m(2, 2) - m(1, 1) - m(3, 3));
                    q.w = (m(1, 3) - m(3, 1)) / s;
                    q.v.x = (m(1, 2) + m(2, 1)) / s;
                    q.v.y = T(0.25) * s;
                    q.v.z = (m(2, 3) + m(3, 2)) / s;
                }
                else
                {
                    s = T(2.0) * (T) sqrt(1.0 + m(3, 3) - m(1, 1) - m(2, 2));
                    q.w = (m(2, 1) - m(1, 2)) / s;
                    q.v.x = (m(1, 3) + m(3, 1)) / s;
                    q.v.y = (m(2, 3) + m(3, 2)) / s;
                    q.v.z = T(0.25) * s;
                }
            }
            return q;
        }

        template <typename T> Matrix3<T> rot_matrix(const Quaternion<T> &q)
        {
            Matrix3<T> ret;
            const T &w = q.w;
            const Vector3<T> &v = q.v;
            T xx = v.x * v.x;
            T xy = v.x * v.y;
            T xz = v.x * v.z;
            T xw = v.x * w;
            T yy = v.y * v.y;
            T yz = v.y * v.z;
            T yw = v.y * w;
            T zz = v.z * v.z;
            T zw = v.z * w;

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

        template <typename T> Matrix4<T> transform(const Quaternion<T> &q)
        {
            Matrix4<T> ret;
            const T &w = q.w;
            const Vector3<T> &v = q.v;
            T xx = v.x * v.x;
            T xy = v.x * v.y;
            T xz = v.x * v.z;
            T xw = v.x * w;
            T yy = v.y * v.y;
            T yz = v.y * v.z;
            T yw = v.y * w;
            T zz = v.z * v.z;
            T zw = v.z * w;

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

        template <typename T> inline Quaternion<T> lerp(const Quaternion<T> &q1, const Quaternion<T> &q2, T fact)
        {
            return Quaternion<T>((1-fact)*q1.w + fact*q2.w, vector3::lerp(q1.v, q2.v, fact));
        }

        template <typename T> inline Quaternion<T> slerp(const Quaternion<T>& q1, const Quaternion<T>& q2, T r)
        {
            // Quaternion<T> ret;
            // T cosTheta = q1.w*q2.w + q1.v.x*q2.v.x + q1.v.y*q2.v.y + q1.v.z*q2.v.z;
            // T theta = (T) acos(cosTheta);
            // if (fabs(theta) < EPSILON)
            // {
            //     ret = q1;
            // }
            // else
            // {
            //     T sinTheta = (T) sqrt(1.0 - cosTheta*cosTheta);
            //     if (fabs(sinTheta) < EPSILON)
            //     {
            //         ret.w = (T)(0.5*q1.w + 0.5*q2.w);
            //         ret.v = vector3::lerp(q1.v, q2.v, 0.5f);
            //     }
            //     else
            //     {
            //         T rA = (T) sin((1.0-r)*theta) / sinTheta;
            //         T rB = (T) sin(r*theta) / sinTheta;

            //         ret.w   = q1.w*rA   + q2.w*rB;
            //         ret.v.x = q1.v.x*rA + q2.v.x*rB;
            //         ret.v.y = q1.v.y*rA + q2.v.y*rB;
            //         ret.v.z = q1.v.z*rA + q2.v.z*rB;
            //     }
            // }
            // return ret;
            // calc cosine theta
            T costheta = q1.v.x * q2.v.x + q1.v.y * q2.v.y + q1.v.z * q2.v.z + q1.w * q2.w;

            // adjust signs (if necessary)
            Quaternion<T> end = q2;
            if( costheta < static_cast<T>(0.0))
            {
                costheta = -costheta;
                end      = -end;   // Reverse all signs
            }

            // Calculate coefficients
            T sclp, sclq;
            if( (static_cast<T>(1.0) - costheta) > static_cast<T>(0.0001)) // some tolerance
            {
                // Standard case (slerp)
                T theta, sintheta;
                theta    = acos( costheta); // extract theta from dot product's cos theta
                sintheta = sin( theta);
                sclp     = sin( (static_cast<T>(1.0) - r) * theta) / sintheta;
                sclq     = sin( r * theta) / sintheta;
            } else
            {
                // Very close, do linear interp (because it's faster)
                sclp = static_cast<T>(1.0) - r;
                sclq = r;
            }

            Quaternion<T> out;
            out.v.x = sclp * q1.v.x + sclq * end.v.x;
            out.v.y = sclp * q1.v.y + sclq * end.v.y;
            out.v.z = sclp * q1.v.z + sclq * end.v.z;
            out.w   = sclp * q1.w   + sclq * end.w;

            return out;
        }

    }






    // ///////////////////////// //
    // Vector2<T> implementation //
    // ///////////////////////// //

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
        return (fabs(x - rhs.x) < EPSILON) && (fabs(y - rhs.y) < EPSILON);
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




    // ///////////////////////// //
    // Vector3<T> implementation //
    // ///////////////////////// //


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
        return fabs(x - rhs.x) < EPSILON && fabs(y - rhs.y) < EPSILON && fabs(z - rhs.z) < EPSILON;
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




    // ///////////////////////// //
    // Vector4<T> implementation //
    // ///////////////////////// //


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
        return fabs(x - rhs.x) < EPSILON && fabs(y - rhs.y) < EPSILON && fabs(z - rhs.z) < EPSILON && fabs(w - rhs.w) < EPSILON;
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



    // ///////////////////////// //
    // Matrix3<T> implementation //
    // ///////////////////////// //


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
            if (fabs(data[i] - rhs.data[i]) >= EPSILON)
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




    // ///////////////////////// //
    // Matrix4<T> implementation //
    // ///////////////////////// //


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
            if (fabs(data[i] - rhs.data[i]) >= EPSILON )
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




    // //////////////////////////// //
    // Quaternion<T> implementation //
    // //////////////////////////// //


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
        return (fabs(lhs.w - rhs.w) < EPSILON) && lhs.v == rhs.v;
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


}  // namespace math
