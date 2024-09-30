#include <tuple>

#include <gtest/gtest.h>

#include "color.hpp"

using std::tuple;

class TestColorConstants : 
public ::testing::TestWithParam<tuple<plot::Color, 
plot::Color>> {
};

TEST_P(TestColorConstants, Test) {
    auto& [expected, actual] = GetParam();

    EXPECT_EQ(expected, actual);
}

INSTANTIATE_TEST_CASE_P(, TestColorConstants,
                        ::testing::Values(tuple{plot::Color{255, 0, 0, 255},
                                                plot::colors::RED},
                                          tuple{plot::Color{0, 255, 0, 255},
                                                plot::colors::GREEN},
                                          tuple{plot::Color{0, 0, 255, 255},
                                                plot::colors::BLUE},
                                          tuple{plot::Color{0, 0, 0, 255},
                                                plot::colors::BLACK},
                                          tuple{plot::Color{255, 255, 255, 255},
                                                plot::colors::WHITE}));