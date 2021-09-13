file(GLOB_RECURSE SOURCES_SYSTEMS_FRAMEWORK RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cc)

add_library(framework ${SOURCES_SYSTEMS_FRAMEWORK})

add_library(maliput_drake::systems::framework ALIAS framework)

set_target_properties(
  framework
  PROPERTIES
    OUTPUT_NAME ${PROJECT_NAME}_systems_framework
)

target_include_directories(
  framework
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(
  framework
    fmt::fmt
    Eigen3::Eigen
    maliput_drake::common
    maliput_drake::math
    maliput_drake::systems::framework
)

install(
  TARGETS framework
  EXPORT ${PROJECT_NAME}-targets
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
