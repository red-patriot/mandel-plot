#ifndef MANDEL_PLOT_COLOR_CALCULATOR_HPP
#define MANDEL_PLOT_COLOR_CALCULATOR_HPP

#include <complex>
#include <vector>

#include "canvas.hpp"
#include "color.hpp"

namespace plot {
  /** A Naive color calculator that calculates all colors in each row */
  class ColorCalculator {
   public:
    ColorCalculator(std::vector<Color> palette,
                    size_t (*escapeFunction)(Canvas::Point c, size_t limit),
                    std::shared_ptr<plot::Canvas> cavnvas = nullptr);

    Color findColor(Canvas::Point point);

    void update();

   private:
    std::vector<Color> palette_;
    size_t (*escapeFunction_)(std::complex<double> c, size_t limit);

    std::shared_ptr<plot::Canvas> canvas_;
    bool finished_{false};
    size_t currentCol_{0};
    size_t currentRow_{0};
  };
}  // namespace plot

#endif
