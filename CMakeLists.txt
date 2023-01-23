cmake_minimum_required(VERSION 3.23)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_C_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_TEST_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests)

set(ENABLE_DEVELOPER_MODE
    TRUE
    CACHE BOOL "Enable 'develeoper mode'")

set(OPT_WARNINGS_AS_ERRORS_DEVELOPER_DEFAULT TRUE)
set(BUILD_SHARED_LIBS
    TRUE
    CACHE BOOL "Build shared libraries")

include(FetchContent)
FetchContent_Declare(
  _project_options
  GIT_REPOSITORY https://github.com/aminya/project_options.git
  GIT_TAG origin/main)

FetchContent_MakeAvailable(_project_options)

include(${_project_options_SOURCE_DIR}/Index.cmake)

project(
  CubeTimer++
  VERSION 0.1.0
  DESCRIPTION "A rubik's cube timer and scrambler app"
  HOMEPAGE_URL "https://github.com/bwhitchurch/cubeTimer"
  LANGUAGES CXX C)

if(PROJECT_IS_TOP_LEVEL)
  include(CTest)
endif()

set(GIT_SHA
    "Unknown"
    CACHE STRING "SHA from which this build was generated")
string(SUBSTRING "${GIT_SHA}" 0 8 GIT_SHORT_SHA)

set(CMAKE_CONFIGURATION_TYPES
    ${CMAKE_BUILD_TYPE}
    CACHE STRING "Enabled
build types" FORCE)

set(DOXYGEN_EXCLUDE_PATTERNS conanfile.py ${CMAKE_BINARY_DIR}/_deps/*)
set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/docs)
set(DOXYGEN_WARN_LOGFILE ${CMAKE_BINARY_DIR}/docs/UNDOCUMENTED.log)
set(DOXYGEN_EXTRACT_ALL NO)
set(DOXYGEN_DOT_IMAGE_FORMAT svg)
set(DOXYGEN_INTERACTIVE_SVG YES)
set(DOXYGEN_WARNINGS YES)
set(DOXYGEN_WARN_IF_UNDOCUMENTED YES)
set(DOXYGEN_WARN_NO_PARAMDOC YES)

option(ENABLE_COVERAGE "Enable coverage flags" OFF)
if(ENABLE_COVERAGE)
  set(ENABLE_COVERAGE "ENABLE_COVERAGE")
endif()

option(ENABLE_DOXYGEN "Build the doxygen documentation" OFF)
if(ENABLE_DOXYGEN)
  set(ENABLE_DOXYGEN "ENABLE_DOXYGEN")
endif()

option(ENABLE_INCLUDE_WHAT_YOU_USE "Enable iwyu parsing of #includes" OFF)
if(ENABLE_INCLUDE_WHAT_YOU_USE)
  set(ENABLE_INCLUDE_WHAT_YOU_USE "ENABLE_INCLUDE_WHAT_YOU_USE")
endif()
include(${_project_options_SOURCE_DIR}/src/DynamicProjectOptions.cmake)

dynamic_project_options(
  ENABLE_CONAN
  ${ENABLE_DOXYGEN}
  ${ENABLE_COVERAGE}
  ${ENABLE_INCLUDE_WHAT_YOU_USE}
  CPPCHECK_OPTIONS
  --enable=style,performance,warning,portability
  --inline-suppr
  --suppress=cppcheckError
  --suppress=internalAstError
  --suppress=unmatchedSuppression
  --suppress=passedByValue
  --suppress=syntaxError
  --inconclusive)

if(ENABLE_INCLUDE_WHAT_YOU_USE)
  set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE
      "${CMAKE_CXX_INCLUDE_WHAT_YOU_USE}"
      "-w"
      "-Xiwyu;--mapping-file=${CMAKE_SOURCE_DIR}/project_mappings.imp"
      "-Xiwyu;--check_also=${CMAKE_SOURCE_DIR}/\*.hpp"
      "-Xiwyu;quoted_includes_first"
      "-Xiwyu;--cxx17ns")
endif()

target_compile_features(project_options INTERFACE cxx_std_${CMAKE_CXX_STANDARD})
add_library(CubeTimer++::project_options INTERFACE IMPORTED)
add_library(CubeTimer++::project_warnings INTERFACE IMPORTED)

option(ENABLE_TESTING "Enable the tests" ${PROJECT_IS_TOP_LEVEL})
if(ENABLE_TESTING)
  enable_testing()
endif()

option(ENABLE_FUZZING "Enable fuzz tests" OFF)
if(ENABLE_FUZZING)

endif()

find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(CLI11 CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)

add_subdirectory(configured_files)

add_subdirectory(src)

add_subdirectory(app)

set(CPACK_PACKAGE_FILE_NAME
    "${CMAKE_PROJECT_NAME}-${CMAKE_PROJECT_VERSION}-${GIT_SHORT_SHA}-${CMAKE_SYSTEM_NAME}-${CMAKE_BUILD_TYPE}-${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}"
)
include(CPack)
