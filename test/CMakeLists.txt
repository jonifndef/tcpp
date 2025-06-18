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

add_subdirectory(unit_tests)
