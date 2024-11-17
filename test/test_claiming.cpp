#include <algorithm>
#include <latch>
#include <thread>
#include <vector>

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

TEST(TestClaimMatrix, AtomicClaim) {
  plot::ClaimMatrix uut{357, 984};

  EXPECT_TRUE(uut.atomicClaim(312, 94));
  // This fails because the pixel is already claimed
  EXPECT_FALSE(uut.atomicClaim(312, 94));
}

TEST(TestClaimMatrix, NoRaceWhenClaiming) {
  size_t expected = 1;
  std::atomic_size_t couldClaim = 0;  // Number of triers that could claim the same pixel

  plot::ClaimMatrix uut{357, 984};
  constexpr size_t TRIERS_COUNT = 50;
  std::latch syncPoint(TRIERS_COUNT);
  std::vector<std::jthread> triers;
  triers.reserve(TRIERS_COUNT);
  for (size_t i = 0; i != TRIERS_COUNT; ++i) {
    triers.emplace_back([&]() {
      syncPoint.arrive_and_wait();
      if (uut.atomicClaim(15, 15)) {
        ++couldClaim;
      }
    });
  }

  for (auto& trier : triers) {
    trier.join();  // Wait for all threads to finish
  }

  // Only one trier should ever be successf
  EXPECT_EQ(expected, couldClaim);
}
