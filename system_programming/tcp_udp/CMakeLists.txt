cmake_minimum_required(VERSION 3.17)
project(tcp_udp)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_library(utils tcp_udp_utils.cpp)


add_executable(tcp_server tcp_server.cpp)
add_executable(tcp_client tcp_client.cpp)
add_executable(pong_udp pong_udp.cpp)
add_executable(ping_udp ping_udp.cpp)
add_executable(rbo_serv broadcast_udp.cpp)

target_link_libraries(tcp_server pthread utils)
target_link_libraries(tcp_client utils)
target_link_libraries(pong_udp utils)
target_link_libraries(ping_udp utils)
target_link_libraries(rbo_serv utils)

