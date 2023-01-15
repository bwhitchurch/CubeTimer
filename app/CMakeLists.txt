find_package(fmt CONFIG)
find_package(spdlog CONFIG)
find_package(CLI11 CONFIG REQUIRED)

add_executable(cubeTimer++ cubeTimer++.cpp)
target_link_libraries(cubeTimer++ CLI11::CLI11 fmt::fmt spdlog::spdlog foo)
target_include_directories(
  cubeTimer++ PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include")
