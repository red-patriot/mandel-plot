#ifndef MANDEL_PLOT_COLOR_CALCULATOR_HPP
#define MANDEL_PLOT_COLOR_CALCULATOR_HPP

#include <complex>
#include <vector>

#include "canvas.hpp"
#include "color.hpp"

namespace plot {
  class ColorCalculator {
   public:
    ColorCalculator(std::vector<Color> palette,
                    size_t (*escapeFunction)(Canvas::Point c, size_t limit));

    Color findColor(Canvas::Point point);

   private:
    std::vector<Color> palette_;
    size_t (*escapeFunction_)(std::complex<double> c, size_t limit);
  };
}  // namespace plot

#endif
