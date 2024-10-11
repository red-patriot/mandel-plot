#include "mandelbrot.hpp"

namespace mandelbrot {
  std::complex<double> f(std::complex<double> z_n, std::complex<double> c) noexcept {
    return (z_n * z_n) + c;
  }

  size_t escapeTime(std::complex<double> c, size_t limit) {
    static constexpr double THRESHOLD = 2.0;

    std::complex<double> z = 0.0;
    for (size_t iteration = 1; iteration <= limit; ++iteration) {
      z = f(z, c);
      if (std::abs(z) > THRESHOLD) {
        return iteration;
      }
    }

    return DOES_NOT_ESCAPE;
  }
}  // namespace mandelbrot
