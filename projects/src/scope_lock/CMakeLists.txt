cmake_minimum_required(VERSION 3.17)
project(scope_lock)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(scope_lock_test
        scope_lock_test.cpp)

target_link_libraries(scope_lock_test boost_system boost_thread)