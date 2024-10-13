#include "color_calculator.hpp"

#include "escape_constants.hpp"

using std::operator""i;

namespace plot {
  ColorCalculator::ColorCalculator(std::vector<Color> palette,
                                   size_t (*escapeFunction)(Canvas::Point c, size_t limit)) :
      palette_(std::move(palette)),
      escapeFunction_(escapeFunction) { }

  Color ColorCalculator::findColor(Canvas::Point point) {
    auto iterations = escapeFunction_(point, 1000);
    if (iterations == DOES_NOT_ESCAPE) {
      return BLACK;
    }

    return palette_[(iterations - 1) % palette_.size()];
  }

  void ColorCalculator::update(Canvas& canvas) {
    // calculate 1 row of the plot at a time
    auto imagStep = canvas.step().imag();
    auto realStep = canvas.step().real();

    if (first_) {
      first_ = false;
      currentPoint_ = canvas.min();
    }

    for (; currentPoint_.real() <= canvas.max().real(); currentPoint_ += realStep) {
      canvas[currentPoint_] = findColor(currentPoint_);
    }

    currentPoint_ = {canvas.min().real(), currentPoint_.imag() + imagStep};
  }

}  // namespace plot
