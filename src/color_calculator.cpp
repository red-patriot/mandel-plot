#include "color_calculator.hpp"

#include <cmath>
#include <cassert>

#include "escape_constants.hpp"

using std::operator""i;

namespace plot {
  ColorCalculator::ColorCalculator(std::vector<Color> palette,
                                   Escape (*escapeFunction)(Canvas::Point c, size_t limit),
                                   std::shared_ptr<plot::Canvas> canvas) :
      palette_(std::move(palette)),
      escapeFunction_(escapeFunction),
      canvas_(canvas) { }

  Color ColorCalculator::findColor(Canvas::Point point) {
    auto [iteration, z] = escapeFunction_(point, 10);
    if (iteration == DOES_NOT_ESCAPE) {
      return BLACK;
    }

    double logZn = std::log(std::abs(z));
    double nu = std::log(logZn / std::log(2)) / std::log(2);
    double fracIteration = iteration + 1 - nu;

    auto c1 = palette_[iteration % palette_.size()];
    auto c2 = palette_[(iteration + 1) % palette_.size()];
    double unused;
    double fracPart = std::modf(fracIteration, &unused);
    assert(fracPart < 1.0);
    auto actualColor = interpolate(c1, c2, fracPart);

    return actualColor;
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
