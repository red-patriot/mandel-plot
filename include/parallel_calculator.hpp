#ifndef MANDEL_PLOT_PARALLEL_CALCULATOR_HPP
#define MANDEL_PLOT_PARALLEL_CALCULATOR_HPP

#include <span>
#include <thread>
#include <vector>
#include <concurrentqueue/concurrentqueue.h>

#include "color_calculator.hpp"
#include "claim_matrix.hpp"

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

    moodycamel::ConcurrentQueue<std::pair<Pixel, Color>> readyPoints_; /**< Pixels which are ready to be displayed */
    ClaimMatrix claims_;                                               /**< Indicates which pixels are currently claimed */
    std::vector<std::jthread> workers_;                                /**< The parallel workers to perform calculations */

    /** Performs calculations over the canvas until signaled to stop or done */
    void calculate(const std::stop_token& signal,
                   size_t startY);

    /** Claims the given pixels to calculate. Indicates if the pixels are available */
    bool claim(Pixel pixel);
  };
}  // namespace plot

#endif
