#ifndef MANDEL_PLOT_CALCULATOR_HPP
#define MANDEL_PLOT_CALCULATOR_HPP

#include <cstddef>

#include "canvas.hpp"

namespace plot {
  class IterationCalculator {
   public:
    virtual ~IterationCalculator() = default;

    virtual size_t operator()(Canvas::Point point, size_t escapeLimit) = 0;
  };
}  // namespace plot

#endif
