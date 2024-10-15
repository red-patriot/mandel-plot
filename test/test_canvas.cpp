#include <Eigen/Core>
#include <algorithm>
#include <complex>

#include <gtest/gtest.h>

#include "canvas.hpp"

using namespace std::complex_literals;

using std::operator""i;

TEST(TestCanvas, ConstructsCanvasOfCorrectSize) {
  plot::Canvas::Point smallestPoint{-1.0, -1.0};
  plot::Canvas::Point greatestPoint{1.0, 1.0};

  plot::Canvas uut{smallestPoint, greatestPoint, 50, 100};

  EXPECT_EQ(50, uut.width());
  EXPECT_EQ(100, uut.height());
}

TEST(TestCanvas, GetWidth) {
  plot::Canvas::Point smallestPoint{-1.0, -1.0};
  plot::Canvas::Point greatestPoint{1.0, 1.0};

  plot::Canvas uut{smallestPoint, greatestPoint, 1580, 1960};

  EXPECT_EQ(1580, uut.width());
}

TEST(TestCanvas, GetHeight) {
  plot::Canvas::Point smallestPoint{-1.0, -1.0};
  plot::Canvas::Point greatestPoint{1.0, 1.0};

  plot::Canvas uut{smallestPoint, greatestPoint, 1580, 1960};

  EXPECT_EQ(1960, uut.height());
}

TEST(TestCanvas, IndexColorsByComplex) {
  plot::Canvas::Point smallestPoint{-1.0, -1.0};
  plot::Canvas::Point greatestPoint{1.0, 1.0};

  plot::Canvas uut{smallestPoint, greatestPoint, 10, 10};

  uut[0.5 + 0.5i] = plot::RED;
  uut[0.5 - 0.5i] = plot::BLUE;

  auto first = uut[0.5 + 0.5i];
  auto second = uut[0.5 - 0.5i];

  EXPECT_EQ(plot::RED, first);
  EXPECT_EQ(plot::BLUE, second);
}

TEST(TestCanvas, IndexColorsByIndex) {
  plot::Canvas::Point smallestPoint{-1.0, -1.0};
  plot::Canvas::Point greatestPoint{1.0, 1.0};

  plot::Canvas uut{smallestPoint, greatestPoint, 10, 10};

  uut(6, 7) = plot::RED;
  uut(7, 4) = plot::BLUE;

  auto first = uut(6, 7);
  auto second = uut(7, 4);

  EXPECT_EQ(plot::RED, first);
  EXPECT_EQ(plot::BLUE, second);
}

TEST(TestCanvas, IndicatesSpan) {
  plot::Canvas::Point smallestPoint = 1.0 + 1.0i;
  plot::Canvas::Point greatestPoint = 2.0 + 3.0i;
  auto expected = 1.0 + 2.0i;

  plot::Canvas uut{smallestPoint, greatestPoint, 10, 10};

  auto actual = uut.span();

  EXPECT_EQ(expected, actual);
}

TEST(TestCanvas, GetStepSize) {
  plot::Canvas::Point smallestPoint = 1.0 + 1.0i;
  plot::Canvas::Point greatestPoint = 2.0 + 3.0i;
  auto expected = 0.1 + 0.1i;

  plot::Canvas uut{smallestPoint, greatestPoint, 10, 20};

  auto actual = uut.step();

  EXPECT_EQ(expected, actual);
}

TEST(TestCanvas, GetPointOfPixel) {
  plot::Canvas::Point smallestPoint = 1.0 - 1.0i;
  plot::Canvas::Point greatestPoint = 2.0 + 3.0i;
  auto expected = 1.5 + 0.4i;

  plot::Canvas uut{smallestPoint, greatestPoint, 10, 40};

  auto actual = uut.valueOf(5, 14);

  EXPECT_NEAR(expected.real(), actual.real(), 1e-6);
  EXPECT_NEAR(expected.imag(), actual.imag(), 1e-6);
}

TEST(TestCanvas, GetPointOfPixelStart) {
  plot::Canvas::Point smallestPoint = 1.0 - 1.0i;
  plot::Canvas::Point greatestPoint = 2.0 + 3.0i;
  auto expected = 1.0 - 1.0i;

  plot::Canvas uut{smallestPoint, greatestPoint, 10, 40};

  auto actual = uut.valueOf(0, 0);

  EXPECT_NEAR(expected.real(), actual.real(), 1e-6);
  EXPECT_NEAR(expected.imag(), actual.imag(), 1e-6);
}

TEST(TestCanvas, GetPointOfPixelEnd) {
  plot::Canvas::Point smallestPoint = 1.0 - 1.0i;
  plot::Canvas::Point greatestPoint = 2.0 + 3.0i;
  auto expected = 2.0 + 3.0i;

  plot::Canvas uut{smallestPoint, greatestPoint, 10, 40};

  auto actual = uut.valueOf(10, 40);

  EXPECT_NEAR(expected.real(), actual.real(), 1e-6);
  EXPECT_NEAR(expected.imag(), actual.imag(), 1e-6);
}

TEST(TestCanvas, CannotConstructWithNonPositiveWidth) {
  EXPECT_THROW(plot::Canvas c(0.0 - 1.0i, 1.0 + 1.0i, -5, 20), std::invalid_argument);
}

TEST(TestCanvas, CannotConstructWithNonPositiveHeight) {
  EXPECT_THROW(plot::Canvas c(0.0 - 1.0i, 1.0 + 1.0i, 20, -100), std::invalid_argument);
}
