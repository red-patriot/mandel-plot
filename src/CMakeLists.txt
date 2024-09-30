find_package(SDL2 REQUIRED)
find_package(Eigen3 REQUIRED)

add_library(plot_lib
    STATIC
    "fractal_view.cpp"
    "canvas.cpp"
    "color.cpp"
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
)

add_executable(${PROJECT_NAME}
    "main.cpp"
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    plot_lib
)
