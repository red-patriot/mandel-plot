#ifndef MANDEL_PLOT_CLAIM_MATRIX_HPP
#define MANDEL_PLOT_CLAIM_MATRIX_HPP

#include <atomic>
#include <cstdint>
#include <vector>

namespace plot {
  class ClaimMatrix {
   public:
    explicit ClaimMatrix(size_t height);

    size_t height() const { return height_; }

    bool atomicClaim(size_t y);

   private:
    size_t height_;
    static_assert(std::atomic_uint16_t::is_always_lock_free);
    std::vector<std::atomic_bool> claims_;
  };
}  // namespace plot

#endif
