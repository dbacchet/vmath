load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = 'benchmark_transform',
    srcs = ['benchmark_transform.cpp'],
    deps = ['//:vmath',
           ]
)

cc_binary(
    name = 'vmath_benchmark',
    srcs = ['vmath_benchmark.cpp', 'benchmark_util.h'],
    deps = ['//:vmath'],
)
