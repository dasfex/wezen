cmake_minimum_required(VERSION 3.21)
project(calcom)

set(CMAKE_CXX_STANDARD 20)

add_executable(calcom tests.cpp includes/minmax.hpp includes/math.hpp)
