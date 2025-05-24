cmake_minimum_required(VERSION 3.5)

project(tcpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME})

add_subdirectory(src)
add_subdirectory(external/spdlog)
add_subdirectory(external/argparse)

target_include_directories(${PROJECT_NAME} PRIVATE include)
#target_include_directories(${PROJECT_NAME} PRIVATE external/argparse/include)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog morrisfranken::argparse)

enable_testing()

add_executable(
  ethernetframe_test
  test/ethernetframe_test.cc
)
target_link_libraries(
  ethernetframe_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(ethernetframe_test)
