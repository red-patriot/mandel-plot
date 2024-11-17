#include <algorithm>

#include <gtest/gtest.h>

#include "claim_matrix.hpp"

TEST(TestClaimMatrix, Width) {
  size_t expected = 10;
  plot::ClaimMatrix uut{10, 25};

  auto actual = uut.width();

  EXPECT_EQ(expected, actual);
}

TEST(TestClaimMatrix, Height) {
  size_t expected = 25;
  plot::ClaimMatrix uut{10, 25};

  auto actual = uut.height();

  EXPECT_EQ(expected, actual);
}

TEST(TestClaimMatrix, SetAndRead) {
  plot::ClaimMatrix uut{128, 128};

  EXPECT_FALSE(uut.at(95, 49));

  uut.at(95, 49) = true;

  EXPECT_TRUE(uut.at(95, 49));
}
