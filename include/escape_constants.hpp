#ifndef MANDEL_PLOT_ESCAPE_CONSTANTS_HPP
#define MANDEL_PLOT_ESCAPE_CONSTANTS_HPP

#include <cstddef>

namespace plot {
  enum EscapeConstants : size_t {
    DOES_NOT_ESCAPE = 0
  };

  struct Escape {
    size_t iteration;
    std::complex<double> value;
  };
}  // namespace plot

#endif
