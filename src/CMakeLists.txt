find_package(SDL2 REQUIRED)

add_executable(${PROJECT_NAME}
    "main.cpp"
    "fractal_view.cpp"
)

target_compile_definitions(${PROJECT_NAME}
    PUBLIC
    SDL_MAIN_HANDLED
)
    

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)
