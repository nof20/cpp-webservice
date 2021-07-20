load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "rules_foreign_cc",
    sha256 = "e14a159c452a68a97a7c59fa458033cc91edb8224516295b047a95555140af5f",
    strip_prefix = "rules_foreign_cc-0.4.0",
    url = "https://github.com/bazelbuild/rules_foreign_cc/archive/0.4.0.tar.gz",
)

load("@rules_foreign_cc//foreign_cc:repositories.bzl", "rules_foreign_cc_dependencies")

rules_foreign_cc_dependencies()

http_archive(
    name = "oatpp",
    build_file = "oatpp.BUILD",
    sha256 = "21cfea0f254f0016b878dae2056286e203e9a78e7a4a413cb5524a7406ac36ff",
    strip_prefix = "oatpp-1.2.5",
    url = "https://github.com/oatpp/oatpp/archive/refs/tags/1.2.5.zip",
)
