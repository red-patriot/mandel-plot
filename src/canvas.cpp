#include "canvas.hpp"

namespace plot {
  Canvas::Canvas(const Point& minPoint,
                 const Point& maxPoint,
                 size_t width, size_t height) :
      points_(height, width),
      min_(minPoint),
      max_(maxPoint) { }

  Canvas::View Canvas::allPoints() const {
    return points_;
  }

  Color& Canvas::operator[](const Point& location) {
    auto index = indexOf(location);
    return points_(index.first, index.second);
  }
  const Color& Canvas::operator[](const Point& location) const {
    auto index = indexOf(location);
    return points_(index.first, index.second);
  }

  std::pair<Eigen::Index, Eigen::Index> Canvas::indexOf(const Point& location) const {
    size_t column = width() / (max_.real() - min_.real()) * (location.real() - min_.real());
    size_t row = height() / (max_.imag() - min_.imag()) * (location.imag() - min_.imag());

    return {column, row};
  }
}  // namespace plot
