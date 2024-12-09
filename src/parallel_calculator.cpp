#include "parallel_calculator.hpp"

#include <algorithm>
#include <chrono>
#include <functional>
#include <span>

using namespace std::chrono_literals;

namespace plot {
  ParallelCalculator::ParallelCalculator(size_t numberOfWorkers,
                                         std::vector<Color> palette,
                                         Color noEscapeColor,
                                         Escape (*escapeFunction)(Canvas::Point c, size_t limit),
                                         std::shared_ptr<plot::Canvas> canvas) :
      ColorCalculator(palette, noEscapeColor, escapeFunction, canvas),
      claims_(getCanvas().height()) {
    workers_.reserve(numberOfWorkers);
  }

  void ParallelCalculator::update() {
    std::this_thread::sleep_for(1ms);
  }

  bool ParallelCalculator::finished() const {
    return stillWorking_.load() == 0;
  }

  void ParallelCalculator::start() {
    workers_.clear();
    stillWorking_.store(static_cast<int>(workers_.capacity()));
    size_t step = getCanvas().height() / workers_.capacity();
    for (size_t i = 0; i < workers_.capacity(); ++i) {
      workers_.emplace_back(std::bind_front(&ParallelCalculator::calculate, this),
                            i * step);
    }
  }

  void ParallelCalculator::calculate(const std::stop_token& signal,
                                     size_t startY) {
    // For now, just find any available pixel to calculate
    for (size_t y = startY;
         !signal.stop_requested() && (y != getCanvas().height());
         ++y) {
      if (claim(y)) {
        std::vector<Color> calculatedRow(getCanvas().width(), BLACK);
        for (size_t x = 0; x != getCanvas().width(); ++x) {
          auto point = getCanvas().valueOf(x, y);
          auto color = findColor(point);
          calculatedRow.at(x) = color;
        }

        getCanvas().setRow(y, calculatedRow);
      }
    }

    stillWorking_.fetch_sub(1);
  }

  bool ParallelCalculator::claim(size_t row) {
    return claims_.atomicClaim(row);
  }
}  // namespace plot
