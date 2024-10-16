#include "mandelbrot.hpp"

namespace mandelbrot {
  std::complex<double> f(std::complex<double> z_n, std::complex<double> c) noexcept {
    return (z_n * z_n) + c;
  }

  plot::Escape escapeTime(std::complex<double> c, size_t limit) {
    static constexpr double THRESHOLD = 2.0;
    plot::Escape ret;

    ret.value = 0.0;
    for (ret.iteration = 1; ret.iteration <= limit; ++ret.iteration) {
      ret.value = f(ret.value, c);
      if (std::abs(ret.value) > THRESHOLD) {
        return ret;
      }
    }
    ret.iteration = plot::DOES_NOT_ESCAPE;
    return ret;
  }
}  // namespace mandelbrot
