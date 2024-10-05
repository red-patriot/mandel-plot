#include <tuple>

#include <gtest/gtest.h>

#include "color.hpp"

using std::tuple;

class TestColor : public ::testing::TestWithParam<tuple<plot::Color,
                                                        plot::Color>> {
};

TEST_F(TestColor, GetRed) {
  std::uint8_t expected = 32;
  plot::Color uut{expected, 3, 5, 23};

  EXPECT_EQ(expected, uut.red());
}

TEST_F(TestColor, GetGreen) {
  std::uint8_t expected = 71;
  plot::Color uut{54, expected, 3, 23};

  EXPECT_EQ(expected, uut.green());
}

TEST_F(TestColor, GetBlue) {
  std::uint8_t expected = 46;
  plot::Color uut{243, 48, expected, 255};

  EXPECT_EQ(expected, uut.blue());
}

TEST_F(TestColor, GetAlpha) {
  std::uint8_t expected = 32;
  plot::Color uut{43, 211, 143, expected};

  EXPECT_EQ(expected, uut.alpha());
}

TEST_F(TestColor, SetRed) {
  std::uint8_t expected = 13;
  plot::Color uut;

  uut.red() = expected;

  EXPECT_EQ(expected, uut.red());
}

TEST_F(TestColor, SetGreen) {
  std::uint8_t expected = 123;
  plot::Color uut;

  uut.green() = expected;

  EXPECT_EQ(expected, uut.green());
}

TEST_F(TestColor, SetBlue) {
  std::uint8_t expected = 54;
  plot::Color uut;

  uut.blue() = expected;

  EXPECT_EQ(expected, uut.blue());
}

TEST_F(TestColor, SetAlpha) {
  std::uint8_t expected = 63;
  plot::Color uut;

  uut.alpha() = expected;

  EXPECT_EQ(expected, uut.alpha());
}

TEST_P(TestColor, Create) {
  auto& [expected, actual] = GetParam();

  EXPECT_EQ(expected, actual);
}

INSTANTIATE_TEST_CASE_P(, TestColor,
                        ::testing::Values(
                            tuple{plot::Color{255, 0, 0, 255},
                                  plot::colors::RED},
                            tuple{plot::Color{0, 255, 0, 255},
                                  plot::colors::GREEN},
                            tuple{plot::Color{0, 0, 255, 255},
                                  plot::colors::BLUE},
                            tuple{plot::Color{0, 0, 0, 255},
                                  plot::colors::BLACK},
                            tuple{plot::Color{255, 255, 255, 255},
                                  plot::colors::WHITE}));
