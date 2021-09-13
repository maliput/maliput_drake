file(GLOB_RECURSE SOURCES_COMMON_TRAJECTORIES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cc)

add_library(trajectories ${SOURCES_COMMON_TRAJECTORIES})

add_library(maliput_drake::trajectories ALIAS trajectories)

set_target_properties(
  trajectories
  PROPERTIES
    OUTPUT_NAME ${PROJECT_NAME}_trajectories
)

target_include_directories(
  trajectories
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(
  trajectories
    Eigen3::Eigen
    fmt::fmt
    maliput_drake::common
    maliput_drake::math
)

install(
  TARGETS trajectories
  EXPORT ${PROJECT_NAME}-targets
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
