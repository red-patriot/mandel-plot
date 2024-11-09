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
      bufferCanvas_(*canvas) {
    for (size_t i = 0; i != getCanvas().height(); ++i) {
      claims_.emplace_back(getCanvas().width(), false);
    }

    workers_.reserve(numberOfWorkers);
    for (size_t i = 0; i < numberOfWorkers; ++i) {
      workers_.emplace_back(std::bind_front(&ParallelCalculator::calculate, this));
    }
  }

  void ParallelCalculator::update() {
    std::this_thread::sleep_for(1ms);
    std::unique_lock lock(calculationInProgress_);
    getCanvas() = bufferCanvas_;
  }

  void ParallelCalculator::calculate(const std::stop_token& signal) {
    // For now, just find an available row to calculate
    std::vector<Pixel> pixels;
    pixels.reserve(bufferCanvas_.width());
    for (size_t y = 0;
         !signal.stop_requested() && (y != bufferCanvas_.height());
         ++y) {
      pixels.clear();
      for (size_t x = 0; x != bufferCanvas_.width(); ++x) {
        pixels.emplace_back(Pixel{x, y});
      }

      if (claim(pixels)) {
        std::shared_lock lock(calculationInProgress_);
        for (const auto& [x, y] : pixels) {
          auto point = bufferCanvas_.valueOf(x, y);
          auto color = findColor(point);
          bufferCanvas_(x, y) = color;
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
