function(add_test test_name)
  add_executable(
    ${test_name}
    ${test_name}.cc
  )

  target_include_directories(${test_name} PRIVATE ${CMAKE_SOURCE_DIR}/include)

  target_link_libraries(
    ${test_name}
    PRIVATE
    tcpp_lib
    GTest::gtest_main
    spdlog::spdlog
    morrisfranken::argparse
  )

  gtest_discover_tests(${test_name})
endfunction()

add_test(ethernetframe_test)
add_test(arppacket_test)
