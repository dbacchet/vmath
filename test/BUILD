filegroup(
    name = 'unit_test_files',
    srcs = ['test_vmath_types.cpp',
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
