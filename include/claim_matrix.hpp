#ifndef MANDEL_PLOT_CLAIM_MATRIX_HPP
#define MANDEL_PLOT_CLAIM_MATRIX_HPP

#include <cstdint>

namespace plot {
  class ClaimMatrix {
   public:
    ClaimMatrix(size_t width, size_t height);

    size_t width() const { return width_; }
    size_t height() const { return height_; }

   private:
    size_t width_;
    size_t height_;
  };
}  // namespace plot

#endif
