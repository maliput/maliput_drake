file(GLOB_RECURSE SOURCES_SYSTEMS_ANALYSIS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cc)

add_library(analysis ${SOURCES_SYSTEMS_ANALYSIS})

add_library(maliput_drake::analysis ALIAS analysis)

set_target_properties(
  analysis
  PROPERTIES
    OUTPUT_NAME ${PROJECT_NAME}_analysis
)

target_include_directories(
  analysis
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(
  analysis
    fmt::fmt
    Eigen3::Eigen
    maliput_drake::common
    maliput_drake::math
    maliput_drake::framework
)

install(
  TARGETS analysis
  EXPORT ${PROJECT_NAME}-targets
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
