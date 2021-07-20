load("@rules_foreign_cc//foreign_cc:defs.bzl", "cmake")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "all",
    srcs = glob(["**"]),
)

cmake(
    name = "oatpp",
    cache_entries = {
        "OATPP_BUILD_TESTS": "OFF",
    },
    env = {
        "DESTDIR": "${INSTALLDIR}",
    },
    lib_source = ":all",
    out_headers_only = True,
)
