#ifndef MANDEL_PLOT_CLAIM_MATRIX_HPP
#define MANDEL_PLOT_CLAIM_MATRIX_HPP

#include <atomic>
#include <cstdint>
#include <vector>

namespace plot {
  class ClaimMatrix {
   public:
    class BoolWrapperRef {
     public:
      BoolWrapperRef(std::atomic_uint16_t& element, size_t offset);
      BoolWrapperRef& operator=(bool b);

      operator bool() const;

      bool atomicClaim();

     private:
      std::atomic_uint16_t& element_;
      uint16_t mask_;
    };
    using reference = BoolWrapperRef;
    using const_reference = const BoolWrapperRef;

    ClaimMatrix(size_t width, size_t height);

    size_t width() const { return width_; }
    size_t height() const { return height_; }

    reference at(size_t x, size_t y);
    const_reference at(size_t x, size_t y) const;
    bool atomicClaim(size_t x, size_t y);

   private:
    size_t width_;
    size_t height_;
    static_assert(std::atomic_uint16_t::is_always_lock_free);
    std::vector<std::vector<std::atomic_uint16_t>> claims_;

    reference createWrapper(size_t x, size_t y) const;
  };
}  // namespace plot

#endif
