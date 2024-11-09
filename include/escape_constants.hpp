#ifndef MANDEL_PLOT_ESCAPE_CONSTANTS_HPP
#define MANDEL_PLOT_ESCAPE_CONSTANTS_HPP

#include <cstddef>

namespace plot {
  static constexpr size_t DOES_NOT_ESCAPE = 0;
  static constexpr size_t MAX_ITERATIONS = 100'000;
  static constexpr double ESCAPE_RADIUS = 100.0;

  struct Escape {
    size_t iteration;
    std::complex<double> value;
  };
}  // namespace plot

#endif
