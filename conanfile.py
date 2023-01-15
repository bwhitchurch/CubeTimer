from conans import CMake, ConanFile


class cube_timer_conan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = "fmt/9.1.0", "spdlog/1.11.0", "catch2/3.2.1"
    generators = "cmake", "gcc", "txt"
    default_options = {"fmt:header_only": True, "spdlog:header_only": True,
                       "catch2:fPIC": True, "catch2:shared": True}
