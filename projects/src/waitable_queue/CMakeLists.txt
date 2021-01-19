cmake_minimum_required(VERSION 3.13)
project(waitable_queue)

set(CMAKE_CXX_STANDARD 98)

include_directories(. ../../include)

add_executable(waitable_queue proj_utils.cpp waitable_queue_test.cpp)

target_link_libraries(waitable_queue boost_system boost_chrono boost_thread)