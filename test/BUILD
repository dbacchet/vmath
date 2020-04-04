filegroup(
    name = 'unit_test_files',
    srcs = ['test_vmath_types_vector2.cpp',
            'test_vmath_types_vector3.cpp',
            'test_vmath_types_vector4.cpp',
            'test_vmath_types_matrix3.cpp',
            'test_vmath_types_matrix4.cpp',
            'test_vmath_types_quaternion.cpp',
            'test_vmath_functions.cpp',
            'test_vmath_factories.cpp',
            'test_vmath.cpp',
           ],
)

# header-only version
cc_test(
    name = 'vmath_unit_test',
    srcs = [':unit_test_files'],
    deps = [
            '@googletest//:gtest_main',
            '//:vmath']
)

# precompiled version
cc_test(
    name = 'vmath_compiled_lib_unit_test',
    srcs = [':unit_test_files'],
    deps = [
            '@googletest//:gtest_main',
            '//:vmath_compiled_lib']
)
