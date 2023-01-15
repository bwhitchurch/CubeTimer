add_executable(cubeTimer++ cubeTimer++.cpp)
target_link_libraries(cubeTimer++ CONAN_PKG::fmt CONAN_PKG::spdlog)
