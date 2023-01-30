add_executable(enumUtilsTest enumUtilsTest.cpp)
target_link_libraries(enumUtilsTest PUBLIC Catch2::Catch2WithMain EnumUtils
                                           fmt::fmt)
target_link_libraries(enumUtilsTest PRIVATE project_options project_warnings)
set_target_properties(enumUtilsTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                               "${CMAKE_TEST_OUTPUT_DIRECTORY}")

include(Catch)
catch_discover_tests(
  enumUtilsTest
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
