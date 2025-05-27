cmake_minimum_required(VERSION 3.5)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  ethernetframe_test
  ethernetframe_test.cc
  ../src/ethernet-frame.cpp
  ../src/arp.cpp
)

# Add include directories for the test target
target_include_directories(ethernetframe_test PRIVATE
    ${CMAKE_SOURCE_DIR}/include  # For public headers
)

target_link_libraries(
  ethernetframe_test
  GTest::gtest_main
  #$<TARGET_OBJECTS:tcpp>  # Link with main project's objects
  spdlog::spdlog
  morrisfranken::argparse
)

include(GoogleTest)
