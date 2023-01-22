add_executable(cubeTimer++ cubeTimer++.cpp)
target_link_libraries(cubeTimer++ CLI11::CLI11 fmt::fmt spdlog::spdlog
                      scrambler)
target_include_directories(
  cubeTimer++ PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include")
