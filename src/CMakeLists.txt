add_library(scrambler scrambler.cpp)
target_include_directories(scrambler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(scrambler PROPERTIES PUBLIC_HEADER
                                           "scrambler.hpp;enum.hpp")
target_link_libraries(
  scrambler
  PUBLIC project_options project_warnings
  PRIVATE fmt::fmt spdlog::spdlog)

target_include_directories(
  scrambler PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include")

install(
  TARGETS scrambler
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  PUBLIC_HEADER DESTINATION include)

if(ENABLE_TESTING)
  add_subdirectory(test)
endif()
