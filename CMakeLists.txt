cmake_minimum_required(VERSION 3.21)
project(wezen)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DTEST")

add_executable(wezen playground.cpp wezen.hpp
        includes/math/basics.hpp includes/math.hpp includes/math/fib.hpp)
