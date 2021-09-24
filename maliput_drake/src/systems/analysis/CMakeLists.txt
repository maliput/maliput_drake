add_library(analysis
  antiderivative_function.cc
  bogacki_shampine3_integrator.cc
  dense_output.cc
  explicit_euler_integrator.cc
  hermitian_dense_output.cc
  implicit_euler_integrator.cc
  implicit_integrator.cc
  initial_value_problem.cc
  integrator_base.cc
  monte_carlo.cc
  radau_integrator.cc
  runge_kutta2_integrator.cc
  runge_kutta3_integrator.cc
  runge_kutta5_integrator.cc
  scalar_dense_output.cc
  scalar_initial_value_problem.cc
  scalar_view_dense_output.cc
  semi_explicit_euler_integrator.cc
  simulator.cc
  simulator_config.cc
  simulator_config_functions.cc
  simulator_gflags.cc
  simulator_status.cc
  stepwise_dense_output.cc
  velocity_implicit_euler_integrator.cc
)

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
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(
  analysis
    Eigen3::Eigen
    fmt::fmt
    gflags
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
