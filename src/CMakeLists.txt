find_package(SDL2 REQUIRED)
find_package(Eigen3 REQUIRED)
 find_package(unofficial-concurrentqueue CONFIG REQUIRED)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(COMPILER_FLAGS
        -Wall -Wextra -Werror
    )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(COMPILER_FLAGS
       "/W3" "/WX" "/external:anglebrackets" "/external:W0"
    )
endif()

message(STATUS ${COMPILER_FLAGS})

add_library(plot_lib
    STATIC
    "canvas.cpp"
    "color.cpp"
    "color_calculator.cpp"
    "fractal_view.cpp"
    "mandelbrot.cpp"
    "parallel_calculator.cpp"
    "simple_calculator.cpp"
    "claim_matrix.cpp"
)

target_compile_options(plot_lib
    PRIVATE
    ${COMPILER_FLAGS}    
)

target_compile_definitions(plot_lib
    PUBLIC
    SDL_MAIN_HANDLED
)    

target_include_directories(plot_lib
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_link_libraries(plot_lib
    PUBLIC
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
    Eigen3::Eigen
     unofficial::concurrentqueue::concurrentqueue
)

add_executable(${PROJECT_NAME}
    "main.cpp"
)

target_compile_options(${PROJECT_NAME}
    PRIVATE
    ${COMPILER_FLAGS}    
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    plot_lib
)
