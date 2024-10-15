#include "color_calculator.hpp"

#include "escape_constants.hpp"

using std::operator""i;

namespace plot {
  ColorCalculator::ColorCalculator(std::vector<Color> palette,
                                   size_t (*escapeFunction)(Canvas::Point c, size_t limit),
                                   std::shared_ptr<plot::Canvas> canvas) :
      palette_(std::move(palette)),
      escapeFunction_(escapeFunction),
      canvas_(canvas) { }

  Color ColorCalculator::findColor(Canvas::Point point) {
    auto iterations = escapeFunction_(point, 1000);
    if (iterations == DOES_NOT_ESCAPE) {
      return BLACK;
    }

    return palette_[(iterations - 1) % palette_.size()];
  }

  void ColorCalculator::update() {
    if (finished_ || !canvas_) {
      return;
    }

    // calculate 1 row of the plot at a time
    for (currentCol_ = 0; currentCol_ != canvas_->width(); ++currentCol_) {
      auto point = canvas_->valueOf(currentCol_, currentRow_);
      (*canvas_)(currentCol_, currentRow_) = findColor(point);
    }

    ++currentRow_;
    if (currentRow_ == canvas_->height()) {
      finished_ = true;
    }
  }

}  // namespace plot
