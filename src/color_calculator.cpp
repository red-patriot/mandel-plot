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
    if (finished_) {
      return;
    }

    // calculate 1 row of the plot at a time
    for (currentCol_ = 0; currentCol_ != canvas.width(); ++currentCol_) {
      auto point = canvas.valueOf(currentCol_, currentRow_);
      canvas(currentCol_, currentRow_) = findColor(point);
    }

    ++currentRow_;
    if (currentRow_ == canvas.height()) {
      finished_ = true;
    }
  }

}  // namespace plot
