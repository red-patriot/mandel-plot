#include <complex>
#include <tuple>

#include <gtest/gtest.h>

#include "mandelbrot.hpp"

using std::operator""i;
using std::tuple;

class TestMandelbrotEquation : public ::testing::TestWithParam<tuple<std::complex<double>,
                                                             std::complex<double>,
                                                             std::complex<double>>> {
};

TEST_P(TestMandelbrotEquation, Test) {
  auto& [expected, z, c] = GetParam();

  auto actual = mandelbrot::f(z, c);

  EXPECT_NEAR(expected.real(), actual.real(), 1e-6);
  EXPECT_NEAR(expected.imag(), actual.imag(), 1e-6);
}

INSTANTIATE_TEST_CASE_P(, TestMandelbrotEquation,
                        ::testing::Values(tuple{2i,
                                                1.0 + 1i,
                                                0i},
                                          tuple{
                                              7.0132 - 0.2176i,
                                              0.34 - 0.32i,
                                              7.0 + 0i},
                                          tuple{83.838433 - 27.196576i,
                                                9.32143 - 1.432i,
                                                -1.0 - 0.5i},
                                          tuple{-1.35 - 0.72i,
                                                0.3 - 1.2i,
                                                0i}));
