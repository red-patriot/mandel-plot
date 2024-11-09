#ifndef MANDEL_PLOT_COLOR_CALCULATOR_HPP
#define MANDEL_PLOT_COLOR_CALCULATOR_HPP

#include <complex>
#include <vector>

#include "canvas.hpp"
#include "color.hpp"
#include "escape_constants.hpp"

namespace plot {
  /** An interface for an object that performs color calculations */
  class ColorCalculator {
   public:
    ColorCalculator(std::vector<Color> palette,
                    Color noEscapeColor,
                    Escape (*escapeFunction)(Canvas::Point c, size_t limit),
                    std::shared_ptr<plot::Canvas> cavnvas = nullptr);

    virtual void update() = 0;
    bool finished() const;
    virtual void start() { }

   protected:
    Color findColor(Canvas::Point point) const;

    Canvas& getCanvas() const { return *canvas_; }

   private:
    std::vector<Color> palette_;
    Color noEscapeColor_;
    Escape (*escapeFunction_)(std::complex<double> c, size_t limit);

    std::shared_ptr<plot::Canvas> canvas_;
  };
}  // namespace plot

#endif
