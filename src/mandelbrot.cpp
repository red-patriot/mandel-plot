#include "mandelbrot.hpp"

namespace mandelbrot {
  std::complex<double> f(std::complex<double> z_n, std::complex<double> c) noexcept {
    return (z_n * z_n) + c;
  }
}  // namespace mandelbrot
