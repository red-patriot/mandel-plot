#include "mandelbrot.hpp"

namespace {
  bool isInMainCardioidOrMainBulb(std::complex<double> z) {
    double x = z.real();
    double y = z.imag();
    double q = (x - 0.25) * (x - 0.25) + y * y;
    return q * (q + (x - 0.25)) <= 0.25 * y * y ||
           (x + 1.0) * (x + 1.0) + y * y <= 0.0625;
  }
}  // namespace

namespace mandelbrot {
  static double abs2(std::complex<double> z) {
    return z.real() * z.real() + z.imag() * z.imag();
  }

  std::complex<double> f(std::complex<double> z_n, std::complex<double> c) noexcept {
    return (z_n * z_n) + c;
  }

  plot::Escape escapeTime(std::complex<double> c, size_t limit) {
    plot::Escape result{plot::DOES_NOT_ESCAPE, c};
    if (::isInMainCardioidOrMainBulb(c)) {
      return result;
    }

    static constexpr double THRESHOLD = plot::ESCAPE_RADIUS * plot::ESCAPE_RADIUS;

    result.value = 0.0;
    for (result.iteration = 1; result.iteration <= limit; ++result.iteration) {
      result.value = f(result.value, c);
      if (abs2(result.value) > THRESHOLD) {
        return result;
      }
    }

    result.iteration = plot::DOES_NOT_ESCAPE;
    return result;
  }
}  // namespace mandelbrot
