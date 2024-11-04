#ifndef MANDEL_PLOT_PARALLEL_CALCULATOR_HPP
#define MANDEL_PLOT_PARALLEL_CALCULATOR_HPP

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

   private:
    std::vector<std::jthread> workers_;

    void calculate(const std::stop_token& signal);
  };
}  // namespace plot

#endif
