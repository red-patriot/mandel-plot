#include <tuple>

#include <gtest/gtest.h>

#include "color_calculator.hpp"
#include "mandelbrot.hpp"

using std::tuple;
using std::operator""i;

class TestColorCalculator : public ::testing::TestWithParam<tuple<plot::Color,
                                                                  plot::Canvas::Point>>,
                            public plot::ColorCalculator {
 public:
  TestColorCalculator() :
      plot::ColorCalculator({0x33CEFFFF,
                             0x3368FFFF,
                             0x6433FFFF,
                             0xCA33FFFF,
                             0xFF33CEFF,
                             0xFF3368FF},
                            plot::BLACK,
                            mandelbrot::escapeTime) { }

  void
  update() override { }
};

TEST_P(TestColorCalculator, CalculateColor) {
  auto [expected, point] = GetParam();

  auto actual = findColor(point);

  EXPECT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(, TestColorCalculator,
                         ::testing::Values(
                             tuple{plot::BLACK, 0.0 + 0.0i},
                             tuple{0xF3'33'D8'FF, 3.0 + 1.5i},
                             tuple{0x88'8C'BF'FF, -0.7615925686316078 + 0.3774627599091196i},
                             tuple{0xFA'33'D2'FF, -1.4264226680892969 - 0.047432573597014915i},
                             tuple{0xFF'33'7F'FF, 0.32636891459807016 + 0.4548624542701969i}));
