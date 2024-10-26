#ifndef MANDEL_PLOT_COLOR_CALCULATOR_HPP
#define MANDEL_PLOT_COLOR_CALCULATOR_HPP

#include <complex>
#include <vector>

#include "canvas.hpp"
#include "color.hpp"
#include "escape_constants.hpp"

namespace plot {
  /** A Naive color calculator that calculates all colors in each row */
  class ColorCalculator {
   public:
    ColorCalculator(std::vector<Color> palette,
                    Color noEscapeColor,
                    Escape (*escapeFunction)(Canvas::Point c, size_t limit),
                    std::shared_ptr<plot::Canvas> cavnvas = nullptr);

    Color findColor(Canvas::Point point);

    void update();
    bool finished() const { return pointsLeft_ == 0; }

   private:
    std::vector<Color> palette_;
    Color noEscapeColor_;
    Escape (*escapeFunction_)(std::complex<double> c, size_t limit);
    size_t pointsLeft_;

    std::shared_ptr<plot::Canvas> canvas_;
    size_t currentCol_{0};
    size_t currentRow_{0};
  };
}  // namespace plot

#endif
