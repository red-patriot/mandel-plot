#include "parallel_calculator.hpp"

#include <algorithm>
#include <chrono>
#include <functional>

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
    static constexpr size_t MAX_ITERS = 256;
    static constexpr size_t BULK_READS = 512;
    std::array<std::pair<Pixel, Color>, BULK_READS> next;
    for (size_t i = 0; i != MAX_ITERS; ++i) {
      size_t count = readyPoints_.try_dequeue_bulk(next.begin(), next.size());
      std::span toCopy{next.data(), count};
      std::ranges::for_each(toCopy.begin(), toCopy.end(),
                            [this](const auto& n) {
                              const auto& [point, color] = n;
                              getCanvas()(point.x, point.y) = color;
                            });
    }
  }

  void ParallelCalculator::start() {
    workers_.clear();
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
        for (size_t x = 0; x != getCanvas().width(); ++x) {
          auto point = getCanvas().valueOf(x, y);
          auto color = findColor(point);
          readyPoints_.enqueue({Pixel{x, y}, color});
        }
      }
    }
  }

  bool ParallelCalculator::claim(size_t row) {
    return claims_.atomicClaim(row);
  }
}  // namespace plot
