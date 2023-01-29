add_executable(ppUtilsTest ppUtilsTest.cpp)
target_link_libraries(ppUtilsTest PUBLIC Catch2::Catch2WithMain fmt::fmt
                                         ppUtils)
target_link_libraries(ppUtilsTest PRIVATE project_options project_warnings)
set_target_properties(ppUtilsTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                             "${CMAKE_TEST_OUTPUT_DIRECTORY}")

include(Catch)
catch_discover_tests(
  ppUtilsTest
  TEST_PREFIX
  "libEnumUtils."
  REPORTER
  XML
  OUTPUT_DIR
  .
  OUTPUT_PREFIX
  "libEnumUtils."
  OUTPUT_SUFFIX
  .xml)
