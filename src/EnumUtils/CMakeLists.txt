add_library(EnumUtils enumUtils.cpp)
target_include_directories(EnumUtils PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(
  EnumUtils
  PUBLIC ppUtils
  PRIVATE project_options project_warnings)

if(ENABLE_TESTING)
  add_subdirectory(test)
endif()
