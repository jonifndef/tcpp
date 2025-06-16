add_library("${PROJECT_NAME}_lib"
    arp-handler.cpp
    arp-table.cpp
    arp.cpp
    ethernet-frame.cpp
    ip-datagram.cpp
    tap-device.cpp
    tcpp.cpp
)

target_include_directories("${PROJECT_NAME}_lib" PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries("${PROJECT_NAME}_lib" PUBLIC spdlog::spdlog morrisfranken::argparse)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE "${PROJECT_NAME}_lib")
