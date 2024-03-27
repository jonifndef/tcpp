cmake_minimum_required(VERSION 3.2)

project(tcpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

add_executable(${PROJECT_NAME})

add_subdirectory(src)
add_subdirectory(external/spdlog)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)
