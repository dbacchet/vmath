# vmath
Minimalistic math library with 2/3/4-dimensional vectors, matrices and quaternions

[![Build Status](https://github.com/dbacchet/vmath/workflows/build/badge.svg)](https://github.com/dbacchet/vmath/actions?query=workflow%3Abuild+branch%3Amaster)
[![Coverage Status](https://coveralls.io/repos/github/dbacchet/vmath/badge.svg?branch=master)](https://coveralls.io/github/dbacchet/vmath?branch=master)

This is the rewrite of a library that I used for several years in both personal and professional projects. It's supposed to be 
stable, but if you find any bug or want to contribute bugfixes and improvements feel free to open an issue or a pull request!

## Design

The Vector2/3/4, Matrix2/3/4 and Quaternion classes are minimalistic by design. They only contain setters, accessors and operators;
everything else is implemented as external functions and factories in order to provide more consistency between the functionality that 
is packaged in the library and custom extensions.

The data in the `Vector` classes is accessible using either `x`/`y`/`z` or `r`/`g`/`b` notation, to support both math and color/texture notations.

The data in the `Matrix` classes is stored internally in column-major order, compatible with the default of many graphics API.

I't possible to pass directly a `Vector`/`Matrix` in functions that accept a pointer (like OpenGL); for example:
```
math::Matrix4f transform = math::factory::create_transformation(math::Vector3f(10,1,0),                                             // offset
                                                               math::factory::quat_from_axis_angle(math::Vector3f(0,0,1), M_PI/3)); // orientation
glUniformMatrix4fv(uniform_id, 1, GL_FALSE, transform);
```
 
## Installation

Vmath is header-only. In order to use it just copy the files in the `include` folder in your project and you are good to go. 

### precompiled version

It's also possible to use a precompiled version, with the benefit of faster compilation time. To use it, you have to:
1. define `VMATH_COMPILED_LIB` in your project
2. compile the file `vmath_compiled_lib.cpp`

That file declares the classes for the most common types (explicit template instantiation): `int8_t`, `int32_t`, `int64_t`, `float`, `double`.
In case you are using the precompiled version and you need other types, they can easily be added to the same file.

