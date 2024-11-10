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

    /** Performs one update of the canvas */
    void update() override;
    /** Starts the calculations */
    void start() override;

   private:
    struct Pixel {
      size_t x;
      size_t y;
    };
    std::mutex claimInProgress_;              /**< Prevents races when workers try to claim pixels to calculate */
    std::shared_mutex calculationInProgress_; /**< Prevents races over shared data */
    std::vector<std::jthread> workers_;       /**< The parallel workers to perform calculations */
    Canvas bufferCanvas_;                     /**< Buffer to perform calculations over in parallel */
    std::vector<std::vector<bool>> claims_;   /**< Indicates which pixels are currently claimed */

    /** Performs calculations over the canvas until signaled to stop or done */
    void calculate(const std::stop_token& signal);

    /** Claims the given pixels to calculate. Indicates if the pixels are available */
    bool claim(std::span<Pixel> pixels);
  };
}  // namespace plot

#endif
