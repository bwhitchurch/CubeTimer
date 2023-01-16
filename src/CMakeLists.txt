find_package(fmt CONFIG)
find_package(spdlog CONFIG)

add_library(foo foo.cpp)
target_link_libraries(
  foo
  PUBLIC project_options project_warnings
  PRIVATE fmt::fmt spdlog::spdlog)

target_include_directories(
  foo PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include")

if(ENABLE_TESTING)
  add_subdirectory(test)
endif()
