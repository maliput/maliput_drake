ament_add_gtest(saturate_test saturate_test.cc)

macro(add_dependencies_to_test target)
    if (TARGET ${target})

      target_include_directories(${target}
        PRIVATE
          ${PROJECT_SOURCE_DIR}/include
          ${CMAKE_CURRENT_SOURCE_DIR}
          ${PROJECT_SOURCE_DIR}/test
      )

      target_link_libraries(
        ${target}
          maliput_drake::analysis
          maliput_drake::common
          maliput_drake::framework
          maliput_drake::math
          maliput_drake::trajectories
      )

    endif()
endmacro()

add_dependencies_to_test(saturate_test)