#ifndef MANDEL_PLOT_PARALLEL_CALCULATOR_HPP
#define MANDEL_PLOT_PARALLEL_CALCULATOR_HPP

#include <mutex>
#include <shared_mutex>
#include <span>
#include <thread>
#include <vector>

#include "color_calculator.hpp"

namespace plot {
  /** Performs color calculations in multiple threads to improve performance */
  class ParallelCalculator : public ColorCalculator {
   public:
    ParallelCalculator(size_t numberOfWorkers,
                       std::vector<Color> palette,
                       Color noEscapeColor,
                       Escape (*escapeFunction)(Canvas::Point c, size_t limit),
                       std::shared_ptr<plot::Canvas> canvas = nullptr);

    void update() override;
    void start() override;

   private:
    struct Pixel {
      size_t x;
      size_t y;
    };
    std::mutex claimInProgress_;
    std::shared_mutex calculationInProgress_;
    std::vector<std::jthread> workers_;
    Canvas bufferCanvas_;
    std::vector<std::vector<bool>> claims_;

    void calculate(const std::stop_token& signal);

    bool claim(std::span<Pixel> pixels);
  };
}  // namespace plot

#endif
