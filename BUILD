cc_library(
    name = 'vmath',
    hdrs = [
            'include/vmath_types.h',
            'include/vmath_types_impl.h',
            'include/vmath.h',
           ],
    strip_include_prefix = 'include',
    linkstatic = True,
    visibility = ["//visibility:public"],
)

cc_library(
    name = 'vmath_compiled_lib',
    hdrs = [
            'include/vmath_types.h',
            'include/vmath_types_impl.h',
            'include/vmath.h',
           ],
    srcs = [
            'src/vmath_compiled_lib.cpp',
           ],
    defines = ['VMATH_COMPILED_LIB'],
    strip_include_prefix = 'include',
    linkstatic = True,
    visibility = ["//visibility:public"],
)

