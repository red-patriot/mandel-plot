#ifndef MANDEL_PLOT_SIMPLE_CALCULATOR_HPP
#define MANDEL_PLOT_SIMPLE_CALCULATOR_HPP

#include "color_calculator.hpp"

namespace plot {
  /** A Naive color calculator that calculates all colors in each row */
  class SimpleCalculator : public ColorCalculator {
   public:
    using ColorCalculator::ColorCalculator;

    void update() override;

   private:
    size_t currentCol_{0};
    size_t currentRow_{0};
  };
}  // namespace plot

#endif
