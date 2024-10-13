#include "color_calculator.hpp"

#include "escape_constants.hpp"

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
}  // namespace plot
