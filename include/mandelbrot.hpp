#ifndef MANDEL_PLOT_MANDELBROT_HPP
#define MANDEL_PLOT_MANDELBROT_HPP

#include <complex>

namespace mandelbrot {
  std::complex<double> f(std::complex<double> z_n, std::complex<double> c) noexcept;
}

#endif
