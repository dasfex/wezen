cmake_minimum_required(VERSION 3.21)
project(wezen)

set(CMAKE_CXX_STANDARD 20)

add_executable(wezen tests.cpp includes/minmax.hpp includes/math.hpp wezen.hpp)
