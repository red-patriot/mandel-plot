#include <gtest/gtest.h>

#include "color.hpp"

TEST(TestColor, CreateFromComponents) {
  plot::Color expected{0xFFBBAAEE};

  plot::Color actual = plot::combineColor(0xFF, 0xBB, 0xAA, 0xEE);

  EXPECT_EQ(expected, actual);
}

TEST(TestColor, GetRed) {
  std::uint8_t expected = 0xF1;

  auto actual = plot::red(0xF123BA34);

  EXPECT_EQ(expected, actual);
}

TEST(TestColor, GetGreen) {
  std::uint8_t expected = 0x23;

  auto actual = plot::green(0xF123BA34);

  EXPECT_EQ(expected, actual);
}

TEST(TestColor, GetBlue) {
  std::uint8_t expected = 0xBA;

  auto actual = plot::blue(0xF123BA34);

  EXPECT_EQ(expected, actual);
}

TEST(TestColor, GetAlpha) {
  std::uint8_t expected = 0x34;

  auto actual = plot::alpha(0xF123BA34);

  EXPECT_EQ(expected, actual);
}

TEST(TestColor, InterpolateCenter) {
  plot::Color expected = 0x15'EE'55'BB;

  plot::Color first = 0x12'FF'00'BB;
  plot::Color second = 0x18'DE'AA'BB;
  double ratio = 0.5;

  auto actual = plot::interpolate(first, second, ratio);

  EXPECT_EQ(expected, actual);
}

TEST(TestColor, InterpolateAllFirst) {
  plot::Color expected = 0x12'FF'00'BB;

  plot::Color first = 0x12'FF'00'BB;
  plot::Color second = 0x18'DE'AA'BB;
  double ratio = 0.0;

  auto actual = plot::interpolate(first, second, ratio);

  EXPECT_EQ(expected, actual);
}

TEST(TestColor, InterpolateAllSecond) {
  plot::Color expected = 0x18'DE'AA'BB;

  plot::Color first = 0x12'FF'00'BB;
  plot::Color second = 0x18'DE'AA'BB;
  double ratio = 1.0;

  auto actual = plot::interpolate(first, second, ratio);

  EXPECT_EQ(expected, actual);
}
