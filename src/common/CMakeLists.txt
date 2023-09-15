add_library(common
  drake_assert_and_throw.cc
  hash.cc
  nice_type_name.cc
  nice_type_name_override.cc
  pointer_cast.cc
  polynomial.cc
  random.cc
  text_logging.cc
  value.cc
)

add_library(maliput_drake::common ALIAS common)

set_target_properties(
  common
  PROPERTIES
    OUTPUT_NAME ${PROJECT_NAME}_common
)

target_include_directories(
  common
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(
  common
    dl
    Eigen3::Eigen
    fmt::fmt
)

install(
  TARGETS common
  EXPORT ${PROJECT_NAME}-targets
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)

add_subdirectory(trajectories)