#ifndef MANDEL_PLOT_ESCAPE_CONSTANTS_HPP
#define MANDEL_PLOT_ESCAPE_CONSTANTS_HPP

#include <cstddef>

namespace plot {
  /** Indiates a point does not escape to infinity */
  static constexpr size_t DOES_NOT_ESCAPE = 0;
  /** The maximum number of iterations to perform */
  static constexpr size_t MAX_ITERATIONS = 100'000;
  /** Any point which reaches outside this radius will eventually escape to infinity */
  static constexpr double ESCAPE_RADIUS = 100.0;

  /** Indiates the results of an escape calculation */
  struct Escape {
    size_t iteration;           /**< The iterations it took to escape (or DOES_NOT_ESCAPE)*/
    std::complex<double> value; /**< The final value of the calculation */
  };
}  // namespace plot

#endif
