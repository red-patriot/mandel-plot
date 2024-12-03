#include "claim_matrix.hpp"

#include <algorithm>
#include <iterator>

namespace plot {
  ClaimMatrix::ClaimMatrix(size_t height) :
      height_(height),
      claims_(height) {
    std::ranges::fill(claims_, false); 
  }

  bool ClaimMatrix::atomicClaim(size_t y) {
    auto& element = this->claims_.at(y);
    return !element.exchange(true, std::memory_order_acq_rel);
  }
}  // namespace plot
