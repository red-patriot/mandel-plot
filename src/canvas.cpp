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
    

    return points_(1, 2);
  }
  const Color& Canvas::operator[](const Point& location) const {
    return points_(0, 0);
  }
}  // namespace plot
