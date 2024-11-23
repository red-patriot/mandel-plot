#include "mandelbrot.hpp"

namespace {
  bool isInMainCardioidOrMainBulb(std::complex<double> z) {
    double x = z.real();
    double y = z.imag();
    double q = (x - 0.25) * (x - 0.25) + y * y;
    return q * (q + (x - 0.25)) <= 0.25 * y * y ||
           (x + 1.0) * (x + 1.0) + y * y <= 0.0625;
  }
  double abs2(std::complex<double> z) {
    return z.real() * z.real() + z.imag() * z.imag();
  }
  bool approx(const std::complex<double>& a, const std::complex<double>& b) {
    static constexpr double THRESHOLD = 1e-12;
    return std::abs(a.real() - b.real()) < THRESHOLD &&
           std::abs(a.imag() - b.imag()) < THRESHOLD;
  }
}  // namespace

namespace mandelbrot {

  std::complex<double> f(std::complex<double> z_n, std::complex<double> c) noexcept {
    return (z_n * z_n) + c;
  }

  plot::Escape escapeTime(std::complex<double> c, size_t limit) {
    plot::Escape result{plot::DOES_NOT_ESCAPE, c};
    if (::isInMainCardioidOrMainBulb(c)) {
      return result;
    }

    static constexpr double THRESHOLD = plot::ESCAPE_RADIUS * plot::ESCAPE_RADIUS;
    static constexpr size_t MAX_PERIOD = 20;

    result.value = 0.0;
    std::complex<double> oldValue = result.value;
    for (result.iteration = 1; result.iteration <= limit; ++result.iteration) {
      result.value = f(result.value, c);
      if (::abs2(result.value) > THRESHOLD) {
        return result;
      }
      // check periodicity
      if (::approx(result.value, oldValue)) {
        break;
      }

      if (result.iteration % MAX_PERIOD == 0) {
        oldValue = result.value;
      }
    }

    result.iteration = plot::DOES_NOT_ESCAPE;
    return result;
  }
}  // namespace mandelbrot
