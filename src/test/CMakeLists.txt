find_package(Catch2 CONFIG REQUIRED)

include(Catch)

add_executable(scramblerTest scramblerTest.cpp)
target_link_libraries(scramblerTest PRIVATE scrambler Catch2::Catch2WithMain
                                            project_options project_warnings)

set_target_properties(scramblerTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                               "${CMAKE_TEST_OUTPUT_DIRECTORY}")

catch_discover_tests(
  scramblerTest
  TEST_PREFIX
  "libscrambler."
  REPORTER
  XML
  OUTPUT_DIR
  .
  OUTPUT_PREFIX
  "libscrambler."
  OUTPUT_SUFFIX
  .xml)
