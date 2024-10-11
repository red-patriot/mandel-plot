#ifndef MANDEL_PLOT_MANDELBROT_HPP
#define MANDEL_PLOT_MANDELBROT_HPP

#include <complex>

namespace mandelbrot {
  enum EscapeComstants : size_t {
    DOES_NOT_ESCAPE = 0
  };

  std::complex<double> f(std::complex<double> z_n, std::complex<double> c) noexcept;
  size_t escapeTime(std::complex<double> c, size_t limit = 1000);
}  // namespace mandelbrot

#endif
