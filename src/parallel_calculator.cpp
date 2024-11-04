#include "parallel_calculator.hpp"

#include <functional>

namespace plot {
  ParallelCalculator::ParallelCalculator(size_t numberOfWorkers,
                                         std::vector<Color> palette,
                                         Color noEscapeColor,
                                         Escape (*escapeFunction)(Canvas::Point c, size_t limit),
                                         std::shared_ptr<plot::Canvas> canvas) :
      ColorCalculator(palette, noEscapeColor, escapeFunction, canvas) {
    workers_.reserve(numberOfWorkers);
    for (size_t i = 0; i < numberOfWorkers; ++i) {
      workers_.emplace_back(std::bind_front(&ParallelCalculator::calculate, this));
    }
  }

  void ParallelCalculator::update() {
  }

  void ParallelCalculator::calculate(const std::stop_token&) {
  }
}  // namespace plot
