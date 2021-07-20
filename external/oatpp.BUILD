package(default_visibility = ["//visibility:public"])

filegroup(
    name = "hdrs",
    srcs = glob(["src/oatpp/**"]),
)

cc_library(
    name = "oatpp",
    srcs = [":hdrs"],
    hdrs = [":hdrs"],
    includes = ["src/"],
)
