include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(mandelbrot_test
  "test_argument_parse.cpp"
  "test_canvas.cpp"
  "test_claiming.cpp"
  "test_color.cpp"
  "test_color_calculator.cpp"
  "test_mandelbrot_equation.cpp"
)


target_link_libraries(mandelbrot_test
  GTest::gtest_main
  plot_lib
)

include(GoogleTest)
gtest_discover_tests(mandelbrot_test)
