cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS ON)

set(ENABLE_DEVELOPER_MODE
    TRUE
    CACHE BOOL "Enable 'develeoper mode'")

set(OPT_WARNINGS_AS_ERRORS_DEVELOPER_DEFAULT TRUE)

include(FetchContent)
FetchContent_Declare(
  _project_options
  GIT_REPOSITORY https://github.com/aminya/project_options.git
  GIT_TAG origin/main)

FetchContent_MakeAvailable(_project_options)

include(${_project_options_SOURCE_DIR}/Index.cmake)

project(
  CubeTimer++
  VERSION 0.0.1
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

include(${_project_options_SOURCE_DIR}/src/DynamicProjectOptions.cmake)

dynamic_project_options(
  ENABLE_CONAN
  CPPCHECK_OPTIONS
  --enable=style,performance,warning,portability
  --inline-suppr
  --suppress=cppcheckError
  --suppress=internalAstError
  --suppress=unmatchedSuppression
  --suppress=passedByValue
  --suppress=syntaxError
  --inconclusive)

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

add_subdirectory(configured_files)

add_subdirectory(src)

add_subdirectory(app)
