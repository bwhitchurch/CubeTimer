find_package(Catch2 CONFIG REQUIRED)

include(Catch)

add_executable(fooTest fooTest.cpp)
target_link_libraries(fooTest PRIVATE foo Catch2::Catch2WithMain
                                      project_options project_warnings)

set_target_properties(fooTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                         "${CMAKE_TEST_OUTPUT_DIRECTORY}")

catch_discover_tests(
  fooTest
  TEST_PREFIX
  "libfoo."
  REPORTER
  XML
  OUTPUT_DIR
  .
  OUTPUT_PREFIX
  "libfoo."
  OUTPUT_SUFFIX
  .xml)
