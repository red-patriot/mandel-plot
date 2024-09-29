#include <Eigen/Core>
#include <gtest/gtest.h>

#include "canvas.hpp"

using Eigen::Vector2d;

TEST(TestCanvas, Has2DCanvasField) {
  Vector2d smallestPoint{-1.0, -1.0};
  Vector2d greatestPoint{1.0, 1.0};

  plot::Canvas uut{smallestPoint, greatestPoint, 100, 100};

  auto& actual = uut.getPoints();

  EXPECT_EQ(100 * 100, actual.size());
}

TEST(TestCanvas, ConstructsCanvasOfCorrectSize) {
  Vector2d smallestPoint{-1.0, -1.0};
  Vector2d greatestPoint{1.0, 1.0};

  plot::Canvas uut{smallestPoint, greatestPoint, 50, 100};

  auto& actual = uut.getPoints();

  EXPECT_EQ(50, actual.cols());
  EXPECT_EQ(100, actual.rows());
}

TEST(TestCanvas, GetWidth) {
  Vector2d smallestPoint{-1.0, -1.0};
  Vector2d greatestPoint{1.0, 1.0};

  plot::Canvas uut{smallestPoint, greatestPoint, 1580, 1960};

  EXPECT_EQ(1580, uut.width());
}

TEST(TestCanvas, GetHeight) {
  Vector2d smallestPoint{-1.0, -1.0};
  Vector2d greatestPoint{1.0, 1.0};

  plot::Canvas uut{smallestPoint, greatestPoint, 1580, 1960};

  EXPECT_EQ(1960, uut.height());
}
