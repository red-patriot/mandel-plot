#include "claim_matrix.hpp"

#include <algorithm>
#include <iterator>

namespace plot {
  ClaimMatrix::ClaimMatrix(size_t width, size_t height) :
      width_(width),
      height_(height) {
    for (size_t i = 0; i != height; ++i) {
      claims_.emplace_back(width / 16 + 1);
    }
  }

  ClaimMatrix::reference ClaimMatrix::at(size_t x, size_t y) {
    return createWrapper(x, y);
  }
  ClaimMatrix::const_reference ClaimMatrix::at(size_t x, size_t y) const {
    return createWrapper(x, y);
  }

  ClaimMatrix::reference ClaimMatrix::createWrapper(size_t x, size_t y) const {
    size_t xIndex = x / 16;
    size_t xShiftOffset = x % 16;
    auto& elementGroup = claims_.at(y).at(xIndex);
    // This line below feels like an evil hack...
    return BoolWrapperRef{const_cast<std::atomic_uint16_t&>(elementGroup), xShiftOffset};
  }

  ClaimMatrix::BoolWrapperRef::BoolWrapperRef(std::atomic_uint16_t& element, size_t offset) :
      element_(element),
      mask_(0b01 << offset) { }

  ClaimMatrix::BoolWrapperRef& ClaimMatrix::BoolWrapperRef::operator=(bool b) {
    if (b) {
      element_.fetch_or(mask_);
    } else {
      element_.fetch_and(~mask_);
    }
    return *this;
  }

  ClaimMatrix::BoolWrapperRef::operator bool() const {
    return static_cast<bool>(element_.load() & mask_);
  }

}  // namespace plot
