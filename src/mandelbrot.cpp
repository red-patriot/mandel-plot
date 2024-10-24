#include "mandelbrot.hpp"

namespace mandelbrot {
  static double abs2(std::complex<double> z) {
    return z.real() * z.real() + z.imag() * z.imag();
  }

  std::complex<double> f(std::complex<double> z_n, std::complex<double> c) noexcept {
    return (z_n * z_n) + c;
  }

  plot::Escape escapeTime(std::complex<double> c, size_t limit) {
    static constexpr double THRESHOLD = plot::ESCAPE_RADIUS * plot::ESCAPE_RADIUS;
    plot::Escape ret;

    ret.value = 0.0;
    for (ret.iteration = 1; ret.iteration <= limit; ++ret.iteration) {
      ret.value = f(ret.value, c);
      if (abs2(ret.value) > THRESHOLD) {
        return ret;
      }
    }
    ret.iteration = plot::DOES_NOT_ESCAPE;
    return ret;
  }
}  // namespace mandelbrot
