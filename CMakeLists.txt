cmake_minimum_required(VERSION 3.21)
project(wezen)

set(CMAKE_CXX_STANDARD 17)

add_executable(wezen tests.cpp wezen.hpp
        includes/minmax.hpp includes/math.hpp)
