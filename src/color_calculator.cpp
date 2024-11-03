#include "color_calculator.hpp"
#include <algorithm>

namespace plot {
  ColorCalculator::ColorCalculator(std::vector<Color> palette,
                                   Color noEscapeColor,
                                   Escape (*escapeFunction)(Canvas::Point c, size_t limit),
                                   std::shared_ptr<plot::Canvas> canvas) :
      palette_(std::move(palette)),
      noEscapeColor_(noEscapeColor),
      escapeFunction_(escapeFunction),
      canvas_(canvas) { }

  bool ColorCalculator::finished() const {
    return std::none_of(canvas_->begin(), canvas_->end(),
                        [](const Color& c) {
                          return alpha(c) == 0;
                        });
  }

  Color ColorCalculator::findColor(Canvas::Point point) const {
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

    auto color = interpolate(color1, color2, nu);
    return color;
  }
}  // namespace plot
