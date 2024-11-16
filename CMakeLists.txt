cmake_minimum_required(VERSION 3.20)
project(mandel_plot
    DESCRIPTION "A fast mandelbrot plotter"
    VERSION 0.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)


enable_testing()
add_subdirectory(test)
