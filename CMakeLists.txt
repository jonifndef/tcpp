cmake_minimum_required(VERSION 3.5)

project(tcpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

add_executable(${PROJECT_NAME})

add_subdirectory(src)
add_subdirectory(external/spdlog)
add_subdirectory(external/argparse)
add_subdirectory(test)

target_include_directories(${PROJECT_NAME} PRIVATE include)
#target_include_directories(${PROJECT_NAME} PRIVATE external/argparse/include)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog morrisfranken::argparse)
