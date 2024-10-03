#include <Eigen/Core>
#include <algorithm>
#include <complex>

#include <gtest/gtest.h>

#include "canvas.hpp"

using namespace std::complex_literals;

using std::operator""i;

TEST(TestCanvas, Has2DCanvasField) {
  plot::Canvas::Point smallestPoint{-1.0, -1.0};
  plot::Canvas::Point greatestPoint{1.0, 1.0};

  plot::Canvas uut{smallestPoint, greatestPoint, 100, 100};

  auto& actual = uut.allPoints();

  EXPECT_EQ(100 * 100, actual.size());
}

TEST(TestCanvas, ConstructsCanvasOfCorrectSize) {
  plot::Canvas::Point smallestPoint{-1.0, -1.0};
  plot::Canvas::Point greatestPoint{1.0, 1.0};

  plot::Canvas uut{smallestPoint, greatestPoint, 50, 100};

  auto& actual = uut.allPoints();

  EXPECT_EQ(50, actual.cols());
  EXPECT_EQ(100, actual.rows());
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

  uut[0.5 + 0.5i] = plot::colors::RED;
  uut[0.5 - 0.5i] = plot::colors::BLUE;

  auto first = uut[0.5 + 0.5i];
  auto second = uut[0.5 - 0.5i];

  EXPECT_EQ(plot::colors::RED, first);
  EXPECT_EQ(plot::colors::BLUE, second);
}

TEST(TestCanvas, IndexColorsByIndex) {
  plot::Canvas::Point smallestPoint{-1.0, -1.0};
  plot::Canvas::Point greatestPoint{1.0, 1.0};

  plot::Canvas uut{smallestPoint, greatestPoint, 10, 10};

  uut(6, 7) = plot::colors::RED;
  uut(7, 4) = plot::colors::BLUE;

  auto first = uut(6, 7);
  auto second = uut(7, 4);

  EXPECT_EQ(plot::colors::RED, first);
  EXPECT_EQ(plot::colors::BLUE, second);
}

TEST(TestCanvas, IndicatesSpan) {
  plot::Canvas::Point smallestPoint = 1.0 + 1.0i;
  plot::Canvas::Point greatestPoint = 2.0 + 3.0i;
  auto expected = 1.0 + 2.0i;

  plot::Canvas uut{smallestPoint, greatestPoint, 10, 10};

  auto actual = uut.span();

  EXPECT_EQ(expected, actual);
}