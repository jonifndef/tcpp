cmake_minimum_required(VERSION 3.16)

project(tcpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

add_subdirectory(src)
add_subdirectory(external/spdlog)
add_subdirectory(external/argparse)
add_subdirectory(test)
