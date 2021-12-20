cmake_minimum_required(VERSION 3.21)
project(wezen VERSION 1.0 LANGUAGES CXX)

get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)

option(WEZEN_TESTING "Включить статическое тестирование" ON)

add_compile_options(
        -Werror

        -Wall
        -Wextra
        -Wpedantic

        -Wcast-align
        -Wcast-qual
        -Wconversion
        -Wctor-dtor-privacy
        -Wenum-compare
        -Wfloat-equal
        -Wold-style-cast
        -Wredundant-decls
        -Wsign-conversion
        -Wsign-promo
)

if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DTEST")

add_executable(wezen playground.cpp wezen.hpp
        includes/math/math_basics.hpp
        includes/math.hpp
        includes/math/fib.hpp
        includes/traits/traits_basics.hpp
        includes/traits.hpp)
