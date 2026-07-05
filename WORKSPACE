workspace(name = "vmath")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")


http_archive(
    name = "googletest",
    urls = ["https://github.com/google/googletest/archive/release-1.12.1.tar.gz"],
    sha256 = "81964fe578e9bd7c94dfdb09c8e4d6e6759e19967e397dbea48d1c10e45d0df2",
    strip_prefix = "googletest-release-1.12.1",
)

http_archive(
    name = "eigen",
    urls = ["https://gitlab.com/libeigen/eigen/-/archive/3.3.7/eigen-3.3.7.tar.gz"],
    sha256 = "7e84ef87a07702b54ab3306e77cea474f56a40afa1c0ab245bb11725d006d0da",
    build_file = "//var/bazel:BUILD.eigen",
)

