file(GLOB_RECURSE SOURCES_MATH RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cc)

add_library(math ${SOURCES_MATH})

add_library(maliput_drake::math ALIAS math)

set_target_properties(
  math
  PROPERTIES
    OUTPUT_NAME ${PROJECT_NAME}_math
)

target_include_directories(
  math
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(
  math
    Eigen3::Eigen
    fmt::fmt
    maliput_drake::common
)

install(
  TARGETS math
  EXPORT ${PROJECT_NAME}-targets
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
