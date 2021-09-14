file(GLOB_RECURSE SOURCES_COMMON RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cc)

add_library(common ${SOURCES_COMMON})

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
    fmt::fmt
    Eigen3::Eigen
)

install(
  TARGETS common
  EXPORT ${PROJECT_NAME}-targets
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)

ament_export_libraries(common)

add_subdirectory(trajectories)