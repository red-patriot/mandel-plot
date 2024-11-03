#include "simple_calculator.hpp"

#include <cmath>
#include <cassert>
#include <algorithm>

#include "escape_constants.hpp"

using std::operator""i;

namespace plot {
  SimpleCalculator::SimpleCalculator(std::vector<Color> palette,
                                     Color noEscapeColor,
                                     Escape (*escapeFunction)(Canvas::Point c, size_t limit),
                                     std::shared_ptr<plot::Canvas> canvas) :
      palette_(std::move(palette)),
      noEscapeColor_(noEscapeColor),
      escapeFunction_(escapeFunction),
      canvas_(canvas),
      pointsLeft_(canvas ? canvas->height() * canvas->width() : 0) { }

  Color SimpleCalculator::findColor(Canvas::Point point) {
    auto [iteration, z] = escapeFunction_(point, MAX_ITERATIONS);
    if (iteration == DOES_NOT_ESCAPE) {
      return noEscapeColor_;
    }

    double logZn = std::log(std::abs(z));
    double nu = std::log(logZn / std::log(plot::ESCAPE_RADIUS)) / std::log(2);
    nu = iteration + 1 - nu;

    auto color1 = palette_[iteration % palette_.size()];
    auto color2 = palette_[(iteration + 1) % palette_.size()];
    double unused;
    nu = std::modf(nu, &unused);
    assert(nu >= 0.0 && nu < 1.0);

    auto color = interpolate(color1, color2, nu);
    return color;
  }

  void SimpleCalculator::update() {
    if (finished() || !canvas_) {
      return;
    }

    // calculate 1 row of the plot at a time
    auto currentRow = canvas_->row(currentRow_);
    for (currentCol_ = 0; currentCol_ != canvas_->width(); ++currentCol_) {
      auto point = canvas_->valueOf(currentCol_, currentRow_);
      auto color = findColor(point);
      currentRow[currentCol_] = color;
    }
    auto reflectedRow = canvas_->row(canvas_->height() - (currentRow_ + 1));
    std::ranges::copy(currentRow, reflectedRow.begin());

    pointsLeft_ -= canvas_->width() * 2;  // 2 rows were colored on this iteration

    ++currentRow_;
  }

}  // namespace plot
