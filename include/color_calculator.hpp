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

    /** Performs one update of the canvas */
    virtual void update() = 0;
    /** Indicates that all calculations are finished */
    bool finished() const;
    /** Starts calculating pixel values */
    virtual void start() { }

   protected:
    /** Calculates the color of one given point on the canvas */
    Color findColor(Canvas::Point point) const;

    /** Accesses the canvas */
    Canvas& getCanvas() const { return *canvas_; }

   private:
    std::vector<Color> palette_;                                     /**< The color palette to use for pixel colors */
    Color noEscapeColor_;                                            /**< The color for a pixel that is in the set */
    Escape (*escapeFunction_)(std::complex<double> c, size_t limit); /**< Calculates the escape time of a point*/

    std::shared_ptr<plot::Canvas> canvas_;
  };
}  // namespace plot

#endif
