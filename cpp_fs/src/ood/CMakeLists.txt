cmake_minimum_required(VERSION 3.17)
project(ood)

set(CMAKE_CXX_STANDARD 98)

include_directories(.)

add_executable(ood
        ood.cpp
        ood.hpp
        ood_test.cpp)
