cmake_minimum_required(VERSION 3.5)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.12.1.zip
)

set(GOOGLETEST_ROOT ${CMAKE_BINARY_DIR}/_deps/googletest-src)
include_directories(${GOOGLETEST_ROOT}/googlemock/include)
include_directories(${GOOGLETEST_ROOT}/googletest/include)

FetchContent_MakeAvailable(googletest)
include(GoogleTest)
enable_testing()

add_executable(
  ethernetframe_test
  ethernetframe_test.cc
)

target_include_directories(ethernetframe_test PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(
  ethernetframe_test
  PRIVATE
  tcpp_lib
  GTest::gtest_main
  spdlog::spdlog
  morrisfranken::argparse
)

gtest_discover_tests(ethernetframe_test)
