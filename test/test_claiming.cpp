#include <algorithm>
#include <latch>
#include <thread>
#include <vector>

#include <gtest/gtest.h>

#include "claim_matrix.hpp"

TEST(TestClaimMatrix, Height) {
  size_t expected = 25;
  plot::ClaimMatrix uut{25};

  auto actual = uut.height();

  EXPECT_EQ(expected, actual);
}

TEST(TestClaimMatrix, AtomicClaim) {
  plot::ClaimMatrix uut{984};

  EXPECT_TRUE(uut.atomicClaim(94));
  // This fails because the pixel is already claimed
  EXPECT_FALSE(uut.atomicClaim(94));
}

TEST(TestClaimMatrix, NoRaceWhenClaiming) {
  size_t expected = 1;
  std::atomic_size_t couldClaim = 0;  // Number of triers that could claim the same pixel

  plot::ClaimMatrix uut{984};
  constexpr size_t TRIERS_COUNT = 50;
  std::latch syncPoint(TRIERS_COUNT);
  std::vector<std::jthread> triers;
  triers.reserve(TRIERS_COUNT);
  for (size_t i = 0; i != TRIERS_COUNT; ++i) {
    triers.emplace_back([&]() {
      syncPoint.arrive_and_wait();
      if (uut.atomicClaim(15)) {
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
