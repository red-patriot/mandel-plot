#include "parallel_calculator.hpp"

#include <algorithm>
#include <functional>

namespace plot {
  ParallelCalculator::ParallelCalculator(size_t numberOfWorkers,
                                         std::vector<Color> palette,
                                         Color noEscapeColor,
                                         Escape (*escapeFunction)(Canvas::Point c, size_t limit),
                                         std::shared_ptr<plot::Canvas> canvas) :
      ColorCalculator(palette, noEscapeColor, escapeFunction, canvas) {
    for (size_t i = 0; i != getCanvas().height(); ++i) {
      claims_.emplace_back(getCanvas().width(), false);
    }

    workers_.reserve(numberOfWorkers);
  }

  void ParallelCalculator::update() {
    static constexpr size_t MAX_ITERS = 1000;
    std::pair<Pixel, Color> next;
    for (size_t i = 0; i != MAX_ITERS && readyPoints_.try_dequeue(next); ++i) {
      const auto& [point, color] = next;
      getCanvas()(point.x, point.y) = color;
    }
  }

  void ParallelCalculator::start() {
    for (size_t i = 0; i < workers_.capacity(); ++i) {
      workers_.emplace_back(std::bind_front(&ParallelCalculator::calculate, this));
    }
  }

  void ParallelCalculator::calculate(const std::stop_token& signal) {
    // For now, just find an available row to calculate
    std::vector<Pixel> pixels;
    pixels.reserve(getCanvas().width());
    for (size_t y = 0;
         !signal.stop_requested() && (y != getCanvas().height());
         ++y) {
      pixels.clear();
      for (size_t x = 0; x != getCanvas().width(); ++x) {
        pixels.emplace_back(Pixel{x, y});
      }

      if (claim(pixels)) {
        for (const auto& [x, y] : pixels) {
          auto point = getCanvas().valueOf(x, y);
          auto color = findColor(point);
          readyPoints_.enqueue({Pixel{x, y}, color});
        }
      }
    }
  }

  bool ParallelCalculator::claim(std::span<ParallelCalculator::Pixel> pixels) {
    std::lock_guard lg(claimInProgress_);

    if (std::none_of(pixels.begin(), pixels.end(),
                     [this](const Pixel& p) -> bool {
                       return claims_.at(p.y).at(p.x);
                     })) {
      std::for_each(pixels.begin(), pixels.end(),
                    [this](const Pixel& p) {
                      claims_.at(p.y).at(p.x) = true;
                    });
      return true;
    }

    return false;
  }
}  // namespace plot
