#ifndef MANDEL_PLOT_MANDELBROT_HPP
#define MANDEL_PLOT_MANDELBROT_HPP

#include <complex>

#include "escape_constants.hpp"

namespace mandelbrot {
  std::complex<double> f(std::complex<double> z_n, std::complex<double> c) noexcept;
  plot::Escape escapeTime(std::complex<double> c, size_t limit = 1000);
}  // namespace mandelbrot

#endif
