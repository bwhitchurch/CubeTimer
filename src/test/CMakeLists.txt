add_executable(scramblerTest scramblerTest.cpp)
target_link_libraries(scramblerTest PRIVATE scrambler Catch2::Catch2WithMain
                                            project_options project_warnings)

set_target_properties(scramblerTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                               "${CMAKE_TEST_OUTPUT_DIRECTORY}")

add_executable(cubeTest cubeTest.cpp)
target_link_libraries(cubeTest PRIVATE scrambler Catch2::Catch2WithMain
                                       project_options project_warnings)

set_target_properties(cubeTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                          "${CMAKE_TEST_OUTPUT_DIRECTORY}")

include(Catch)

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
catch_discover_tests(
  cubeTest
  TEST_PREFIX
  "cube."
  REPORTER
  XML
  OUTPUT_DIR
  .
  OUTPUT_PREFIX
  "cube."
  OUTPUT_SUFFIX
  .xml)
